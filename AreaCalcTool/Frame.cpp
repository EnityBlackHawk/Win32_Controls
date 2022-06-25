#include "Frame.h"
#include <windows.h>

LRESULT CALLBACK FrameProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps = {};
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        break;
    }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


Frame::Frame(int x, int y, int width, int height, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background):
    background(background)
{
    posX = x;
    posY = y;
    Element::width = width;
    Element::height = height;
    Element::align = alignment;

    const char* name = "frame";
    HBRUSH b;

    if (background == NULL)
    {
        b = (HBRUSH)GetClassLongPtr(hParent, GCLP_HBRBACKGROUND);
    }
    else b = CreateSolidBrush(background);

    WNDCLASS fr = {};
    fr.lpszClassName = "frame";
    fr.hbrBackground = b;
    fr.hInstance = hInstance;
    fr.lpfnWndProc = FrameProc;
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
        NULL
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
