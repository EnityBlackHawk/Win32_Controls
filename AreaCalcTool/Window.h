#pragma once
#include <Windows.h>
#include <vector>
#include "Element.h"

class Window
{
public:
	Window() = default;
	Window(HINSTANCE hInstance, const char* name, WNDPROC windowProcedure, COLORREF background, 
		COLORREF borderColor = NULL, COLORREF captionColor = NULL, COLORREF titleColor = NULL,
		DWORD dStyle = NULL, DWORD dStyleEx = NULL);
	LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT uMgs, WPARAM wPram, LPARAM lParam);
	void Show() const;
	void AddElement(Element&);
	int GetActualWidth() const;
	int GetActualHeight() const;
	Element* operator[](int index);
	HWND GetHwnd()
	{
		return hwnd;
	}


private:
	HWND hwnd;
	HINSTANCE hInstace;
	const char* name;
	COLORREF borderColor;
	COLORREF captionColor;
	COLORREF textColor;
	std::vector<Element*> elements;
};

