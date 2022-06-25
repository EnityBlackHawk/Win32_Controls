#include "Window.h"
#include "Label.h"
#include "TextBox.h"
#include "Frame.h"
#include "StackPanel.h"
#include "Button.h"

Window window;


LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return window.InternalWindowProc(hwnd, uMsg, wParam, lParam);
}

void EventTeste(Element* sender)
{
	Button* b = reinterpret_cast<Button*>(sender);
	b->SetText("Clicado");
	b->Reload();
}

int WinMain(HINSTANCE hInstance, HINSTANCE hIgnore, PSTR lpCmdLine, INT nCmdShow)
{
	window = Window(hInstance, "Title", WinProc, RGB(0, 0, 25), RGB(255,255,255), RGB(0, 0, 25), RGB(255,255,255));
	StackPanel s = StackPanel(0, 0, ALIGN_CENTER, window.GetHwnd(), hInstance, NULL);

	Label l = Label("Welcome", 0, 0, 0, 0, s.GetHwnd(), hInstance, ALIGN_NONE, 35, RGB(0, 0, 25), RGB(255, 255, 255));
	l.SetMargin({ 0, 0, 0, 5 });


	Button b = Button("Click me", 100, 45, 0, 0, ALIGN_NONE, s.GetHwnd(), hInstance, WHITE, BLACK, 10);
	b.AddEvent(WM_LBUTTONUP, EventTeste);
	
	s.AddChild(l);
	s.AddChild(b);
	window.AddElement(s);
	window.Show();
}
