#include "Button.h"
#include "Exception.h"
#include <Windows.h>

LRESULT CALLBACK DummyProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
        Button* pButton = static_cast<Button*>(cs->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&Button::ProcStart);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pButton);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


Button::Button(const char* text, int width, int height, int x, int y, unsigned char align,
    int fontSize, HWND hParent, HINSTANCE hInstance, Style style):
    text(text),
    style(style),
    fontSize(fontSize)
{
    Element::width = width;
    Element::height = height;
    posX = x;
    posY = y;
    Element::align = align;
    Element::hParent = hParent;
    handCursor = LoadCursor(NULL, IDC_HAND);
    
    const char* className = "CustomButtonClass";

    WNDCLASS wc = {};
    wc.lpszClassName = className;
    wc.hbrBackground = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = DummyProc;
    
    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0,
        className,
        text,
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

    

    TRACKMOUSEEVENT tme = {};
    tme.dwFlags = TME_HOVER;
    tme.cbSize = sizeof(tme);
    tme.dwHoverTime = 1;
    tme.hwndTrack = hwnd;
    BOOL a = TrackMouseEvent(&tme);
    if (!a)
    {
        ERROR_MESSAGE_LAST_ERROR();
    }
    
}

void Button::SetText(const char* text)
{
    Button::text = text;
}

void Button::SetStyle(Style style)
{
    Button::style = style;
}


HWND Button::Show(HWND hParent, HINSTANCE hInstance)
{
    ShowWindow(hwnd, 10);
    Align(hParent);
    return hwnd;
}

void Button::RaiseEvent(int windowMessage)
{
    if(commands.size() != 0)
    commands[windowMessage](this);
}

LRESULT CALLBACK Button::ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (commands.contains(uMsg))
    {
        RaiseEvent(uMsg);
        if (overwriteProc) return;
    }

    switch (uMsg)
    {
    case WM_PAINT:
    {
        HFONT font = CreateFont(fontSize , 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI")
        );
        PAINTSTRUCT ps = {};
        auto hrc = BeginPaint(hwnd, & ps);
        
        SelectObject(hrc, font);
        SetTextColor(hrc, style.foreground);
        SetBkColor(hrc, style.background);
        SetTextAlign(hrc, TA_CENTER);
        
        if (style.borderColor != NULL)
        {
            HPEN pen = CreatePen(PS_SOLID, style.borderThickness, RGB(255, 0, 0));
            SelectObject(hrc, pen);
        }
        
        auto r = RoundRect(hrc, 0, 0, width, height, style.cornerRadius, style.cornerRadius);
        r = TextOut(hrc, width / 2, ((height - fontSize)/2), text, strlen(text));
        DeleteObject(font);
        EndPaint(hwnd, &ps);
        break;
    }
    case WM_SETCURSOR:
    {
        SetCursor(handCursor);
        break;
    }
    
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Button::ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    Button* pButton = reinterpret_cast<Button*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
    return pButton->ButtonProc(hwnd, uMsg, wParam, lParam);
}

void Button::LoadChilds(HINSTANCE hInstance)
{
}

void Button::AddChild(Element& rElement)
{
}

void Button::RemoveChild(Element* target)
{
}

void Button::RemoveChild(int index)
{
}
