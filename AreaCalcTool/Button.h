#pragma once
#include <windows.h>
#include "ICommandable.h"
#include "Frame.h"

class Button : public Element, public ICommandable, public IParentable
{
public:
	Button(const char* text, int width, int height, int x, int y, unsigned char align, HWND hParent, 
		HINSTANCE hInstance, Style style);
	void SetText(const char* text);
	

	// Inherited via Element
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

	// Inherited via ICommandable
	virtual void RaiseEvent(int windowMessage) override;

	HRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static HRESULT ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	const char* text;
	Style style;
	HCURSOR handCursor;


	// Inherited via IParentable
	virtual void LoadChilds(HINSTANCE hInstance) override;
	virtual void AddChild(Element& rElement) override;
	virtual void RemoveChild(Element* target) override;
	virtual void RemoveChild(int index) override;
};

