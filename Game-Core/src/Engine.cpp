#include "Engine.h"
#ifdef E_WINDOWS
#include <Windows.h>
#include <iostream>
#include <ctime>
#endif

const Console::Theme Console::c_MessageTheme = Theme(BrightWhite, Black);
const Console::Theme Console::c_WarningTheme = Theme(LightYellow, Black);
const Console::Theme Console::c_ErrorTheme = Theme(LightRed, Black);
const Console::Theme Console::c_FatalTheme = Theme(BrightWhite, LightRed);

const Console::Theme Console::c_DefaultTheme = Theme(BrightWhite, Black);


#ifdef E_DEBUG
Console::LogLevel Console::s_CurrLogLevel = Console::LogLevel::MESSAGE_LEVEL;
#else
Console::LogLevel Console::s_CurrLogLevel = Console::LogLevel::FATAL_LEVEL;
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

void Console::SetConsoleTheme(ThemeColor font, ThemeColor background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)(background<<1)|(WORD)(font));
}

void Console::SetConsoleTheme(Theme theme)
{
	WORD t = (WORD)(theme.m_background << 4) | (WORD)(theme.m_font);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), t);
}

void Console::ResetConsoleTheme()
{
	#ifdef E_WINDOWS
	SetConsoleTheme(c_DefaultTheme);
	#endif
}

void Console::PrintMessage(const std::string & message)
{
	if (s_CurrLogLevel < LogLevel::MESSAGE_LEVEL) return;
	SetConsoleTheme(c_MessageTheme);
	std::cout << getTimeString();
	#ifdef E_WINDOWS
	std::cout << message << std::endl;
	#endif
	ResetConsoleTheme();
}

void Console::PrintWarning(const std::string & warning)
{
	if (s_CurrLogLevel < LogLevel::WARNING_LEVEL) return;
	SetConsoleTheme(c_WarningTheme);
	std::cout << getTimeString();
	#ifdef E_WINDOWS
	std::cout << warning << std::endl;
	#endif
	ResetConsoleTheme();
}

void Console::PrintError(const std::string & error)
{
	if (s_CurrLogLevel < LogLevel::ERROR_LEVEL) return;
	SetConsoleTheme(c_ErrorTheme);
	std::cout << getTimeString();
	#ifdef E_WINDOWS
	std::cout << error << std::endl;
	#endif
	ResetConsoleTheme();
}

void Console::PrintFatal(const std::string& fatal) {
	if (s_CurrLogLevel < LogLevel::FATAL_LEVEL) return;
	SetConsoleTheme(c_FatalTheme);
	#ifdef E_WINDOWS
	std::cout << getTimeString();
	std::cout << fatal << std::endl;
	#endif
	ResetConsoleTheme();
}

void Console::Print(const std::string & str)
{
	ResetConsoleTheme();
	#ifdef E_WINDOWS
	std::cout << str << std::endl;
	#endif
}

template <typename T>
void Console::Print(const T& t)
{
	ResetConsoleTheme();
	#ifdef E_WINDOWS
	std::cout << t << std::endl;
	#endif
}

void Console::Pause()
{
	#ifdef E_WINDOWS
	system("pause");
	#endif
}

void Console::Pause(const std::string & message)
{
	Pause();
	PrintMessage(message);
}
