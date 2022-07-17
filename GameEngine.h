#pragma once
class GameEngine
{
public:
	GameEngine(HINSTANCE& hInstance);
	void Run();
	HINSTANCE GetHInstance();
	Win32Window* GetWin32WindowPtr();
private:
	Win32Window* windowPtr = nullptr;
	HINSTANCE hInst = nullptr;
};