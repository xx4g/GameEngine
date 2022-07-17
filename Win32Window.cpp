#include "pch.h"

Win32Window::Win32Window(HINSTANCE hInstance)
{
	WNDPROC WindowProcedure = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
		switch (message)                  /* handle the messages */
		{
		case WM_DESTROY:/* the window was destroyed */
			ExitProcess(
				0
			);
			break;
		default:                      /* for messages that we don't deal with */
			return DefWindowProc(hwnd, message, wParam, lParam);
		}
		return 0;
	};

	bool noError = true;
	while (noError)
	{
		auto wc = std::make_shared<WNDCLASSEX>();
		if (!wc)
		{
			noError = false;
			break;
		}
		//Step 1: Registering the Window Class
		wc->cbSize = sizeof(WNDCLASSEX);
		wc->style = 0;
		wc->lpfnWndProc = WindowProcedure;
		wc->cbClsExtra = 0;
		wc->cbWndExtra = 0;
		wc->hInstance = hInstance;
		wc->hIcon = LoadIcon(hInstance, NULL);
		wc->hCursor = LoadCursor(NULL, IDC_ARROW);
		wc->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc->lpszMenuName = NULL;
		wc->lpszClassName = L"Win32WindowClass";
		wc->hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (!RegisterClassEx(wc.get()))
		{
			MessageBox(NULL, L"Window Registration Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			noError = false;
			break;
		}

		// Step 2: Creating the Window
		hwnd = CreateWindowEx(
			WS_EX_CLIENTEDGE,
			L"Win32WindowClass",
			L"Game Engine",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 500, 500,
			NULL, NULL, hInstance, NULL);

		if (hwnd == NULL)
		{
			MessageBox(NULL, L"Window Creation Failed!", L"Error!",
				MB_ICONEXCLAMATION | MB_OK);
			noError = false;
			break;
		}

		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
		break;
	};
}

const HWND Win32Window::GetHwnd()
{
	return hwnd;
}
