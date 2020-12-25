#include <Windows.h>

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

#define MB_ITEM_1 1
#define MB_ITEM_2 2
#define MB_ITEM_3 3
#define MB_ITEM_4 4
#define MB_ITEM_5 5

HMENU Menubar;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	WNDCLASSW wc = { 0 };
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"MainWndClass";
	wc.lpfnWndProc = MainWindowProc;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(
		L"MainWndClass", L"Window Title",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		400, 200, 500, 250, 
		NULL, NULL, NULL, NULL
	);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

void CreateMenu(HWND hWnd) {

	Menubar = CreateMenu(); //Create the menu

	//First menu
	HMENU FirstMenu = CreateMenu(); //Create first menuentry
	HMENU FirstSubMenu = CreateMenu(); //Create submenu

	//Second menu
	HMENU SecondMenu = CreateMenu(); //Create first menuentry

	//First menu entry with submenu
	AppendMenu(Menubar, MF_POPUP, (UINT_PTR)FirstMenu, "First"); //Add main menuentry
	AppendMenu(FirstMenu, MF_STRING, MB_ITEM_1, "Item 1"); //Add item with name "Item 1"
	AppendMenu(FirstMenu, MF_POPUP, (UINT_PTR)FirstSubMenu, "SubMenu"); //Create the submenu
	AppendMenu(FirstSubMenu, MF_STRING, MB_ITEM_2, "Item 2"); //Add item to submenu with name "Item 2"
	AppendMenu(FirstMenu, MF_SEPARATOR, NULL, NULL); //Add a separator
	AppendMenu(FirstMenu, MF_STRING, MB_ITEM_3, "Item 3"); //Add item with name "Item 3"

	//Second menu entry
	AppendMenu(Menubar, MF_POPUP, (UINT_PTR)SecondMenu, "Second"); //Add main menuentry
	AppendMenu(SecondMenu, MF_CHECKED, MB_ITEM_4, "Item 4"); //Add checked item
	AppendMenu(SecondMenu, MF_SEPARATOR, NULL, NULL); //Add a separator
	AppendMenu(SecondMenu, MF_GRAYED, NULL, "Item 5"); //Add grayed item
	
	SetMenu(hWnd, Menubar);
}


LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

	case WM_COMMAND: { //Messagehandle for menuclick
		switch (wp)
		{
		case MB_ITEM_1: {
			MessageBox(hWnd, "Item 1", "", MB_OK);
			break;
		}
		case MB_ITEM_2: {
			MessageBox(hWnd, "Item 2", "", MB_OK);
			break;
		}
		case MB_ITEM_3: {
			MessageBox(hWnd, "Item 3", "", MB_OK);
			break;
		}
		case MB_ITEM_4: {
			MessageBox(hWnd, "Item 4", "", MB_OK);
			break;
		}
		}
	}

	case WM_CREATE: {
		CreateMenu(hWnd); //Call CreateMenu function
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	}
	return DefWindowProcW(hWnd, msg, wp, lp);
}
