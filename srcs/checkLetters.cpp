#include "checkLetters.h"
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using Guess = std::vector<CharacterPosition>;

void markCorrectPositions(Guess& result, const std::string& guessWord, const Answer& ans, std::map<char, int>& answerFreq) {
    for (int i = 0; i < 5; i++) {
        if (guessWord[i] == ans.correct[i]) {
            result[i].correctPosition = true;
            result[i].correctLetter = true;
            answerFreq[guessWord[i]]--;
        }
    }
}

void markCorrectLetters(Guess& result, const std::string& guessWord, std::map<char, int>& answerFreq) {
    for (int i = 0; i < 5; i++) {
        if (!result[i].correctPosition) {
            char c = guessWord[i];
            if (answerFreq[c] > 0) {
                result[i].correctLetter = true;
                answerFreq[c]--;
            }
        }
    }
}

Guess evaluateGuess(const std::string& guessWord, const Answer& ans) {
    Guess result(5);
    
    for (int i = 0; i < 5; i++) {
        result[i].c = guessWord[i];
    }
    std::map<char, int> answerFreq;
    for (char c : ans.correct) {
        answerFreq[c]++;
    }
    markCorrectPositions(result, guessWord, ans, answerFreq);
    markCorrectLetters(result, guessWord, answerFreq);
    
    return result;
}

bool hasCorrectPositions(const std::string& word, const Guess& evaluatedGuess) {
    for (int i = 0; i < 5; i++) {
        if (evaluatedGuess[i].correctPosition && word[i] != evaluatedGuess[i].c) {
            return false;
        }
    }
    return true;
}

bool hasRequiredLetterFrequencies(const std::string& word, const Guess& evaluatedGuess) {
    std::map<char, int> wordFreq;
    for (char c : word) {
        wordFreq[c]++;
    }
    
    std::map<char, int> requiredFreq;
    for (const auto& pos : evaluatedGuess) {
        if (pos.correctLetter) {
            requiredFreq[pos.c]++;
        }
    }
    
    for (auto it = requiredFreq.begin(); it != requiredFreq.end(); ++it) {
        char letter = it->first;
        int count = it->second;
        if (wordFreq[letter] < count) {
            return false;
        }
    }
    
    return true;
}

bool hasUnavailableLetters(const std::string& word, const Guess& evaluatedGuess) {

    std::map<char, std::vector<int>> unavailablePositions;
    for (int i = 0; i < 5; i++) {
        if (!evaluatedGuess[i].correctLetter) {
            unavailablePositions[evaluatedGuess[i].c].push_back(i);
        }
    }
    for (const auto& pair : unavailablePositions) {
        char letter = pair.first;
        const auto& positions = pair.second;
        int unavailableCount = positions.size();
        int correctCount = 0;
        for (int i = 0; i < 5; i++) {
            if (evaluatedGuess[i].correctLetter && evaluatedGuess[i].c == letter) {
                correctCount++;
            }
        }
        int wordCount = 0;
        for (char c : word) {
            if (c == letter) {
                wordCount++;
            }
        }
        if (wordCount > correctCount) {
            return true;
        }
        for (int pos : positions) {
            if (word[pos] == letter) {
                return true;
            }
        }
    }
    
    return false;
}
