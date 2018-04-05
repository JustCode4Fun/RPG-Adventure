#pragma once

#include <string>
#include <cstdint>
#include <fl>

typedef int8_t _bool;
typedef int8_t _byte;
typedef uint8_t _ubyte;
typedef int16_t _short;
typedef uint16_t _ushort;
typedef int32_t _int;
typedef uint32_t _uint;
typedef int64_t _long;
typedef uint64_t _ulong;
typedef float _float;
typedef double _double;

class Console {
private:
	enum ThemeColor
	{
		Black = 0x00,
		Blue = 0x01,
		Green = 0x02,
		Aqua = 0x03,
		Red = 0x04,
		Purple = 0x05,
		Yellow = 0x06,
		White = 0x07,
		Gray = 0x08,
		LightBlue = 0x09,
		LightGreen = 0x0a,
		LightAqua = 0x0b,
		LightRed = 0x0c,
		LightPurple = 0x0d,
		LightYellow = 0x0e,
		BrightWhite = 0x0f,
	};
	struct Theme {
		ThemeColor m_font, m_background;

		Theme(ThemeColor font, ThemeColor background) : m_font(font), m_background(background) {};
		Theme(_int theme) { m_font = ThemeColor(theme >> 1); m_background = ThemeColor(theme & 0x0f); };

	};
public:
	static const Theme c_MessageTheme;
	static const Theme c_WarningTheme;
	static const Theme c_ErrorTheme;
	static const Theme c_FatalTheme;

	static const Theme c_DefaultTheme;

public:
	enum LogLevel {
		NO_LOGGING_LEVEL = 0,
		FATAL_LEVEL = 1,
		ERROR_LEVEL = 2,
		WARNING_LEVEL = 3,
		MESSAGE_LEVEL = 4,
	};
	static LogLevel s_CurrLogLevel;
private:
	static std::string getTimeString();

private:
	static void SetConsoleTheme(ThemeColor font, ThemeColor background);
	static void SetConsoleTheme(Theme theme);
	static void ResetConsoleTheme();
public:
	static void PrintMessage(const std::string& message);
	static void PrintWarning(const std::string& warning);
	static void PrintError(const std::string& error);
	static void PrintFatal(const std::string& fatal);

	static void Print(const std::string& str);
	template <typename T>
	static void Print(const T& t);
public:
	static void Pause();
	static void Pause(const std::string& message);
};
