#pragma once
#include <Windows.h>
#include "Element.h"
#include <vector>
#include "Frame.h"

class Grid : public Element
{
public:
	Grid(int x, int y, int width, int height, unsigned char align, HWND hParent, HINSTANCE hInstance);
	
	template<class I, class... Args>
	void DefineRow(I height, Args... args);
	template<class I>
	void DefineRow(I height);

	template<class I, class... Args>
	void DefineColumn(I width, Args... args);
	template<class I>
	void DefineColumn(I width);

	// Inherited via Element
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

private:
	std::vector<int> rows;
	std::vector<int> columns;
	Frame** frames;
};