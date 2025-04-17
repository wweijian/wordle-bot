#include <fstream> 
#include <iostream> 
#include <vector> 
#include <string>

class Answer
{
	public:
		Answer()
			:	correct(inputAnswer(5)),
				remainingSolutions(loadAnswersFromFile("data/14855solutions.txt")),
				unavailableLetters({'g'}),
				attempt(0)
		{}

		const std::string			correct;
		std::vector<std::string> 	remainingSolutions;
		std::vector<char>			unavailableLetters;
		int							attempt;

	private:
		static bool 					isOnlyLetters(const std::string& input);
		std::string 					inputAnswer(size_t maxLength);
		static bool 					validateAnswer(std::string& word);
		static std::vector<std::string>	loadAnswersFromFile(const std::string& filename);

};