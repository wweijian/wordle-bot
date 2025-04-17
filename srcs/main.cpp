#include <iostream>
#include <WordEntry.h>

std::string inputAnswer(size_t maxLength);

int main()
{

	std::string answer = inputAnswer((std::size_t) 5);	
	if (WordEntry::validateWord(answer) == true)
		std::cout << "Answer Accepted. Wordie will begin guessing." << std::endl;	
	solveWordle();
	return 0;
}