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
        if (!result[i].correctPosition) { // Skip already correctly positioned letters
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

// Check if a word has letters in correct positions based on the guess
bool hasCorrectPositions(const std::string& word, const Guess& evaluatedGuess) {
    for (int i = 0; i < 5; i++) {
        if (evaluatedGuess[i].correctPosition && word[i] != evaluatedGuess[i].c) {
            return false; // Word doesn't have required letter in correct position
        }
    }
    return true;
}

bool hasRequiredLetterFrequencies(const std::string& word, const Guess& evaluatedGuess) {
    // Create letter frequency map for the word being checked
    std::map<char, int> wordFreq;
    for (char c : word) {
        wordFreq[c]++;
    }
    
    // Check for minimum letter frequencies
    std::map<char, int> requiredFreq;
    for (const auto& pos : evaluatedGuess) {
        if (pos.correctLetter) {
            requiredFreq[pos.c]++;
        }
    }
    
    // Check if word meets minimum frequency requirements
    for (auto it = requiredFreq.begin(); it != requiredFreq.end(); ++it) {
        char letter = it->first;
        int count = it->second;
        if (wordFreq[letter] < count) {
            return false; // Word doesn't have enough of a required letter
        }
    }
    
    return true;
}

bool hasUnavailableLetters(const std::string& word, const Guess& evaluatedGuess) {
    // Build a map of which letters are unavailable in which positions
    std::map<char, std::vector<int>> unavailablePositions;
    
    // Mark positions where letters are definitely not correct
    for (int i = 0; i < 5; i++) {
        if (!evaluatedGuess[i].correctLetter) {
            unavailablePositions[evaluatedGuess[i].c].push_back(i);
        }
    }
    
    // Check if the word contains any letters in positions where they are known to be unavailable
    for (const auto& pair : unavailablePositions) {
        char letter = pair.first;
        const auto& positions = pair.second;
        
        // Count how many times this letter appears in the guess but was marked incorrect
        int unavailableCount = positions.size();
        
        // Count how many times this letter appears correctly in other positions
        int correctCount = 0;
        for (int i = 0; i < 5; i++) {
            if (evaluatedGuess[i].correctLetter && evaluatedGuess[i].c == letter) {
                correctCount++;
            }
        }
        
        // Count how many times this letter appears in the word
        int wordCount = 0;
        for (char c : word) {
            if (c == letter) {
                wordCount++;
            }
        }
        
        // If this letter appears more times in the word than it does in correct positions in the guess,
        // then the word should be filtered out
        if (wordCount > correctCount) {
            return true;
        }
        
        // Also, check for specific positions where we know the letter can't be
        for (int pos : positions) {
            if (word[pos] == letter) {
                return true;
            }
        }
    }
    
    return false;
}
