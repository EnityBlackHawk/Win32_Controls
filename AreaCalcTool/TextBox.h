#pragma once
#include <Windows.h>
#include "Element.h"
class TextBox : public Element
{
public:
	TextBox(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align);

	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;
	
};

