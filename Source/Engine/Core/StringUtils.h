#pragma once
#include <string>
//#include <glm/glm/glm.hpp>
#include <glad/include/glad/glad.h>

namespace nc
{
	class StringUtils
	{
public:
	std::string ToUpper(std::string inputString);
	std::string ToLower(std::string inputString);
	bool IsEqualIgnoreCase(std::string inputStringA, std::string inputStringB);
	std::string CreateUnique(std::string inputString);
	};

}

// ToUpper
// ToLower
// IsEqualIgnoreCase
// CreateUnique