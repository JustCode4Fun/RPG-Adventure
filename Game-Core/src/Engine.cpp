#include "Engine.h"
#ifdef E_WINDOWS
#include <iostream>
#endif

void Console::printMessage(std::string & message)
{
	#ifdef E_WINDOWS
	std::cout << message << std::endl;
	#endif
}

void Console::printWarning(std::string & warning)
{
}

void Console::printError(std::string & error)
{
}
