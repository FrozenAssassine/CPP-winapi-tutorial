#include <Windows.h> //Load the Windows.h
#include <richedit.h> //Load the richedit.h
#include "RichtextFormats.h"

#define POPUPMENU_COLORRED 1
#define POPUPMENU_COLORGREEN 2
#define POPUPMENU_COLORBLUE 3
#define POPUPMENU_BACKRED 4
#define POPUPMENU_BACKGREEN 5
#define POPUPMENU_BACKBLUE 6
#define POPUPMENU_BOLD 7
#define POPUPMENU_ITALIC 8
#define POPUPMENU_UNDERLINED 9
#define POPUPMENU_STRIKEOUT 10

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
LRESULT CALLBACK RicheditProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

HWND hRichEdit;
LONG_PTR PrevRichEditProc;

bool ctrlkey = false;

//Create a font for the richedit; You can also use the default
HFONT Font1 = CreateFont(28, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
	OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE, TEXT("Calibri"));

void loadlibs() {
	HINSTANCE relib = LoadLibrary("msftedit.dll");  //Make sure the dll is under C:\Windows\SysWow64 or in the path of your project .exe
	if (relib == NULL) {
		MessageBox(NULL, "Missing msftedit.dll", "Error", MB_ICONEXCLAMATION | MB_OK);
		PostQuitMessage(0);
	}
}

void AddRichedit(HWND hWindow) {
	//Create the Richedit
	hRichEdit = CreateWindowEx(0, "RICHEDIT50W", TEXT(""),
		ES_AUTOVSCROLL | ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | WS_VSCROLL,
		0, 0, 0, 0,
		hWindow, NULL, NULL, NULL);

	//Add a windowprocedure to the richedit to get keyboard and mouse input
	PrevRichEditProc = SetWindowLongPtr(hRichEdit, GWLP_WNDPROC,
		(LONG_PTR)RicheditProcedure);

	SendMessage(hRichEdit, EM_SETLIMITTEXT, -1, 0);
	SendMessage(hRichEdit, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0)); //set the font of the richedit
	SendMessage(hRichEdit, EM_SETZOOM, 1, 1); //Numerator, denumerator; Sample: 1 , 2 = half zoom; 2, 1 = doubled zoom
}

void RichEditPopUpMenu(LPARAM lp, HWND hWindow) {
	POINT point;
	point.x = LOWORD(lp);
	point.y = HIWORD(lp);

	HMENU hPOPMenu = CreatePopupMenu();
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_COLORRED, "For-Red");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_COLORGREEN, "For-Green");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_COLORBLUE, "For-Blue");
	AppendMenu(hPOPMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_BACKRED, "Back-Red");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_BACKGREEN, "Back-Green");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_BACKBLUE, "Back-Blue");
	AppendMenu(hPOPMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_BOLD, "Bold");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_ITALIC, "Italic");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_UNDERLINED, "Underlined");
	AppendMenu(hPOPMenu, MF_STRING, POPUPMENU_STRIKEOUT, "Strikeout");

	ClientToScreen(hWindow, &point);

	TrackPopupMenu(hPOPMenu, TPM_RIGHTBUTTON, point.x, point.y, 0, hWindow, NULL);
	DestroyMenu(hPOPMenu);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"MainWndClass";
	wc.lpfnWndProc = MainWindowProc;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindow(
		"MainWndClass", "Editor - Rightclick for more!",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		400, 200, 500, 300,
		NULL, NULL, NULL, NULL
	);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{

	case WM_CREATE: {
		loadlibs(); //Call the loadlibs function to load the richedit32.dll bevore we create the richedit
		AddRichedit(hWnd); //Call the AddRichedit function to create the Richedit
		break;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		break;
	}
	case WM_SIZE: { //On windowresizing
		MoveWindow(hRichEdit, 0, 0, LOWORD(lp), HIWORD(lp), TRUE);
		break;
	}
	}
	return DefWindowProcW(hWnd, msg, wp, lp);
}

LRESULT CALLBACK RicheditProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg)
	{

	case WM_COMMAND: {
		switch (wp)
		{
		case POPUPMENU_COLORRED: {
			colorseltext(hRichEdit, RGB(255, 0, 0));
			break;
		}
		case POPUPMENU_COLORGREEN: {
			colorseltext(hRichEdit, RGB(0, 255, 0));
			break;
		}
		case POPUPMENU_COLORBLUE: {
			colorseltext(hRichEdit, RGB(0, 0, 255));
			break;
		}
		case POPUPMENU_BACKRED: {
			changeBackColor(hRichEdit, RGB(255, 0, 0));
			break;
		}		
		case POPUPMENU_BACKGREEN: {
			changeBackColor(hRichEdit, RGB(0, 255, 0));
			break;
		}		
		case POPUPMENU_BACKBLUE: {
			changeBackColor(hRichEdit, RGB(0, 0, 255));
			break;
		}
		case POPUPMENU_BOLD: {
			txtBold(hRichEdit);
			break;
		}
		case POPUPMENU_ITALIC: {
			txtItalic(hRichEdit);
			break;
		}
		case POPUPMENU_STRIKEOUT: {
			txtStrikeout(hRichEdit);
			break;
		}
		case POPUPMENU_UNDERLINED: {
			txtUnderlined(hRichEdit);
			break;
		}
		}
		break;
	}
	case WM_RBUTTONDOWN: { //if right mousebutton down
		RichEditPopUpMenu(lp, hWnd); //Call the Popupmenu function
		break;
	}
	case WM_KEYDOWN: { //Keydown event
		if (wp == VK_CONTROL) { //if controlkey is pressed
			ctrlkey = true; //set controlkey to true
		}
		if (wp == 'B' && ctrlkey == true) { //if key "D" pressed and ctrlkey pressed:
			txtBold(hRichEdit);
			ctrlkey = false;
		}
		break;
	}
	case WM_KEYUP: { //Keyup event
		if (wp == VK_CONTROL) {
			ctrlkey = false;
		}
		break;
	}
	
	}
	return CallWindowProc((WNDPROC)PrevRichEditProc, hWnd, msg, wp, lp);
}


