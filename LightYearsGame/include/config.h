#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // no debug is release build
	return "assets/";
#else
	return "C:/Users/Mohamed/Music/LightYears/LightYearsGame/assets/";
#endif
}
