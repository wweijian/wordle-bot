#include "header.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>


void filterWordsByGuess(Answer& ans, const Guess& evaluatedGuess) {
    ans.scoreVector.erase(
        std::remove_if(ans.scoreVector.begin(), ans.scoreVector.end(), 
            [&evaluatedGuess](const Scores& score) {
                const std::string& word = score.word;
                
                if (!hasCorrectPositions(word, evaluatedGuess))
                    return true;
                
                if (!hasRequiredLetterFrequencies(word, evaluatedGuess))
                    return true;
                
                if (hasUnavailableLetters(word, evaluatedGuess)) {
                    return true;
                }
                
                return false; 
            }),
        ans.scoreVector.end()
    );
}

void printGuessEvaluation(const Guess& guess) {
    std::cout << "Guess evaluation:" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "Position " << i << ": " << guess[i].c 
                  << " (In word: " << (guess[i].correctLetter ? "Yes" : "No")
                  << ", Correct position: " << (guess[i].correctPosition ? "Yes" : "No")
                  << ")" << std::endl;
    }
}

std::string maxScoreEntry(const Answer& ans) {
    
    Scores maxScoreEntry = ans.scoreVector[0];

    for (const Scores& score : ans.scoreVector) {
        if (score.score > maxScoreEntry.score) {
            maxScoreEntry = score ;
        }
    }

    return maxScoreEntry.word;
}

void removeGuessFromScoreVector(Answer& ans, const std::string& guessWord) {
    if (guessWord != ans.correct) {
        ans.scoreVector.erase(
            std::remove_if(ans.scoreVector.begin(), ans.scoreVector.end(),
                [&guessWord](const Scores& score) {
                    return score.word == guessWord;
                }),
            ans.scoreVector.end()
        );
    }
}

void solveFor(Answer ans) {
    bool answerRemoved = false;
    int attemptCount = 0;
    
    while (true) {
        letterPoint::updateScore(ans);
        std::string guessWord = maxScoreEntry(ans);
        attemptCount++;
        std::cout << "Attempt " << attemptCount << ": Guessing \"" << guessWord << "\"" << std::endl;
        if (guessWord == ans.correct) {
            std::cout << "Success! Found the answer \"" << ans.correct << "\" in " << attemptCount << " attempts." << std::endl;
            break;
        }
		removeGuessFromScoreVector(ans, guessWord);
        Guess evaluatedGuess = evaluateGuess(guessWord, ans);
        size_t beforeSize = ans.scoreVector.size();
        filterWordsByGuess(ans, evaluatedGuess);
        bool correctWordExists = false;
        for (const auto& score : ans.scoreVector) {
            if (score.word == ans.correct) {
                correctWordExists = true;
                break;
            }
        }
        if (!correctWordExists) {
            std::cout << "Error: The correct answer \"" << ans.correct << "\" was filtered out. Algorithm failed." << std::endl;
            answerRemoved = true;
            break;
        }
        std::cout << "  Filtered from " << beforeSize << " to " << ans.scoreVector.size() << " possible words." << std::endl;
    }
}