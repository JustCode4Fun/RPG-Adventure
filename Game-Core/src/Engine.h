#pragma once

#include <string>

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
		Theme(int theme) { m_font = ThemeColor(theme >> 1); m_background = ThemeColor(theme & 0x0f); };

	};
public:
	static const Theme messageTheme;
	static const Theme warningTheme;
	static const Theme errorTheme;
	static const Theme fatalTheme;

	static const Theme defaultTheme;

private:
	static std::string getTimeString();

private:
	static void setConsoleTheme(ThemeColor font, ThemeColor background);
	static void setConsoleTheme(Theme theme);
	static void resetConsoleTheme();
public:
	static void printMessage(const std::string& message);
	static void printWarning(const std::string& warning);
	static void printError(const std::string& error);
	static void printFatal(const std::string& fatal);
};