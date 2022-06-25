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
	


	window.Show();
}
