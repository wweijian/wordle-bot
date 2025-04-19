#include "answer.h"
#include "solver.h"

int main()
{
	Answer wordleAns;
	letterPoint::solveFor(wordleAns);
	std::cout << "wordleAns.correct: " << wordleAns.correct << std::endl;
	for (size_t i = 1; i < std::min(wordleAns.scoreVector.size(), size_t(10)); ++i) {
		std::cout << "Word: " << wordleAns.scoreVector[i].word << ", Score: " << wordleAns.scoreVector[i].score << std::endl;
	}

	return 0;
}