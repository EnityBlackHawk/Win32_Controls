#include "TextBox.h"
#include "Exception.h"


TextBox::TextBox(const char* text, int x, int y, int width, int height, HWND hParent, HINSTANCE hInstance, unsigned char align, Style style):
	style(style)
{
	Element::width = width;
	Element::height = height;
	Element::posX = x;
	Element::posY = y;
	Element::hParent = hParent;
	Element::align = align;

	const char* className = "classTextBox";
	WNDCLASSEX wc = {};

	BOOL r = GetClassInfoEx(hInstance, className, &wc);
	if (!r)
	{
		wc.lpszClassName = className;
		wc.hInstance = hInstance;
		wc.lpfnWndProc = ProcSetup;
		wc.hbrBackground = NULL;
		wc.cbSize = sizeof(wc);
	}
	RegisterClassEx(&wc);
	
	hwnd = CreateWindowEx(
		0,
		className,
		"",
		WS_CHILD,
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
		return;
	}

	hEdit = CreateWindowEx(
		NULL,
		"EDIT",
		"",
		WS_CHILD,
		5, 
		5,
		width - 10,
		height - 10,
		hwnd,
		NULL,
		hInstance,
		NULL
	);
	if (!hEdit)
	{
		ERROR_MESSAGE_LAST_ERROR();
	}

}

std::string TextBox::GetText() const
{
	int length = SendMessage(hEdit, WM_GETTEXTLENGTH, NULL, NULL);
	char* vText = (char*) malloc((length + 1) * sizeof(char));
	SendMessage(hEdit, WM_GETTEXT, (WPARAM)((length + 1) * sizeof(char)), (LPARAM)vText);
	return std::string(vText);
}


HWND TextBox::Show(HWND hParent, HINSTANCE hInstance)
{
	if (!hwnd) return 0;
	ShowWindow(hwnd, 10);
	ShowWindow(hEdit, 10);
	if (align) Align(hParent);
	return hwnd;
}

LRESULT TextBox::ProcSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		TextBox* pTextbox = reinterpret_cast<TextBox*>(cs->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)&TextBox::ProcStart);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pTextbox);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT TextBox::ProcStart(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TextBox* pTextBox = reinterpret_cast<TextBox*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	return pTextBox->MainProc(hwnd, uMsg, wParam, lParam);
}

LRESULT TextBox::MainProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (commands.contains(uMsg)) RaiseEvent(uMsg);

	switch (uMsg)
	{
	case WM_PAINT:
	{
		HFONT font = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Segoe UI")
		);
		PAINTSTRUCT ps = {};
		HDC hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, CreateSolidBrush(style.background));

		if (style.borderColor)
		{
			HPEN hp = CreatePen(PS_SOLID, style.borderThickness, style.borderColor);
		}
		
		RoundRect(hdc, 0, 0, width, height, style.cornerRadius, style.cornerRadius);

		EndPaint(hwnd, &ps);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)font, TRUE);
		break;
	}
	case WM_CTLCOLOREDIT:
	{
		if ((HWND)lParam == hEdit)
		{
			HDC hdc = (HDC)wParam;
			SetTextColor(hdc, style.foreground);
			SetBkColor(hdc, style.background);
			return NULL;
		}
		break;
	}
	case WM_COMMAND:
	{
		if ((HWND)lParam == hEdit)
		{
			if (HIWORD(wParam) == EN_CHANGE)
			{
				
			}
		}
	}

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void TextBox::RaiseEvent(int windowMessage)
{
	if (commands.size() != 0)
		commands[windowMessage](this);
}
