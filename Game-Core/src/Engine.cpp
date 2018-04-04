#include "Engine.h"
#ifdef E_WINDOWS
#include <Windows.h>
#include <iostream>
#endif

const Console::FontColor Console::messageColor = FontColor::BrightWhite;
const Console::FontColor Console::warningColor = FontColor::LightYellow;
const Console::FontColor Console::errorColor = FontColor::LightRed;

const Console::FontColor Console::defaultColor = FontColor::BrightWhite;

void Console::setFontColor(FontColor c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)c);
}

void Console::resetFontColor()
{
	#ifdef E_WINDOWS
	setFontColor(defaultColor);
	#endif
}

void Console::printMessage(const std::string & message)
{
	setFontColor(messageColor);
	#ifdef E_WINDOWS
	std::cout << message << std::endl;
	#endif
	resetFontColor();
}

void Console::printWarning(const std::string & warning)
{
	setFontColor(warningColor);
	#ifdef E_WINDOWS
	std::cout << warning << std::endl;
	#endif
	resetFontColor();
}

void Console::printError(const std::string & error)
{
	setFontColor(errorColor);
	#ifdef E_WINDOWS
	std::cout << error << std::endl;
	#endif
	resetFontColor();
}

void Console::printDMessage(const std::string & message)
{
	#ifdef E_DEBUG
	printMessage(message);
	#endif
}

void Console::printDWarning(const std::string & warning)
{
	#ifdef E_DEBUG
	printWarning(warning);
	#endif
}

void Console::printDError(const std::string & error)
{
	#ifdef E_DEBUG
	printError(error);
	#endif
}
