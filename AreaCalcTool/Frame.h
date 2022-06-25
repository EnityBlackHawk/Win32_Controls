#pragma once
#include "Element.h"
#include "Parentable.h"
#include <vector>
class Frame : public Element, public IParentable
{
public:
	Frame(int x, int y, int width, int height, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background);
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;
	virtual void OnSizeChanged(HWND hParent) override;

	// Inherited via IParentable
	virtual void LoadChilds(HINSTANCE hInstance) override;
	virtual void AddChild(Element& rElement) override;
	virtual void RemoveChild(Element* target) override;
	virtual void RemoveChild(int index) override;

private:
	COLORREF background;
};

