#pragma once
#include <Windows.h>
#include <vector>
#include "Element.h"

class Window
{
public:
	Window() = default;
	/// <summary>
	/// Create a main window
	/// </summary>
	/// <param name="hInstance">Application HINSTANCE</param>
	/// <param name="name">Window title</param>
	/// <param name="windowProcedure">Window procedure function</param>
	/// <param name="background">Background color</param>
	/// <param name="borderColor">Window border color (Win11 only)</param>
	/// <param name="captionColor">Tile bar color</param>
	/// <param name="titleColor">Tilebar's tile color</param>
	/// <param name="dStyle">Window's styles</param>
	/// <param name="dStyleEx">Window's extended styles</param>
	Window(HINSTANCE hInstance, const char* name, WNDPROC windowProcedure, COLORREF background, 
		COLORREF borderColor = NULL, COLORREF captionColor = NULL, COLORREF titleColor = NULL,
		DWORD dStyle = NULL, DWORD dStyleEx = NULL);
	LRESULT CALLBACK InternalWindowProc(HWND hwnd, UINT uMgs, WPARAM wPram, LPARAM lParam);
	/// <summary>
	/// Show window
	/// </summary>
	void Show() const;
	/// <summary>
	/// Add element to show on window
	/// </summary>
	void AddElement(Element& rElement);
	/// <summary>
	/// Get actual window width
	/// </summary>
	/// <returns>Width value</returns>
	int GetActualWidth() const;

	/// <summary>
	/// Get actual window height
	/// </summary>
	/// <returns>Height value</returns>
	int GetActualHeight() const;
	/// <summary>
	/// Get element added
	/// </summary>
	/// <returns>Element pointer</returns>
	Element* operator[](int index);
	
	/// <summary>
	/// Get window hwnd
	/// </summary>
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

