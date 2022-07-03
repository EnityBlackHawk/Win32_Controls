#pragma once
#include <Windows.h>

#define ALIGN_NONE 0
#define ALIGN_LEFT 1
#define ALIGN_CENTER 2
#define ALIGN_RIGHT 3
#define ALIGN_STREACH 4

#define ALIGN_CENTER_WINDOW 5
#define ALIGN_STREACH_WINDOW 6

#define BLACK RGB(0,0,1)
#define WHITE RGB(255, 255,255)

#define AUTO -1
#define RESIDUAL_SPACE -2

struct Margin
{
	int left;
	int top;
	int right;
	int bottom;
};

struct Style
{
	int cornerRadius = 0;
	COLORREF background = NULL;
	COLORREF foreground = NULL;
	COLORREF borderColor = NULL;
	int borderThickness = 0;
};

class Element
{
public:
	int GetActualWidth()
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		return rect.right - rect.left;
	}

	int GetActualHeight()
	{
		RECT rect;
		GetWindowRect(hwnd, &rect);
		return rect.bottom - rect.top;
	}

	int GetPosX()
	{
		return posX;
	}
	int GetPosY()
	{
		return posY;
	}
	int GetWidth()
	{
		return width;
	}
	int GetHeight()
	{
		return height;
	}
	HWND GetHwnd()
	{
		return hwnd;
	}
	unsigned char GetAlign()
	{
		return align;
	}
	void SetAlign(unsigned char newAlign)
	{
		align = newAlign;
	}

	/// <summary>
	/// Set postion x, postion y, width and heght
	/// </summary>
	/// <param name="x">New x position</param>
	/// <param name="y">New y position</param>
	/// <param name="newWidth">New width</param>
	/// <param name="newHeight">New height</param>
	/// <param name="modes">[optional] Window SetWindowPos config flags</param>
	virtual void SetPosition(int x, int y, int newWidth, int newHeight, DWORD modes)
	{	

		if(x != AUTO) width = newWidth;
		if (y != AUTO) height = newHeight;

		auto b = SetWindowPos(hwnd, NULL, x, y, width, height, modes);
	}
	/// <summary>
	/// Draw window
	/// </summary>
	/// <param name="hParent">Parent's HWND</param>
	/// <param name="hInstance">Application HINSTANCE</param>
	/// <returns>Window HWND</returns>
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) = 0;
	/// <summary>
	/// Function called when the window's size is chaged
	/// </summary>
	/// <param name="hParent">Parent's HWND</param>
	virtual void OnSizeChanged(HWND hParent)
	{
		Align(hParent);
	}


	/// <summary>
	/// Set window style
	/// </summary>
	/// <param name="style">Window style flag</param>
	void SetWindowStyle(DWORD style)
	{
		Element::style = style;
	}

	void SetMargin(Margin margin)
	{
		Element::margin = margin;
	}

	/// <summary>
	/// Align the element based on parent window
	/// </summary>
	/// <param name="hParent">Parent's HWND</param>
	void Align(HWND hParent)
	{
		if (align == ALIGN_CENTER_WINDOW)
		{
			RECT rect;
			GetWindowRect(hParent, &rect);
			auto parentWidth = (rect.right - 20) - rect.left;
			auto parentHeight = (rect.bottom - 41) - rect.top;


			auto newX = (parentWidth / 2) - (width / 2);
			auto newY = ((parentHeight / 2) - (height / 2));

			posX = newX;
			posY = newY;

			SetPosition(newX, newY, width, height, SWP_NOSIZE);
		}
		else if (align == ALIGN_STREACH_WINDOW)
		{
			RECT rect;
			GetWindowRect(hParent, &rect);
			auto parentWidth = (rect.right - 20) - rect.left;
			auto parentHeight = (rect.bottom - 41) - rect.top;

			width = parentWidth - (margin.left + margin.right);
			height = parentHeight - (margin.bottom + margin.top);

			posX = margin.left;
			posY = margin.top;


			SetPosition(margin.left, margin.top, width, height, 0);
		}
		else if (align == ALIGN_CENTER)
		{
			RECT rect;
			GetWindowRect(hParent, &rect);
			auto parentWidth = rect.right - rect.left;
			auto parentHeight = rect.bottom - rect.top;


			auto newX = (parentWidth / 2) - (width / 2);
			auto newY = (parentHeight / 2) - (height / 2);

			posX = newX;
			posY = newY;

			SetPosition(newX, newY, width, height, SWP_NOSIZE);
		}
		else if (align == ALIGN_STREACH)
		{
			RECT rect;
			GetWindowRect(hParent, &rect);
			auto parentWidth = (rect.right) - rect.left;
			auto parentHeight = (rect.bottom) - rect.top;

			width = parentWidth - (margin.left + margin.right);
			height = parentHeight - (margin.bottom + margin.top);

			posX = margin.left;
			posY = margin.top;

			SetPosition(margin.left, margin.top, width, height, 0);
		}
	}

	void SetParent(HWND hParent)
	{
		Element::hParent = hParent;
	}

	/// <summary>
	/// Redraw the element. This function will mainly call the WS_PAINT
	/// </summary>
	void Reload()
	{
		if (!hwnd) return;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}

	HWND GetPatentHwnd()
	{
		return hParent;
	}

	void SetPaintStyleBackground(COLORREF color)
	{
		paintStyle.background = color;
	}

	Style GetPaintStyle()
	{
		return paintStyle;
	}

	Margin margin = { 0,0,0,0 };

protected:
	int posX;
	int posY;
	int width;
	int height;
	DWORD style;
	Style paintStyle;
	HWND hwnd;
	HWND hParent;
	unsigned char align;


};