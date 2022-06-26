#pragma once
#include "Frame.h"

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
    /// <param name="alignment">Align type</param>
    /// <param name="hParent">Parent's HWND</param>
    /// <param name="hInstance">Application HINSTANCE</param>
    /// <param name="background">Backgournd COLORREF</param>
    StackPanel(int x, int y, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background);
    /// <summary>
    /// Draw childs
    /// </summary>
    /// <param name="hInstance">Application HINSTANCE</param>
    virtual void LoadChilds(HINSTANCE hInstance) override;
};

