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
	
	StackPanel s = StackPanel(0, 0, ALIGN_CENTER, window.GetHwnd(), hInstance, NULL);
	TextBox tb = TextBox("", 0, 0, 150, 30, s.GetHwnd(), hInstance, ALIGN_CENTER, {10, WHITE, BLACK, RGB(25,0,0), 1});
	pTb = &tb;
	Button b = Button("Verificar", 100, 30, 0, 0, ALIGN_CENTER, 25,s.GetHwnd(), hInstance, { 5, WHITE, BLACK });
	b.SetMargin({ 0, 10, 0,0 });
	b.AddEvent(WM_LBUTTONUP, EventTeste);

	s.AddChild(tb);
	s.AddChild(b);

	window.AddElement(s);

	window.Show();
}
