#include "stringUtils.h"

namespace MiniEngine
{
	std::vector<std::string> splitString(const std::string& str, char delimeter)
	{
		std::vector<std::string> elems;
		std::stringstream ss(str);
		std::string item;
		while (std::getline(ss, item, delimeter))
		{
			elems.push_back(item);
		}
		return elems;
	}
}
