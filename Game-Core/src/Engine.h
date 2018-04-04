#pragma once

#include <string>

#define E_DEBUG
#define E_RELEASE
#define E_WINDOWS

class Console {
private:
	enum ConsoleFontColor
	{
		Black=0x00,
		Blue=0x01,
		Green=0x02,
		Aqua=0x03,
		Red=0x04,
		Purple=0x05,
		Yellow=0x06,
		White=0x07,
		Gray=0x08,
		LightBlue=0x09,
		LightGreen=0x0a,
		LightAqua=0x0b,
		LightRed=0x0c,
		LightPurple=0x0d,
		LightYellow=0x0e,
		BrightWhite=0x0f,
	};
public:
	ConsoleFontColor
	static void printMessage(std::string& message);
	static void printWarning(std::string& warning);
	static void printError(std::string& error);
};