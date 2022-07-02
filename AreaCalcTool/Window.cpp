#include "Window.h"
#include "Label.h"
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")


Window::Window(HINSTANCE hInstance, const char* name, WNDPROC windowProcedure, COLORREF background, 
	COLORREF borderColor, COLORREF captionColor, COLORREF textColor, DWORD dStyle, DWORD dStyleEx):
	name(name),
	hInstace(hInstance),
	borderColor(borderColor),
	captionColor(captionColor),
	textColor(textColor)
{

	elements = {};
	WNDCLASS wc = {};
	wc.lpszClassName = name;
	wc.lpfnWndProc = windowProcedure;
	wc.hbrBackground = CreateSolidBrush(background);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	
	RegisterClass(&wc);


	hwnd = CreateWindowExA(
		WS_EX_OVERLAPPEDWINDOW | dStyleEx,
		name,
		name,
		WS_TILEDWINDOW | dStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstace,
		NULL
	);

	if (!hwnd) return;
	
	HRESULT h;
	if (captionColor != NULL)
	{
		h = DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &captionColor, sizeof(captionColor));
	}
	if (textColor != NULL)
	{
		h = DwmSetWindowAttribute(hwnd, DWMWA_TEXT_COLOR, &textColor, sizeof(textColor));
	}
	
	//if (fullColoredWindow)
	//{
	//	MARGINS m = { -1 };
	//	h = DwmExtendFrameIntoClientArea(hwnd, &m);
	//}
	if (borderColor != NULL)
	{
		h = DwmSetWindowAttribute(hwnd, DWMWA_BORDER_COLOR, &borderColor, sizeof(borderColor));
	}

}

void Window::Show() const
{
	BOOL result = ShowWindow(hwnd, 10);


	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::AddElement(Element& element)
{
	if (element.GetAlign() == ALIGN_CENTER) element.SetAlign(ALIGN_CENTER_WINDOW);
	else if (element.GetAlign() == ALIGN_STREACH) element.SetAlign(ALIGN_STREACH_WINDOW);
	element.SetParent(hwnd);
	elements.push_back(&element);
}


LRESULT Window::InternalWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_SHOWWINDOW:

		for (auto e : elements)
		{
			e->Show(hwnd, hInstace);
		}
		break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps = {};
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	}
		
		
	case WM_SIZE:
		for (auto e : elements)
		{
			e->OnSizeChanged(hwnd);
		}
		break;

	case WM_ERASEBKGND:
	{
		break;
	}

	case WM_LBUTTONUP:
	{
		
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int Window::GetActualWidth() const
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	return rect.right - rect.left;
}

int Window::GetActualHeight() const
{
	RECT rect;
	GetWindowRect(hwnd, &rect);
	return rect.bottom - rect.top;
}

Element* Window::operator[](int index)
{
	return elements[index];
}





