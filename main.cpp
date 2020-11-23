#include <Windows.h>

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

#define BTN_1 1
#define BTN_2 2
#define CHECKBOX_1 10
#define RADIOBTN_1 50

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
		L"MainWndClass", L"Buttons",
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


void AddButton(HWND hWnd) {

	CreateWindow(
		"Button", //Button class
		"First Button", //Button text
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //Styles
		50, //xpos
		50, //ypos
		100, //xsize
		25, //ysize
		hWnd, //hWnd window
		(HMENU)BTN_1, //Sending a message on buttonclick
		NULL,
		NULL
	);

	CreateWindow(
		"Button", //Button class
		"Second Button", //Button text
		WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, //Styles
		50, //xpos
		100, //ypos
		100, //xsize
		25, //ysize
		hWnd, //hWnd window
		(HMENU)BTN_2, //Sending a message on buttonclick
		NULL,
		NULL
	);

}
void Checkbutton(HWND hWnd) {

	CreateWindow(
		"Button", //Button class
		"Checkbox", //Button text
		WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, //Styles
		50, //xpos
		150, //ypos
		100, //xsize
		25, //ysize
		hWnd, //hWnd window
		(HMENU)CHECKBOX_1, //Sending a message on buttonclick
		NULL,
		NULL
	);
}
void RadioButton(HWND hWnd) {

	CreateWindow(
	"Button",
	"Radiobutton",
	WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON,
	50,
	10,
	120,
	25, 
	hWnd,
	(HMENU)RADIOBTN_1, 
	NULL,
	NULL
	);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

	case WM_COMMAND: {
		switch (wp)
		{
		case BTN_1: {
			MessageBox(hWnd, "Button 1 pressed", "Clickevent", MB_OK); 
			//This will display a messagebox on the hWnd window with the text Button 1 Pressed and the headline Clickevent with an ok button

			break;
		}
		case BTN_2: {
			MessageBox(hWnd, "Button 2 pressed", "Clickevent", MB_OK);
			break;
		}
		case CHECKBOX_1: {
			MessageBox(hWnd, "Checkbox checked", "Clickevent", MB_OK);
			break;
		}
		case RADIOBTN_1: {
			MessageBox(hWnd, "Radiobutton clicked", "Clickevent", MB_OK);
			break;
		}
		default:
			break;
		}
		break;
	}

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}
	case WM_CREATE: {
		AddButton(hWnd);
		Checkbutton(hWnd);
		RadioButton(hWnd);
		break;
	}

	}
	return DefWindowProcW(hWnd, msg, wp, lp);
}