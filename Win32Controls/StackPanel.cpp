#include "StackPanel.h"
#include "Exception.h"
StackPanel::StackPanel(Frame&& frame):
	Frame(frame)
{
}

StackPanel::StackPanel(int x, int y, int width, int height, unsigned char alignment, HWND hParent, HINSTANCE hInstance, COLORREF background,
	unsigned char orientation)
	:
	Frame(x, y, width, height, alignment, hParent, hInstance, {0, background}),
	orientation(orientation)
{
}

void StackPanel::LoadChilds(HINSTANCE hInstance)
{
	int y = 0;
	int x = 0;

	if (orientation == VERTICAL)
	{
		for (auto e : elements)
		{
			x = e->GetWidth() > x ? e->GetWidth() : x;
		}

		for (auto e : elements)
		{
			int eX = 0;

			if (e->GetAlign() == ALIGN_CENTER && e->GetActualWidth() < x)
			{
				eX = (e->GetWidth() / 2);
			}

			e->SetAlign(0);
			e->SetPosition(e->margin.left + eX, y + e->margin.top, e->GetWidth(), e->GetHeight(), 0);
			e->Show(hwnd, hInstance);


			y += e->GetHeight() + e->margin.top + e->margin.bottom;
		}
	}

	else if (orientation == HORIZONTAL)
	{
		ERROR_MESSAGE("Horizontal stackpanel not implemented");
	}

	x = (width == NULL || width == AUTO) ? x : width;
	y = (height == NULL || height == AUTO) ? y : height;
	SetPosition(0, 0, x, y, SWP_NOMOVE);
}

