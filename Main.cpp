#include "pch.h"
WINDOWS_MAIN_ENTRY
{
	std::make_shared<GameEngine>((hInstance))->Run();
	return NOERROR;
}