#pragma once

#include <stdio.h>

namespace ly
{
	//Macro
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__);
}