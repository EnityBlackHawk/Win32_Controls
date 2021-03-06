#include "Grid.h"
#include "Exception.h"


Grid::Grid(int x, int y, int width, int height, unsigned char align, HWND hParent, HINSTANCE hInstance, Style frameStyle):
    hInstance(hInstance),
    frameStyle(frameStyle)
{
    Element::width = width;
    Element::height = height;
    Element::posX = x;
    Element::posY = y;
    Element::align = align;
    
    const char* className = "GridClass";

    WNDCLASS wc = {};
    wc.lpszClassName = className;
    wc.hbrBackground = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = DummyProc;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        className,
        "",
        WS_CHILD | BS_OWNERDRAW,
        x,
        y,
        width,
        height,
        hParent,
        NULL,
        hInstance,
        this
    );

    if (!hwnd) return;
}

void Grid::AddElement(Element& element, int row, int column)
{
    Frame& f = GetFrame(row, column);
    f.AddChild(element);
}

HWND Grid::Show(HWND hParent, HINSTANCE hInstance)
{
    ShowWindow(hwnd, 10);
    
    return hwnd;
}

Frame& Grid::GetFrame(int row, int column)
{
    return vFrames[framesIndex[row][column]];
}

LRESULT CALLBACK Grid::DummyProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        Grid* pGrid = static_cast<Grid*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&Grid::ProcStart);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pGrid);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Grid::GenerateGrid()
{
    int x = 0;
    int y = 0;
    int w = 0, h = 0, t = 0;

    framesIndex = (int**)malloc(rows.size() * sizeof(int*));
    for (int i = 0; i < rows.size(); i++)
    {
        framesIndex[i] = (int*)malloc(columns.size() * sizeof(int));
    }

    for (int i = 0; i < rows.size(); i++)
    {
        for (int j = 0; j < columns.size(); j++)
        {

            if (columns[j] == -1)
            {
                int temp = 0;
                for (int k : columns)
                {
                    temp = k == -1 ? temp : temp + k;
                }
                w = GetActualWidth() - temp;
            }
            else w = columns[j];
            if (rows[i] == -1)
            {
                int temp = 0;
                for (int k : rows)
                {
                    temp = k == -1 ? temp : temp + k;
                }
                h = GetActualHeight() - temp;
            }
            else h = rows[i];
            Frame f = Frame(x, y, w, h, 0, hwnd, hInstance, frameStyle);
            vFrames.push_back(f);

            framesIndex[i][j] = t;
            x += w;
            t++;
        }
        x = 0;
        y += h + 1;
    }

    for (Frame f : vFrames)
    {
        f.Show(hwnd, hInstance);
    }
}

LRESULT Grid::ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Grid* pGrid = reinterpret_cast<Grid*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    return pGrid->MainProc(hwnd, uMsg, wParam, lParam);
}

void Grid::ResizeFrames()
{
    int x = 0;
    int y = 0;
    int h = 0;
    int w = 0;
    for (int i = 0; i < rows.size(); i++)
    {
        for (int j = 0; j < columns.size(); j++)
        {
            if (columns[j] == RESIDUAL_SPACE)
            {
                int temp = 0;
                for (int k : columns)
                {
                    temp = k == RESIDUAL_SPACE ? temp : temp + k;
                }
                w = GetActualWidth() - temp;
            }
            else w = columns[j];
            if (rows[i] == RESIDUAL_SPACE)
            {
                int temp = 0;
                for (int k : rows)
                {
                    temp = k == RESIDUAL_SPACE ? temp : temp + k;
                }
                h = GetActualHeight() - temp;
            }
            else h = rows[i];
            vFrames[framesIndex[i][j]].SetPosition(x, y, w, h, 0);
            vFrames[framesIndex[i][j]].Reload();
            vFrames[framesIndex[i][j]].LoadChilds(hInstance);
            x += w;
        }
        x = 0;
        y += h;
    }
}

void Grid::RecalculateAuto()
{
    int x = 0;
    int y = 0;
    int h = 0;
    int w = 0;
    for (int i = 0; i < rows.size(); i++)
    {
        for (int j = 0; j < columns.size(); j++)
        {
            if (columns[j] == AUTO)
            {
                for (int k = 0; k < rows.size(); k++)
                {
                    Frame f = vFrames[framesIndex[k][j]];
                    auto c = f.GetChildElements();
                    for (Element* e : c)
                    {
                        int eW = e->GetWidth();
                        w = eW > w ? eW : w;
                    }
                    f.SetPosition(f.GetPosX(), f.GetPosY(), w, f.GetHeight(), 0);
                }

                for (j++; j < columns.size(); j++)
                {
                    for (int k = 0; k < rows.size(); k++)
                    {
                        Frame f = vFrames[framesIndex[k][j]];
                        f.SetPosition(f.GetPosX() + w, f.GetPosY(), f.GetWidth(), f.GetHeight(), 0);
                        f.Reload();
                    }   
                }
            }
        }
    }
}

LRESULT Grid::MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps = {};
        HDC hdc = BeginPaint(hwnd, &ps);

        //if (vFrames.empty()) GenerateFrames();

        ResizeFrames();
        //RecalculateAuto();


        EndPaint(hwnd, &ps);
        break;
    }
    case WM_SIZE:
        ResizeFrames();
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}







