#include "solver.h"
#include <vector>
#include <string> 


unsigned int letterPoint::countLetterInstances(const std::vector<Scores>& scoreVector, char letter) {
    unsigned int count = 0;
    for (const Scores& score : scoreVector) {
        if (score.word.find(letter) != std::string::npos) {
            std::vector<bool> seen(26, false);
            for (char ch : score.word) {
                if (ch == letter && !seen[ch - 'a']) {
                    ++count;
                    seen[ch - 'a'] = true;
                    break;
                }
            }
        }
    }
    return count;
}

bool letterPoint::isUnavailable(char letter, const std::vector<char>& unavailableLetters) {
    return std::find(unavailableLetters.begin(), unavailableLetters.end(), letter) != unavailableLetters.end();
}

std::vector<letterPoint> letterPoint::getPoints(Answer& ans) {
    std::vector<letterPoint> pointsVector;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (isUnavailable(c, ans.unavailableLetters)) {
            continue;
        }

        unsigned int count = 0;
        for (const Scores& score : ans.scoreVector) {
            bool seen = false;
            for (char ch : score.word) {
                if (ch == c) {
                    seen = true;
                    break;
                }
            }
            if (seen) {
                ++count;
            }
        }
        pointsVector.emplace_back(c, count);
    }
    return pointsVector;
}

void letterPoint::updateScore(Answer& ans) {
	std::vector<letterPoint> letterPoints;
	letterPoints = getPoints(ans);
	for (const letterPoint& lp : letterPoints) {
        std::cout << "letter: " << lp.letter << " point: " << lp.points << std::endl;
    }
}


void letterPoint::solveFor(Answer& ans) {
	updateScore(ans);
}
