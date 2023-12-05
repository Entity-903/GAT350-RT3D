#pragma once
#include <string>
#include <glad/include/glad/glad.h>

namespace nc
{
	class StringUtils
	{
public:

	static std::string ToUpper(std::string inputString);
	static std::string ToLower(std::string inputString);
	static bool IsEqualIgnoreCase(std::string inputStringA, std::string inputStringB);
	static std::string CreateUnique(std::string inputString);

	static int GetTrailingNumber(const std::string& str);
	static std::string RemoveTrailingNumber(const std::string& str);
	};

}