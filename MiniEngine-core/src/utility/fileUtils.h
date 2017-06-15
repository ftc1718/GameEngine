#pragma once

#include <string>
#include <FreeImage.h>
#include <GL/glew.h>

namespace MiniEngine
{
	namespace utils
	{
		std::string readFile(const std::string& fileName);
		BYTE* loadTexture(const char* fileName, GLsizei* width, GLsizei* height);
	}
}