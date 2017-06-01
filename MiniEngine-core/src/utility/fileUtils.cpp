#include "fileUtils.h"

namespace miniEngine
{
	namespace utils
	{
		std::string readFile(const std::string& filePath)
		{
			FILE* file;
			file = fopen(filePath.c_str(), "rb");

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			std::string result(length, '\0');
			fseek(file, 0, SEEK_SET);
			
			fread(&result[0], 1, length, file);
			fclose(file);

			return result;
		}
	}
}