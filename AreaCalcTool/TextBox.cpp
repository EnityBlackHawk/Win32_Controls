#include "TextBox.h"
#include "Exception.h"


TextBox::TextBox(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align)
{
	Element::width = width;
	Element::height = height;
	Element::posX = x;
	Element::posY = y;
	Element::hParent = hParent;
	Element::align = align;



	hwnd = CreateWindow(
		"EDIT",
		TEXT(text),
		WS_CHILD | style,
		posX,
		posY,
		width,
		height,
		hParent,
		NULL,
		hInstance,
		NULL
	);
	if (!hwnd)
	{
		ErrorMessageLastError();
		return;
	}

}


HWND TextBox::Show(HWND hParent, HINSTANCE hInstance)
{

	if (!hwnd) return 0;
	ShowWindow(hwnd, 10);
	if (align) Align(hParent);
	return hwnd;
}
