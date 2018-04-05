#include "Engine.h"
#ifdef E_WINDOWS
#include <Windows.h>
#include <iostream>
#include <ctime>
#endif

const Console::Theme Console::messageTheme = Theme(BrightWhite, Black);
const Console::Theme Console::warningTheme = Theme(LightYellow, Black);
const Console::Theme Console::errorTheme = Theme(LightRed, Black);
const Console::Theme Console::fatalTheme = Theme(BrightWhite, LightRed);

const Console::Theme Console::defaultTheme = Theme(BrightWhite, Black);


#ifdef E_DEBUG
Console::LogLevel Console::currLogLevel = Console::LogLevel::MESSAGE_LEVEL;
#else
Console::LogLevel Console::currLogLevel = Console::LogLevel::FATAL_LEVEL;
#endif // E_DEBUG

std::string Console::getTimeString()
{
	time_t t = time(0); // TODO: Put this into its own class
	#pragma warning(disable:4996)
	tm *ltm = localtime(&t);
	#pragma warning(restore:4996) 
	std::string year = std::to_string(1900 + ltm->tm_year);
	std::string month = std::to_string(1 + ltm->tm_mon);
	std::string day = std::to_string(ltm->tm_mday);
	std::string hour = std::to_string(ltm->tm_hour);
	std::string min = std::to_string(ltm->tm_min);
	std::string sec = std::to_string(ltm->tm_sec);
	if (month.length() == 1)month.insert(month.begin(), 1, '0');
	if (day.length() == 1)day.insert(day.begin(), 1, '0');
	if (hour.length() == 1)hour.insert(hour.begin(), 1, '0');
	if (min.length() == 1)min.insert(min.begin(), 1, '0');
	if (sec.length() == 1)sec.insert(sec.begin(), 1, '0');

	std::string time = year + "-" + month + "-" + day + " @ "  + hour + ":" + min + ":" + sec + "\t";

	return time;
}

void Console::setConsoleTheme(ThemeColor font, ThemeColor background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(background<<1)|(WORD)(font));
}

void Console::setConsoleTheme(Theme theme)
{
	WORD t = (WORD)(theme.m_background << 4) | (WORD)(theme.m_font);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t);
}

void Console::resetConsoleTheme()
{
	#ifdef E_WINDOWS
	setConsoleTheme(defaultTheme);
	#endif
}

void Console::printMessage(const std::string & message)
{
	if (currLogLevel < LogLevel::MESSAGE_LEVEL) return;
	setConsoleTheme(messageTheme);
	std::cout << getTimeString();
	#ifdef E_WINDOWS
	std::cout << message << std::endl;
	#endif
	resetConsoleTheme();
}

void Console::printWarning(const std::string & warning)
{
	if (currLogLevel < LogLevel::WARNING_LEVEL) return;
	setConsoleTheme(warningTheme);
	std::cout << getTimeString();
	#ifdef E_WINDOWS
	std::cout << warning << std::endl;
	#endif
	resetConsoleTheme();
}

void Console::printError(const std::string & error)
{
	if (currLogLevel < LogLevel::ERROR_LEVEL) return;
	setConsoleTheme(errorTheme);
	std::cout << getTimeString();
	#ifdef E_WINDOWS
	std::cout << error << std::endl;
	#endif
	resetConsoleTheme();
}

void Console::printFatal(const std::string& fatal) {
	if (currLogLevel < LogLevel::FATAL_LEVEL) return;
	setConsoleTheme(fatalTheme);
	std::cout << getTimeString();
	std::cout << fatal << std::endl;
	resetConsoleTheme();
}