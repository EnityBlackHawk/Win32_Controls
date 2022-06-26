#pragma once
#include <Windows.h>
#include "Element.h"
#include "ICommandable.h"
#include <string>
class TextBox : public Element, public ICommandable
{
public:
	TextBox(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align, Style style);
	std::string GetText() const;

	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

private:

	static LRESULT CALLBACK ProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	Style style;
	HWND hEdit;
	

	// Inherited via ICommandable
	virtual void RaiseEvent(int windowMessage) override;

};

