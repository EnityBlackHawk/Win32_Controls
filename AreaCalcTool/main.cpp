#include "Window.h"
#include "Label.h"
#include "TextBox.h"
#include "Frame.h"
#include "StackPanel.h"
#include "Button.h"

Window window;
TextBox* pTb;

LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return window.InternalWindowProc(hwnd, uMsg, wParam, lParam);
}

void EventTeste(Element* sender)
{
	OutputDebugString(pTb->GetText().c_str());
}

int WinMain(HINSTANCE hInstance, HINSTANCE hIgnore, PSTR lpCmdLine, INT nCmdShow)
{
	window = Window(hInstance, "Title", WinProc, RGB(0, 0, 25), RGB(255,255,255), RGB(0, 0, 25), RGB(255,255,255));
	Frame f = Frame(0, 0, 10, 10, 0, window.GetHwnd(), hInstance, {});
	window.Show();
}
