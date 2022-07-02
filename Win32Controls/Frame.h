#pragma once
#include "Element.h"
#include "Parentable.h"
#include <vector>
class Frame : public Element, public IParentable
{
public:
	/// <summary>
	/// Create a frame window
	/// </summary>
	/// <param name="x">Postion x</param>
	/// <param name="y">Position y</param>
	/// <param name="width">Frame width</param>
	/// <param name="height">Frame height</param>
	/// <param name="alignment">Align type</param>
	/// <param name="hParent">Parent's hwnd</param>
	/// <param name="hInstance">Applicarion HINSTANCE</param>
	/// <param name="style">Style struct</param>
	Frame(int x, int y, int width, int height, unsigned char alignment, HWND hParent, 
		HINSTANCE hInstance, Style style);
	~Frame()
	{
		OutputDebugString("Frame deleted\n");
	}

	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;
	virtual void OnSizeChanged(HWND hParent) override;

	// Inherited via IParentable
	virtual void LoadChilds(HINSTANCE hInstance) override;
	virtual void AddChild(Element& rElement) override;
	virtual void RemoveChild(Element* target) override;
	virtual void RemoveChild(int index) override;

private:
	Style style;
};

