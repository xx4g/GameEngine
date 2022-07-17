#pragma once
class Win32Window
{
public:
	Win32Window(HINSTANCE hInstance);
	const HWND GetHwnd();
private:
	HWND hwnd = nullptr;
};