
#include <fstream> 
#include <iostream> 
#include <vector> 
#include <string>

class WordEntry
{
	public:
		WordEntry();
		bool validWord;
		static std::vector<std::string> loadAnswersFromFile(const std::string& filename);
		static bool validateWord(std::string& word);
	private:
		static bool isOnlyLetters(const std::string& input);
};