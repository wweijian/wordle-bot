#include "WordEntry.h"
#include <algorithm>
#include <cctype>

std::vector<std::string> WordEntry::loadAnswersFromFile(const std::string& filename)
{
	std::ifstream file(filename);
	std::vector<std::string> allSolutions;
	std::string possibleAnswer;
	
	while (std::getline(file, possibleAnswer))
	{
		if(!possibleAnswer.empty())
			allSolutions.push_back(possibleAnswer);
	}

	return allSolutions;
}

bool WordEntry::isOnlyLetters(const std::string& input)
{
	for (char c: input)
	{
		if (!std::isalpha(c))
			return false;
	}
	return true;
}

bool WordEntry::validateWord(std::string& word)
{
	std::cout << "word input: " << word << std::endl;
	for (char& c : word)
		c = std::tolower(static_cast<unsigned char>(c));
	std::cout << "tolower: " << word << std::endl;
	std::vector<std::string> allSolutions = WordEntry::loadAnswersFromFile("data/14855solutions.txt");
	for (const std::string& str : allSolutions)
	{
		if (str == word)
			return true;
	}
	if (word.length() != 5)
		std::cout << "Try again. Please type exactly 5 letters." << std::endl;
	if (word.length() == 5)
		std::cout << "Try again. Word does not exist." << std::endl;
	if (!WordEntry::isOnlyLetters(word))
		std::cout << "Please only use letters from the alphabet";
	return false;
}