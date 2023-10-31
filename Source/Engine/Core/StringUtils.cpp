#include "StringUtils.h"

// Takes in a string and returns it uppercase
std::string nc::StringUtils::ToUpper(std::string inputString)
{
	std::string uppercaseString = inputString;

	for (int i = 0; i < uppercaseString.length(); i++)
	{
		// Checks if the character in the array is lowercase
		if (uppercaseString[i] >= 'a' && uppercaseString[i] <= 'z')
		{
			// The value between an uppercase and lowercase letter is 32, the same value that the whitespace, ' ', represents
			uppercaseString[i] -= ' ';
		}
	}
	return uppercaseString;
}

// Takes in a string and returns it lowercase
std::string nc::StringUtils::ToLower(std::string inputString)
{
	std::string lowercaseString = inputString;

	for (int i = 0; i < lowercaseString.length(); i++)
	{
		// Checks if the character in the array is uppercase
		if (lowercaseString[i] >= 'A' && lowercaseString[i] <= 'Z')
		{
			// The value between an uppercase and lowercase letter is 32, the same value that the whitespace, ' ', represents
			lowercaseString[i] += ' ';
		}
	}
	return lowercaseString;
}

// Takes in two strings and checks if they are equal to each other ignoring case
bool nc::StringUtils::IsEqualIgnoreCase(std::string inputStringA, std::string inputStringB)
{
	return ToLower(inputStringA) == ToLower(inputStringB);
}

// Takes in a string and adds a value at the end
// The variable that holds the value, uniqueCounter, then increments to ensure a unique string is produced every time it is called
std::string nc::StringUtils::CreateUnique(std::string inputString)
{
	static GLuint uniqueCounter;

	std::string uniqueString = inputString + std::to_string(uniqueCounter);
	uniqueCounter++;

	return uniqueString;
}
