// #include "main.h"
#include "answer.h"
#include "letterPoint.h"

void solveFor(Answer ans);

int main()
{
	Answer wordleAns;
	std::cout << "wordleAns.correct: " << wordleAns.correct << std::endl;
	solveFor(wordleAns);
	
    return 0;
}