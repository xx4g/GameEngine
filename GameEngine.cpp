#include "pch.h"
GameEngine::GameEngine(HINSTANCE& hInstance)
{
	hInst = hInstance;
	auto sharePtr = std::make_shared<Win32Window>((hInstance));
	if (sharePtr)
	{
		windowPtr = sharePtr.get();
	}
}

void GameEngine::Run()
{

	auto message = std::make_shared<MSG>();
	if (!message)
	{
		return;
	}
	auto windowPtr = GetWin32WindowPtr();
	if (!windowPtr)
	{
		return;
	}

	HACCEL hAccelTable = LoadAccelerators(GetHInstance(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (message && GetMessage(message.get(), nullptr, 0, 0) > 0)
	{
		if (!TranslateAccelerator(windowPtr->GetHwnd(), hAccelTable, message.get()))
		{
				TranslateMessage(message.get());
				DispatchMessage(message.get());
		}
	}
}

HINSTANCE GameEngine::GetHInstance()
{
	return hInst;
}

Win32Window* GameEngine::GetWin32WindowPtr()
{
	return windowPtr;
}
