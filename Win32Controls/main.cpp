#include "Window.h"
#include "Label.h"
#include "StackPanel.h"
#include "Button.h"
#include "Grid.h"

Window window;

LRESULT CALLBACK WinProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return window.InternalWindowProc(hwnd, uMsg, wParam, lParam);
}

void ButtonClick(Element* sender)
{
	auto b = reinterpret_cast<Button*>(sender);
	b->SetStyle({ 0, BLACK, WHITE, BLACK, 0});
	b->Reload();
}

int WinMain(HINSTANCE hInstance, HINSTANCE hIgnore, PSTR lpCmdLine, INT nCmdShow)
{
	window = Window(hInstance, "Title", WinProc, RGB(0, 0, 25), RGB(127,0,0), RGB(0, 0, 25), RGB(255,255,255), 0);
	
	Grid g = Grid(0, 0, 0, 0, ALIGN_STREACH, window.GetHwnd(), hInstance, {});
	
	g.DefineColumn(200, RESIDUAL_SPACE);
	g.DefineRow(RESIDUAL_SPACE);
	g.GenerateGrid();

	StackPanel menuStack = StackPanel(0, 0, 0, 0, ALIGN_STREACH, GET_GRID_HWND(g, 0, 0), hInstance, {0, WHITE}, HORIZONTAL);
	g.AddElement(menuStack, 0, 0);

	Button homeButton = Button("Home", 200, 40, 0, 0, ALIGN_NONE, 35, menuStack.GetHwnd(), hInstance, { 0, WHITE, BLACK, NULL, 0});
	homeButton.AddEvent(WM_LBUTTONUP, ButtonClick);
	menuStack.AddChild(homeButton);
	
	window.AddElement(g);
	window.Show();
}
