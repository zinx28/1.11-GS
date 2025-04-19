#include "../Public/Log.h"

#include <Windows.h>
#include <iostream>

// wtf is this function???

void TheFunctionThatOutputsTheFuckliongLogToTheUserThankYou(const std::wstring& Message)
{
	std::wcout << std::format(L"{}\n", Message);
	OutputDebugStringW(Message.c_str());
}
