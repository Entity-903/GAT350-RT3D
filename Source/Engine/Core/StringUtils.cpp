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

// return the number at the end of a string "name43" -> 43, if there are no digits return -1
int nc::StringUtils::GetTrailingNumber(const std::string& str)
{
	// if the string is empty return -1
	if (str.empty()) return -1;
	// check from the end of the string for characters that are digits, add digit to strNumber
	// if character is not digit, then exit
	std::string strNumber;
	for (size_t i = str.size() - 1; i >= 0; i--)
	{
		if (std::isdigit(str[i])) strNumber = str[i] + strNumber;
		else break;
	}
	// convert strNumber to a number if not empty
	return (!strNumber.empty()) ? std::stoi(strNumber) : -1;
}

// remove any digit characters from the end of the string "name43" -> "name"
std::string nc::StringUtils::RemoveTrailingNumber(const std::string& str)
{
	if (str.empty()) return "";
	// set result string to str parameter
	// start at the end of the string and remove any characters that are digits
	// if character is not a digit, then exit
	std::string result = str;
	for (size_t i = str.size() - 1; i >= 0; i--)
	{
		if (std::isdigit(str[i])) result.pop_back();
		else break;
	}
	// return string without trailing number
	return result;
}
