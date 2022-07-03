#include "Window.h"
#include "Label.h"
#include "StackPanel.h"
#include "Button.h"

Window window;

LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return window.InternalWindowProc(hwnd, uMsg, wParam, lParam);
}

void ButtonClick(Element* sender)
{
	auto b = reinterpret_cast<Button*>(sender);
	b->SetText("Clicked");
	b->SetStyle({ 10, WHITE, RGB(255, 0, 0), RGB(255, 0,0), 1});
	b->Reload();
}

int WinMain(HINSTANCE hInstance, HINSTANCE hIgnore, PSTR lpCmdLine, INT nCmdShow)
{
	window = Window(hInstance, "Title", WinProc, RGB(0, 0, 25), RGB(127,0,0), RGB(0, 0, 25), RGB(255,255,255), 0);
	
	StackPanel s = StackPanel(0, 0, 0, 0, ALIGN_CENTER, window.GetHwnd(), hInstance, {0, RGB(25,0,0)}, VERTICAL);

	Label l = Label("Welcome", 0, 0, AUTO, AUTO, s.GetHwnd(), hInstance, ALIGN_CENTER, {0, NULL, WHITE}, 35);
	s.AddChild(l);

	Button b = Button("Click me", 200, 50, 0, 0, ALIGN_CENTER, 35, s.GetHwnd(), hInstance, {10, WHITE});
	b.SetMargin({ 0, 5, 0, 0 });
	s.AddChild(b);
	b.AddEvent(WM_LBUTTONUP, ButtonClick);

	window.AddElement(s);
	window.Show();
}
