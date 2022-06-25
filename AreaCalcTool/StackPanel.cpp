#include "StackPanel.h"
StackPanel::StackPanel(Frame&& frame):
	Frame(frame)
{
}

StackPanel::StackPanel(int x, int y, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background):
	Frame(x, y, 0, 0, alignment, hParent, hInstance, {0, background})
{
}

void StackPanel::LoadChilds(HINSTANCE hInstance)
{

	int y = 0;
	int x = 0;
	for (auto e : elements)
	{
		int eX = 0;

		if (x != 0 && e->GetAlign() == ALIGN_CENTER && e->GetWidth() < x)
		{
			eX = (e->GetWidth() / 2);
		}

		e->SetAlign(0);
		e->SetPosition(e->margin.left + eX, y + e->margin.top, e->GetWidth(), e->GetHeight(), 0);
		e->Show(hwnd, hInstance);
		
		
		x = e->GetWidth() > x ? e->GetWidth() : x;
		y += e->GetHeight() + e->margin.top + e->margin.bottom;
	}
	SetPosition(0, 0, x, y, SWP_NOMOVE);
}

