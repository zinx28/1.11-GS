#pragma once

#include <string>
#include <format>

#define MAX_LOG_LEVEL ELogLevel::Error

enum ELogLevel : unsigned char
{
	Info,
	Warning,
	Error
};

constexpr const wchar_t* LogLevelToStringW(const ELogLevel Level)
{
	switch (Level)
	{
	case ELogLevel::Info:
		return L"Info";
	case ELogLevel::Warning:
		return L"Warning";
	case ELogLevel::Error:
		return L"Error";
	default:
		return L"Unknown";
	}
}

void TheFunctionThatOutputsTheFuckliongLogToTheUserThankYou(const std::wstring& Message);

template<typename... Args>
__forceinline void LogMessage(const ELogLevel Level, const std::wstring& Message, const wchar_t* Function, const wchar_t* File, const unsigned int Line, Args&&... Arguments)
{
	if (MAX_LOG_LEVEL < Level)
	{
		return;
	}

	std::wstring FormattedMessage = std::vformat(Message, std::make_wformat_args(Arguments...));

	TheFunctionThatOutputsTheFuckliongLogToTheUserThankYou(
		std::format(L"[Luna 1.11 | {} | {}:{}] {}: {}", Function, File, Line, LogLevelToStringW(Level), FormattedMessage)
	);
}

#define LogMsg(Level, Message, ...) \
	LogMessage(Level, Message, _CRT_WIDE(__FUNCTION__), __FILEW__, __LINE__, __VA_ARGS__);