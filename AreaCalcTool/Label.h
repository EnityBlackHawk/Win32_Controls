#pragma once
#include <windows.h>
#include "Element.h"

#define AUTO 0

class Label : public Element
{
public:
	Label() = default;
	Label(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align, 
		int fontHeight = 35, 
		COLORREF background = NULL,
		COLORREF foreground = RGB(255, 255, 255), 
		HFONT hFont = NULL);
	void ChangeText(const char* newText);
	void SetColor(COLORREF foregroud = NULL, COLORREF background = NULL);

	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

private:
	static LRESULT CALLBACK ProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	const char* text;
	COLORREF backgroundColor;
	COLORREF foregroundColor;
	int fontHeight;
	HFONT hFont;

};

