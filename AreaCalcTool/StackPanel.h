#pragma once
#include "Frame.h"

class StackPanel :
    public Frame
{
public:
    StackPanel(Frame&&);
    StackPanel(int x, int y, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background);
    virtual void LoadChilds(HINSTANCE hInstance) override;
};

