#include "Label.h"
#include "Exception.h"

Label::Label(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align, int fontHeight,
	COLORREF background,
	COLORREF foreground,
	HFONT hFont)
	:
	text(text),
	backgroundColor(background),
	foregroundColor(foreground),
	fontHeight(fontHeight)
{

	if (width == AUTO || height == AUTO)
	{
		if (width == AUTO) width = ((12 * strlen(text) )* fontHeight) / 28;
		if (height == AUTO) height = fontHeight;
	}

	posX = x;
	posY = y;
	Label::width = width;
	Label::height = height;
	Label::align = align;
	Element::hParent = hParent;


	const char* className = "classLabel";
	WNDCLASSEX wc = {};


	auto r = GetClassInfoEx(hInstance, className, &wc);
	if (!r)
	{
		wc.lpszClassName = className;
		wc.hInstance = hInstance;
		wc.lpfnWndProc = ProcSetup;
		wc.hbrBackground = CreateSolidBrush(backgroundColor);
		wc.cbSize = sizeof(wc);
	}
	else
	{
		wc.hbrBackground = CreateSolidBrush(backgroundColor);
	}
	RegisterClassEx(&wc);
	
	hwnd = CreateWindowEx(
		0,
		className,
		"",
		WS_CHILD | style,
		posX,
		posY,
		width,
		height,
		hParent,
		NULL,
		hInstance,
		this);

	if (!hwnd)
	{
		ERROR_MESSAGE_LAST_ERROR();
	}

}

void Label::ChangeText(const char* newText)
{
	text = newText;
	width = width = ((12 * strlen(text)) * fontHeight);
	SetPosition(posX, posY, width, height, SWP_NOMOVE);
	Reload();
}

void Label::SetColor(COLORREF foregroud, COLORREF background)
{
	foregroundColor = foregroud;
	backgroundColor = background;
}

HWND Label::Show(HWND hParent, HINSTANCE hInstance)
{
	if (!hwnd) return 0;
	auto b = ShowWindow(hwnd, 10);
	if (align) Align(hParent);
	return hwnd;
}

LRESULT CALLBACK Label::ProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		Label* pLabel = static_cast<Label*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&Label::ProcStart);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pLabel);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Label::ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	Label* pLabel = reinterpret_cast<Label*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	return pLabel->MainProc(hwnd, uMsg, wParam, lParam);
}

LRESULT Label::MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
	
		PAINTSTRUCT ps = {};
		
		auto h = BeginPaint(hwnd, &ps);
		if (!hFont)
		{
			hFont = CreateFont(fontHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
				CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI")
			);
		}
		
		if (!backgroundColor)
		{
			HBRUSH brush = (HBRUSH)GetClassLongPtr(hParent, GCLP_HBRBACKGROUND);
			LOGBRUSH log;
			GetObject(brush, sizeof(log), &log);
			backgroundColor = log.lbColor;
		}

		SelectObject(h, hFont);
		SetTextColor(h, foregroundColor);
		SetBkColor(h, backgroundColor);
		TextOut(h, 0, 0, text, strlen(text));
		EndPaint(hwnd, &ps);
		break;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
