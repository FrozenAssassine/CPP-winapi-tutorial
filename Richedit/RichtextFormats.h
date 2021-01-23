#pragma once


typedef struct Zoom {
	int numerator = 0;
	int denominator = 0;
};

void InsertTextToRichedit(HWND hWindow, LPCSTR szString)
{
	const TCHAR *c = szString;
	while (*c)
	{
		SendMessage(hWindow, WM_CHAR, *c, 0);
		c++;
	}
}

void SetFont(HWND hWindow, const char * Font) {
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof cf);
	cf.cbSize = sizeof cf;
	cf.dwMask = CFM_FACE;
	wsprintf(cf.szFaceName, Font);
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void FontSize(HWND hWindow, int size) {
	CHARFORMAT2 cf;
	memset(&cf, 0, sizeof cf);
	cf.cbSize = sizeof cf;
	cf.dwMask = CFM_SIZE;
	cf.yHeight = size * 20;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void replace_sel(HWND hWindow, const char* str) {
	SendMessage(hWindow, EM_REPLACESEL, 0, (LPARAM)str);
}

void Subscript(HWND hWindow) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFE_SUBSCRIPT;
	cf.dwEffects = CFE_SUBSCRIPT;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void Superscript(HWND hWindow) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_SUPERSCRIPT;
	cf.dwEffects = CFM_SUPERSCRIPT;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void colorseltext(HWND hWindow, COLORREF clr) {
	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = clr;
	cf.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void changeBackColor(HWND hWindow, COLORREF clr) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_BACKCOLOR;
	cf.crBackColor = clr;
	cf.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void NoBackColor(HWND hWindow) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwCookie = (DWORD)hWindow;
	cf.dwMask = CFM_BACKCOLOR;
	cf.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void txtBold(HWND hWindow) {
	CHARFORMAT boldfont;
	boldfont.cbSize = sizeof(CHARFORMAT);
	boldfont.dwMask = CFM_BOLD;
	boldfont.dwEffects = CFE_BOLD;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&boldfont);
}

void txtUnderlined(HWND hWindow) {
	CHARFORMAT2 underlinedfont;
	underlinedfont.cbSize = sizeof(CHARFORMAT);
	underlinedfont.dwMask = CFM_UNDERLINE;
	underlinedfont.dwEffects = CFM_UNDERLINE;

	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&underlinedfont);
}

void txtFmtReset(HWND hWindow) {
	CHARFORMAT2 reset;
	reset.cbSize = sizeof(CHARFORMAT);
	reset.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFM_SUPERSCRIPT | CFM_STRIKEOUT | CFM_COLOR | CFM_BACKCOLOR;
	reset.dwEffects = 1140850688;
	reset.crBackColor =
		reset.crTextColor = RGB(0, 0, 0);
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&reset);
}

void ResetSuperSubscript(HWND hWindow) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_SUPERSCRIPT | CFM_SUBSCRIPT;
	cf.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
}

void txtItalic(HWND hWindow) {
	CHARFORMAT Kursivfont;
	Kursivfont.cbSize = sizeof(CHARFORMAT);
	Kursivfont.dwMask = CFM_ITALIC;
	Kursivfont.dwEffects = CFM_ITALIC;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&Kursivfont);
}

void txtStrikeout(HWND hWindow) {
	CHARFORMAT underlinedfont;
	underlinedfont.cbSize = sizeof(CHARFORMAT);
	underlinedfont.dwMask = CFM_STRIKEOUT;
	underlinedfont.dwEffects = CFM_STRIKEOUT;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&underlinedfont);
}

void txtResetItalic(HWND hWindow) {
	CHARFORMAT reset;
	reset.cbSize = sizeof(CHARFORMAT);
	reset.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFU_UNDERLINEWAVE;

	reset.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&reset);
}

void txtResetBold(HWND hWindow) {
	CHARFORMAT reset;
	reset.cbSize = sizeof(CHARFORMAT);
	reset.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE | CFU_UNDERLINEWAVE;
	reset.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&reset);
}

void txtResetUnderlined(HWND hWindow) {
	CHARFORMAT reset;
	reset.cbSize = sizeof(CHARFORMAT);
	reset.dwMask = CFM_BOLD | CFM_ITALIC | CFM_UNDERLINE;
	reset.dwEffects = 0;
	SendMessage(hWindow, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&reset);
}

void scroll_to(HWND hWindow, DWORD pos) {
	SendMessage(hWindow, WM_VSCROLL, pos, 0);
}

DWORD ChooseCLR() {
	CHOOSECOLOR cc;
	static COLORREF acrCustClr[32];
	HBRUSH hbrush;
	static DWORD rgbCurrent;

	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = NULL;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE) {
		hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult;
		return rgbCurrent;
	}
	else {
		return 1111111111;
	}
}

void SetZoom(HWND hWindow, Zoom zoom) {
	SendMessage(hWindow, EM_SETZOOM, zoom.numerator, zoom.denominator);
}

Zoom GetZoom(HWND hWindow) {
	Zoom wndz;
	SendMessage(hWindow, EM_GETZOOM, (WPARAM)&wndz.numerator, (LPARAM)&wndz.denominator);
	return wndz;
}

LPCSTR GetFont(HWND hWindow) {
	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = 0xffffffff;

	SendMessage(hWindow, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

	char out[1000];
	wsprintf(out, "%s", cf.szFaceName);
	return cf.szFaceName;
}

LPCSTR GetFontSize(HWND hWindow) {
	CHARFORMAT cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = 0xffffffff;

	SendMessage(hWindow, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);

	char out[1000];
	wsprintf(out, "%d", cf.yHeight / 20);
	return out;
}

DWORD GetColor(HWND hWindow) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = 0xffffffff;

	SendMessage(hWindow, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	return cf.crTextColor;
}

DWORD GetBackColor(HWND hWindow) {
	CHARFORMAT2 cf;
	cf.cbSize = sizeof(cf);
	cf.dwEffects = 0xffffffff;

	SendMessage(hWindow, EM_GETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	return cf.crBackColor;
}
