#pragma once
#include <windows.h>
#include "Element.h"

class Label : public Element
{
public:
	/// <summary>
	/// Create a Label window
	/// </summary>
	/// <param name="text">Label's text</param>
	/// <param name="x">X position</param>
	/// <param name="y">Y position</param>
	/// <param name="width">Width of the element</param>
	/// <param name="height">Height of the element</param>
	/// <param name="hParent">Parent's HWND</param>
	/// <param name="hInstance">Application HISTANCE</param>
	/// <param name="align">Align type</param>
	/// <param name="fontHeight">Font size in logical unities</param>
	/// <param name="background">Background COLORREF</param>
	/// <param name="foreground">Foreground COLORREF</param>
	/// <param name="hFont">[UNUSED] Font type</param>
	Label(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align,
		Style style,
		int fontHeight = 35,
		HFONT hFont = NULL);
	
	/// <summary>
	/// Change label's text
	/// </summary>
	/// <param name="newText">New text</param>
	void ChangeText(const char* newText);

	void SetColor(COLORREF foregroud = NULL, COLORREF background = NULL);

	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

private:
	static LRESULT CALLBACK ProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	const char* text;
	int fontHeight;
	HFONT hFont;

};

