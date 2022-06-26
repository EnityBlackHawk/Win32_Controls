#pragma once
#include <windows.h>
#include "ICommandable.h"
#include "Frame.h"

class Button : public Element, public ICommandable, public IParentable
{
public:
	/// <summary>
	/// Create a button window
	/// </summary>
	/// <param name="text">Text</param>
	/// <param name="width">Button's width</param>
	/// <param name="height">Button's height</param>
	/// <param name="x">X position</param>
	/// <param name="y">Y position</param>
	/// <param name="align">Align type</param>
	/// <param name="fontSize">Font size in logical units</param>
	/// <param name="hParent">Parent's hwnd</param>
	/// <param name="hInstance">Application HINSTANCE</param>
	/// <param name="style">Style struct</param>
	Button(const char* text, int width, int height, int x, int y, unsigned char align, int fontSize, 
		HWND hParent, HINSTANCE hInstance, Style style);
	
	/// <summary>
	/// Set button text
	/// </summary>
	/// <param name="text">New text</param>
	void SetText(const char* text);
	

	/// <summary>
	/// Draw button
	/// </summary>
	/// <param name="hParent">Parent's hwnd</param>
	/// <param name="hInstance">Aplication HINSTANCE</param>
	/// <returns>Button's HWND</returns>
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

	/// <summary>
	/// Call an event
	/// </summary>
	/// <param name="windowMessage">Windows Message identifier</param>
	virtual void RaiseEvent(int windowMessage) override;

	HRESULT CALLBACK ButtonProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static HRESULT ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	const char* text;
	Style style;
	HCURSOR handCursor;
	int fontSize;


	// Inherited via IParentable
	virtual void LoadChilds(HINSTANCE hInstance) override;
	virtual void AddChild(Element& rElement) override;
	virtual void RemoveChild(Element* target) override;
	virtual void RemoveChild(int index) override;
};

