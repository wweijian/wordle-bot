#include <iostream>
#include <WordEntry.h>


int main()
{
	// for (size_t i = 0; i < lines.size(); ++i)
	// 	std::cout << lines[i] << std::endl;
	std::string answer;
	std::cout << "enter word: ";
	std::cin >> answer;

	if (WordEntry::validateWord(answer) == true)
		std::cout << "good stuff" << std::endl;
	return 0;

}