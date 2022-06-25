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

struct Margin
{
	int left;
	int top;
	int right;
	int bottom;
};


class Element
{
public:
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

	virtual void SetPosition(int x, int y, int newWidth, int newHeight, DWORD modes)
	{	
		width = newWidth;
		height = newHeight;
		auto b = SetWindowPos(hwnd, NULL, x, y, width, height, modes);
	}
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) = 0;
	virtual void OnSizeChanged(HWND hParent)
	{
		Align(hParent);
	}

	void SetStyle(DWORD style)
	{
		Element::style = style;
	}

	void SetMargin(Margin margin)
	{
		Element::margin = margin;
	}

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


			SetPosition(1 + margin.left, margin.top, width, height, 0);
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

	void Reload()
	{
		if (!hwnd) return;
		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}

	HWND GetPatentHwnd()
	{
		return hParent;
	}

	Margin margin = { 0,0,0,0 };

protected:
	int posX;
	int posY;
	int width;
	int height;
	DWORD style;
	HWND hwnd;
	HWND hParent;
	unsigned char align;


};