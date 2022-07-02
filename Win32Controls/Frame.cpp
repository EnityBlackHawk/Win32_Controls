#include "Frame.h"
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
    Style style):
    style(style)
{
    posX = x;
    posY = y;
    Element::width = width;
    Element::height = height;
    Element::align = alignment;

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
    fr.lpfnWndProc = FrameProc;
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
        &style
    );

    if (!hwnd) return;


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
        MessageBox(hwnd, "Invalid hParent", "Error", NULL);
        return;
    }
    elements.push_back(&rElement);
}

void Frame::RemoveChild(Element* target)
{
}

void Frame::RemoveChild(int index)
{
}
