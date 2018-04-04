#pragma once

#include <string>


class Console {
private:
	enum class FontColor
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
public:
	static const FontColor messageColor;
	static const FontColor warningColor;
	static const FontColor errorColor;

	static const FontColor defaultColor;

private:
	static void setFontColor(FontColor c);
	static void resetFontColor();
public:
	static void printMessage(const std::string& message);
	static void printWarning(const std::string& warning);
	static void printError(const std::string& error);

	static void printDMessage(const std::string& message);
	static void printDWarning(const std::string& warning);
	static void printDError(const std::string& error);
};