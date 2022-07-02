#pragma once
#include <Windows.h>
#include "Element.h"
#include <vector>
#include "Frame.h"
#include <queue>

class Grid : public Element
{

public:
	/// <summary>
	/// Create a grid window
	/// </summary>
	/// <param name="x">position on coordenate x</param>
	/// <param name="y">Position on coordenate y</param>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="align"> Align type</param>
	/// <param name="hParent"> Parent's HWND</param>
	/// <param name="hInstance"> Application HINSTANCE</param>
	/// <param name="frameStyle> Style applied to grid's internal frame</param>
	Grid(int x, int y, int width, int height, unsigned char align, HWND hParent, HINSTANCE hInstance, Style frameStyle = {});
	
	/// <summary>
	/// Add a row definition
	/// </summary>
	/// <param name="width">Height of the row</param>
	/// <param name="...args">Height of the rows</param>
	template<class I, class ...Args>
	void DefineRow(I height, Args ...args)
	{
		if (sizeof...(args) == 0) DefineRow(height);
		rows.push_back(height);
		DefineRow(args...);
	}

	/// <summary>
	/// Add a row definition
	/// </summary>
	/// <typeparam name="I">Integer type</typeparam>
	/// <param name="width">Height of the row</param>
	template<class I>
	void DefineRow(I height)
	{
		rows.push_back(height);
	}
	/// <summary>
	/// Add a column definition
	/// </summary>
	/// <param name="width">Width of the column</param>
	/// <param name="...args">Width of the column</param>
	template<class I, class ...Args>
	void DefineColumn(I width, Args ...args)
	{
		if (sizeof...(args) == 0) DefineColumn(width);
		columns.push_back(width);
		DefineColumn(args...);
	}
	/// <summary>
	/// Add a column definition
	/// </summary>
	/// <param name="width">Width of the column</param>
	template<class I>
	void DefineColumn(I width)
	{
		columns.push_back(width);
	}

	/// <summary>
	/// Add element into the grid
	/// </summary>
	/// <param name="element"> Element reference</param>
	/// <param name="row"> Row index</param>
	/// <param name="column"> Column index</param>
	void AddElement(Element& element, int row, int column);

	/// <summary>
	/// Get the frame of the coordenate
	/// </summary>
	/// <param name="row"> Row index</param>
	/// <param name="column"> Column index</param>
	Frame& GetFrame(int row, int column);
	void GenerateGrid();

	// Inherited via Element
	virtual HWND Show(HWND hParent, HINSTANCE hInstance) override;

private:


	void ResizeFrames();
	void RecalculateAuto();

	static LRESULT CALLBACK DummyProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HINSTANCE hInstance;
	Style frameStyle;
	std::vector<int> rows;
	std::vector<int> columns;
	std::vector<Frame> vFrames;
	int** framesIndex;
};

#define GET_GRID_HWND(gridInstance, row, column) gridInstance.GetFrame(row, column).GetHwnd()