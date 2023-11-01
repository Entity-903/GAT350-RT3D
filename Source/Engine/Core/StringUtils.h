#pragma once
#include <string>
//#include <glm/glm/glm.hpp>
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
	};

}

// ToUpper
// ToLower
// IsEqualIgnoreCase
// CreateUnique