#include "Grid.h"

Grid::Grid(int x, int y, int width, int height, unsigned char align, HWND hParent, HINSTANCE hInstance)
{
}

HWND Grid::Show(HWND hParent, HINSTANCE hInstance)
{
    frames = (Frame**)malloc(rows.size() * sizeof(Frame*));
    for (int i = 0; i < rows.size(); i++)
    {
        frames[i] = (Frame*)malloc(columns.size() * sizeof(Frame));
    }

    for (int i = 0; i < rows.size(); i++)
    {
        for (int j = 0; j < columns.size(); j++)
        {
            
        }
    }
}

template<class I, class ...Args>
void Grid::DefineRow(I height, Args ...args)
{
    if (sizeof...(args) == 0) DefineRow(height);
    rows.push_back(height);
    DefineRow(args...);
}

template<class I>
void Grid::DefineRow(I height)
{
    rows.push_back(height);
}

template<class I, class ...Args>
void Grid::DefineColumn(I width, Args ...args)
{
    if (sizeof...(args) == 0) DefineColumn(width);
    columns.push_back(width);
    DefineColumn(args...);
}

template<class I>
void Grid::DefineColumn(I width)
{
    columns.push_back(width);
}
