#include "main.h"
#include "answer.h"
#include "letterPoint.h"

int main()
{
	Answer wordleAns;
	solveFor(wordleAns);
	std::cout << "wordleAns.correct: " << wordleAns.correct << std::endl;
	for (size_t i = 8000; i < std::min(wordleAns.scoreVector.size(), size_t(8100)); ++i) {
		std::cout << "Word: " << wordleAns.scoreVector[i].word << ", Score: " << wordleAns.scoreVector[i].score << std::endl;
	}


    return 0;
}