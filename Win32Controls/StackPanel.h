#pragma once
#include "Frame.h"

#define HORIZONTAL 0
#define VERTICAL 1

class StackPanel :
    public Frame
{
public:
    /// <summary>
    /// Create a StackPanel window
    /// </summary>
    /// <param name="">Frame ivalue</param>
    StackPanel(Frame&&);
    /// <summary>
    /// Create a StackPanel window
    /// </summary>
    /// <param name="x">X position</param>
    /// <param name="y">Y position</param>
    /// <param name="width"> AUTO/NULL to streach</param>
    /// <param name="height"> AUTO/NULL to streach</param>
    /// <param name="alignment">Align type</param>
    /// <param name="hParent">Parent's HWND</param>
    /// <param name="hInstance">Application HINSTANCE</param>
    /// <param name="background">Backgournd COLORREF</param>
    StackPanel(int x, int y, int width, int height, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background,
        unsigned char orientation = VERTICAL);
    /// <summary>
    /// Draw childs
    /// </summary>
    /// <param name="hInstance">Application HINSTANCE</param>
    virtual void LoadChilds(HINSTANCE hInstance) override;

private:
    unsigned char orientation;
};

