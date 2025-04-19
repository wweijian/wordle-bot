#include "answer.h"
#include <termios.h>
#include <cctype>

std::vector<std::string> Answer::loadAnswersFromFile(const std::string& filename) { 
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

bool Answer::isOnlyLetters(const std::string& input) {
	for (char c: input)
	{
		if (!std::isalpha(c))
			return false;
	}
	return true;
}

bool Answer::validateAnswer(std::string& word) {
	// std::cout << "word input: " << word << std::endl;
	for (char& c : word)
		c = std::tolower(static_cast<unsigned char>(c));
	// std::cout << "tolower: " << word << std::endl;
	std::vector<std::string> allSolutions = Answer::loadAnswersFromFile("data/14855solutions.txt");
	for (const std::string& str : allSolutions)
	{
		if (str == word)
		{
			std::cout << "Word Accepted."<< std::endl;
			return true;
		}
	}
	if (word.length() != 5)
		std::cout << "Try again. Please type exactly 5 letters." << std::endl;
	if (word.length() == 5)
	{
		std::cout << "You have typed: " << word << std::endl;
		std::cout << "Try again. Word does not exist." << std::endl;
	}
	if (!Answer::isOnlyLetters(word))
		std::cout << "Please only use letters from the alphabet" << std::endl;
	return false;
}

std::string Answer::inputAnswer(unsigned int maxLength) {
	termios oldt, newt; // declaring two terminal config structs
	std::string answer;
	char c;

	tcgetattr(0, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(0, TCSANOW, &newt);

	while (true)
	{
		answer.clear();
		std::cout << "Enter a 5-Letter word as the answer [hidden]" << std::endl;

		while (true)
		{
			c = std::getchar();
			if (c == '\n' || c == '\r')
			{
				std::cout << std::endl;
				break;
			}
			else if ((c == 127 || c == '\b') && !answer.empty())
			{
				answer.pop_back();
				std::cout <<"\b \b";
			}
			else if (answer.length() < maxLength && std::isprint(c))
			{
				answer += c;
				std::cout << '*';
			}
		}

		if (validateAnswer(answer))
			break;
	}

	tcsetattr(0, TCSANOW, &oldt);

	return answer;
}

std::vector<Scores> Answer::createScores(const std::vector<std::string>& words) {
    std::vector<Scores> scoresList;
    for (const std::string& word : words) {
        scoresList.emplace_back(word, 0);
    }
    return scoresList;
}