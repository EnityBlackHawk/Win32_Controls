#include "Frame.h"
#include "Exception.h"
#include <windows.h>

LRESULT CALLBACK FrameProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static Style style;
    switch (uMsg)
    {
    case WM_CREATE:
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        style = *reinterpret_cast<Style*>(cs->lpCreateParams);
        break;
    }
    case WM_PAINT:
    {
        RECT parentRect;
        GetWindowRect(hwnd, &parentRect);

        PAINTSTRUCT ps = {};
        auto hdc = BeginPaint(hwnd, &ps);
        HBRUSH b = CreateSolidBrush(style.background);
        SelectObject(hdc, b);
        
        if (style.borderColor)
        {
            HPEN hp = CreatePen(PS_SOLID, style.borderThickness, style.borderColor);
            SelectObject(hdc, hp);
        }
        else
        {
            HPEN hp = CreatePen(PS_SOLID, style.borderThickness, style.background);
            SelectObject(hdc, hp);
        }
        
        if(style.background != NULL)
        RoundRect(hdc, 0, 0, parentRect.right - parentRect.left, parentRect.bottom - parentRect.top, style.cornerRadius, style.cornerRadius);
        

        EndPaint(hwnd, &ps);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


Frame::Frame(int x, int y, int width, int height, unsigned char alignment, HWND hParent, HINSTANCE hInstance, 
    Style style)
{
    posX = x;
    posY = y;
    Element::width = width;
    Element::height = height;
    Element::align = alignment;
    Element::paintStyle = style;
    Element::hParent = hParent;

    const char* name = "frame";
    HBRUSH b;

    if (style.background == NULL)
    {
        b = (HBRUSH)GetClassLongPtr(hParent, GCLP_HBRBACKGROUND);
    }
    else b = CreateSolidBrush(style.background);

    WNDCLASS fr = {};
    fr.lpszClassName = "frame";
    fr.hbrBackground = (HBRUSH)GetClassLongPtr(hParent, GCLP_HBRBACKGROUND);;
    fr.hInstance = hInstance;
    fr.lpfnWndProc = ProcSetup;
    fr.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&fr);

    hwnd = CreateWindowExA(
        WS_OVERLAPPED,
        name,
        nullptr,
        WS_CHILD,
        posX,
        posY,
        width,
        height,
        hParent,
        NULL,
        hInstance,
        this
    );

    if (!hwnd) return;


}

LRESULT Frame::ProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        Frame* pFrame = reinterpret_cast<Frame*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&Frame::ProcStart);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pFrame);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Frame::ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Frame* pFrame = reinterpret_cast<Frame*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    return pFrame->MainProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Frame::MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        //RECT parentRect;
        //GetWindowRect(hwnd, &parentRect);

        PAINTSTRUCT ps = {};
        auto hdc = BeginPaint(hwnd, &ps);
        HBRUSH b = CreateSolidBrush(paintStyle.background);
        SelectObject(hdc, b);

        if (paintStyle.borderColor)
        {
            HPEN hp = CreatePen(PS_SOLID, paintStyle.borderThickness, paintStyle.borderColor);
            SelectObject(hdc, hp);
        }
        else
        {
            HPEN hp = CreatePen(PS_SOLID, paintStyle.borderThickness, paintStyle.background);
            SelectObject(hdc, hp);
        }

        if (paintStyle.background != NULL)
           RoundRect(hdc, 0, 0, width, height, paintStyle.cornerRadius, paintStyle.cornerRadius);

        EndPaint(hwnd, &ps);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HWND Frame::Show(HWND hParent, HINSTANCE hInstance)
{
    ShowWindow(hwnd, 10);
    Align(hParent);
    LoadChilds(hInstance);
    return hwnd;
}

void Frame::OnSizeChanged(HWND hParent)
{
    Align(hParent);
    for (auto e : elements)
    {
        e->Align(hwnd);
    }
}

void Frame::LoadChilds(HINSTANCE hInstance)
{
    for (auto e : elements)
    {
        e->Show(hwnd, hInstance);
    }
}


void Frame::AddChild(Element& rElement)
{
    if (rElement.GetPatentHwnd() != hwnd)
    {
        ERROR_MESSAGE("hParent invalid");
        return;
    }

    if (paintStyle.background && !rElement.GetPaintStyle().background)
    {
        rElement.SetPaintStyleBackground(paintStyle.background);
    }

    elements.push_back(&rElement);
}

void Frame::RemoveChild(Element* target)
{
}

void Frame::RemoveChild(int index)
{
}
