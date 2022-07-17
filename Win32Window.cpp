#include "pch.h"

Win32Window::Win32Window(HINSTANCE hInstance)
{
	WNDPROC WindowProcedure = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) -> LRESULT {
		

		switch (message)                  /* handle the messages */
		{
		case WM_CREATE:
			if (SetTimer(hwnd, 1, 33, NULL) == 0)
			{
				MessageBox(hwnd, L"Could not SetTimer()!", L"Error", MB_OK | MB_ICONEXCLAMATION);
				return FALSE;
			}
		break;
		case WM_ERASEBKGND:
		{
			return TRUE;
		}
		break;
		case WM_TIMER:
		{
			SendMessage(hwnd, WM_PAINT, wParam, lParam);
		}
		break;
		case WM_PAINT:
			{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

			RECT mRect;
			GetClientRect(hwnd, &mRect);
			HBRUSH bkBrush = CreateSolidBrush(RGB(100, 100, 100));
			FillRect(hdc, &mRect, bkBrush);

			int col = ((100 ) * 255) / 100.0;
			HBRUSH circleBrush = CreateSolidBrush(RGB(col, 0, 0)), oldBrush;
			oldBrush = (HBRUSH)SelectObject(hdc, circleBrush);
			Ellipse(hdc, mRect.left, mRect.top, mRect.right, mRect.bottom);
			SelectObject(hdc, oldBrush);

			DeleteObject(bkBrush);
			DeleteObject(circleBrush);

			EndPaint(hwnd, &ps);
			}
			break;
		case WM_DESTROY:/* the window was destroyed */
			KillTimer(hwnd, 1);
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
		auto resIcon = MAKEINTRESOURCE(IDI_ICON1);
		//Step 1: Registering the Window Class
		wc->cbSize = sizeof(WNDCLASSEX);
		wc->style = CS_HREDRAW | CS_VREDRAW;
		wc->lpfnWndProc = WindowProcedure;
		wc->cbClsExtra = 0;
		wc->cbWndExtra = 0;
		wc->hInstance = hInstance;
		wc->hIcon = LoadIcon(hInstance, resIcon);
		wc->hCursor = LoadCursor(NULL, IDC_ARROW);
		wc->hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wc->lpszMenuName = NULL;
		wc->lpszClassName = L"Win32WindowClass";
		wc->hIconSm = LoadIcon(wc->hInstance, resIcon);

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
