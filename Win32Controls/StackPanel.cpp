#include "StackPanel.h"
#include "Exception.h"
StackPanel::StackPanel(Frame&& frame):
	Frame(frame)
{
}

StackPanel::StackPanel(int x, int y, int width, int height, unsigned char alignment, HWND hParent, HINSTANCE hInstance, Style style,
	unsigned char orientation)
	:
	Frame(x, y, width, height, alignment, hParent, hInstance, {0, style.background}),
	orientation(orientation)
{
}

void StackPanel::LoadChilds(HINSTANCE hInstance)
{
	int y = 0;
	int x = 0;

	if (orientation == VERTICAL)
	{

		if (!width)
		{
			for (auto e : elements)
			{
				x = e->GetWidth() > x ? e->GetWidth() : x;
			}
		}
		else x = width;
		

		for (auto e : elements)
		{
			int eX = 0;

			if (e->GetAlign() == ALIGN_CENTER && e->GetActualWidth() < x)
			{
				eX = (x / 2) - (e->GetWidth() / 2);
			}

			e->SetAlign(0);
			e->SetPosition(e->margin.left + eX, y + e->margin.top, e->GetWidth(), e->GetHeight(), 0);
			e->Show(hwnd, hInstance);


			y += e->GetHeight() + e->margin.top + e->margin.bottom;
		}
	}

	else if (orientation == HORIZONTAL)
	{
		if (!height)
		{
			for (auto e : elements)
				y = e->GetHeight() > y ? e->GetHeight() : y;
		}
		else y = height;
		

		for (auto e : elements)
		{
			int eY = 0;

			if (e->GetAlign() == ALIGN_CENTER && e->GetActualHeight() < y)
			{
				eY = (y / 2) - (e->GetHeight() / 2);
			}

			e->SetAlign(0);
			e->SetPosition(e->margin.left + x, e->margin.top + eY, e->GetWidth(), e->GetHeight(), 0);
			e->Show(hwnd, hInstance);


			x += e->GetWidth() + e->margin.left + e->margin.right;
		}
	
	}

	x = (width == NULL || width == AUTO) ? x : width;
	y = (height == NULL || height == AUTO) ? y : height;
	SetPosition(0, 0, x, y, SWP_NOMOVE);
}

