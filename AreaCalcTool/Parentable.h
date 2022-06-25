#pragma once
#include <vector>
#include "Element.h"

class IParentable
{
public:
	virtual void LoadChilds(HINSTANCE hInstance) = 0;
	virtual void AddChild(Element& rElement) = 0;
	virtual void RemoveChild(Element* target) = 0;
	virtual void RemoveChild(int index) = 0;
protected:
	std::vector<Element*> elements;
};