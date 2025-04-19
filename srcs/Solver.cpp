#include "answer.h"
#include "letterPoint.h"
#include "main.h"
#include <string>

std::string maxScoreEntry(const Answer& ans) {
    
    Scores maxScoreEntry = ans.scoreVector[0];

    for (const Scores& score : ans.scoreVector) {
        if (score.score > maxScoreEntry.score) {
            maxScoreEntry = score ;
        }
    }

    return maxScoreEntry.word;
}

void updateEntries (Answer& ans, std::string guess) {

	// change unavailable letters
		// add all letters that do not match

	// remove all bad entries
		// remove words without letters that are correct
		// remove words that have letters in the wrong position, if there is one matching position


}

void solveFor(Answer& ans) {
	while(true){
		
		letterPoint::updateScore(ans);
		std::string guessWord = maxScoreEntry(ans);
		std::cout << "guess is " << guessWord << std::endl;
		if (guessWord == ans.correct) {
			std::cout << "You got it!" << std::endl;
			return ; 
		}
		else {
			updateEntries(ans, guessWord);
			return;
		}
	}
}
