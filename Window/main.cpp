#include <Windows.h>

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


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


LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

	switch (msg) {

	case WM_DESTROY: {
		PostQuitMessage(0);
		break;
	}

	}
	return DefWindowProcW(hWnd, msg, wp, lp);
}