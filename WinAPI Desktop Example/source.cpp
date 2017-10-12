#include <windows.h> 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND task, textfield1, textfield2, namefield, button;
char text[50];

int WINAPI WinMain(HINSTANCE hInst,
	HINSTANCE hPrevInst,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	TCHAR szClassName[] = L"Мой класс";
	HWND hMainWnd;
	HWND hSecondWnd;
	MSG msg;
	WNDCLASSEX wc;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.cbWndExtra = NULL;
	wc.cbClsExtra = NULL;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.hInstance = hInst;
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Не получилось зарегистрировать класс!", L"Ошибка", MB_OK);
		return NULL;
	}
	hMainWnd = CreateWindow(
		szClassName,
		L"String copy",
		WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		NULL,
		500,
		300,
		(HWND)NULL,
		NULL,
		HINSTANCE(hInst),
		NULL);
	if (!hMainWnd) {
		MessageBox(NULL, L"Не получилось создать окно!", L"Ошибка", MB_OK);
		return NULL;
	}

	ShowWindow(hMainWnd, nCmdShow);
	UpdateWindow(hMainWnd);
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	PAINTSTRUCT ps;
	switch (uMsg) {

	case WM_CREATE:

		task = CreateWindow(
			L"STATIC",
			L"Введите строку",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			180, 40, 140, 20,
			hWnd, NULL, NULL, NULL);

		textfield1 = CreateWindow(
			L"EDIT",
			NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			20, 80, 350, 20,
			hWnd, NULL, NULL, NULL);

		textfield2 = CreateWindow(
			L"STATIC",
			NULL,
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			20, 110, 350, 20,
			hWnd, NULL, NULL, NULL);

		button = CreateWindow(
			L"Button",
			L"Copy",
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			380, 80, 80, 50,
			hWnd, (HMENU)1, NULL, NULL);

		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 1:
			int gwt = 0, swt = 0;
			gwt = GetWindowTextA(textfield1, text, 50);
			swt = SetWindowTextA(textfield2, text);

			//Reverse algorithm

			/*
			WCHAR str[10];
			GetWindowText(textfield1, str, 50);

			int len = 10;

			for (int i = 0; i<len / 2; i++)
			{
				WCHAR t = str[i];
				str[i] = str[len - i - 1];
				str[len - i - 1] = t;
			}

			SetWindowText(textfield2, str);
			*/

			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return NULL;
}