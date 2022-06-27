#include "Window.h"
#include "Label.h"
#include "TextBox.h"
#include "Frame.h"
#include "StackPanel.h"
#include "Button.h"
#include "Grid.h"

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

	Grid g = Grid(0, 0, 0, 0, ALIGN_STREACH, window.GetHwnd(), hInstance);
	g.DefineRow(150, 150, -1);
	g.DefineColumn(150, 150, -1);
	g.GenerateGrid();

	Label l = Label("Teste", 0, 0, AUTO, AUTO, GET_GRID_HWND(0, 2), hInstance, ALIGN_CENTER, 35);
	g.AddElement(l, 0, 2);

	window.AddElement(g);
	window.Show();
}
