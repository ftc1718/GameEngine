#pragma once

#include <string>
#include <FreeImage.h>
#include <FreeImage/Utilities.h>

namespace indie
{
	namespace utils
	{
		std::string readFile(const std::string& fileName);
		BYTE* loadTexture(const char* fileName, int* width, int* height);
	}
}