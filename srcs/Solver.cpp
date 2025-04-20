#include "solver.h"
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
    for (int i = 0; i < 5; i++) {
        if (!evaluatedGuess[i].correctLetter && 
            word.find(evaluatedGuess[i].c) != std::string::npos) {
            return true; // Word contains an unavailable letter
        }
    }
    return false;
}



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

// Print the guess evaluation for debugging
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
    // Only remove if it's not the correct answer
    if (guessWord != ans.correct) {
        // Use remove_if to find and remove the entry with the matching word
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
    // Track if the answer was filtered out
    bool answerRemoved = false;
    // Track number of attempts
    int attemptCount = 0;
    
    while (true) {
        // Step 1: Update scores for all words
        letterPoint::updateScore(ans);
        
        // Step 2: Get the highest-scoring word as our guess
        std::string guessWord = maxScoreEntry(ans);
        
        // Print the current guess and increment attempt counter
        attemptCount++;
        std::cout << "Attempt " << attemptCount << ": Guessing \"" << guessWord << "\"" << std::endl;
        
        // Step 3: Check if the guess is correct
        if (guessWord == ans.correct) {
            std::cout << "Success! Found the answer \"" << ans.correct << "\" in " << attemptCount << " attempts." << std::endl;
            break;
        }

		// Step 4: Remove the incorrect guess from the score vector
		removeGuessFromScoreVector(ans, guessWord);
        
        // Step 4: If not correct, evaluate the guess and filter the words
        Guess evaluatedGuess = evaluateGuess(guessWord, ans);
        
        // Store the size before filtering for debug purposes
        size_t beforeSize = ans.scoreVector.size();
        
        // Apply our filtering functions
        filterWordsByGuess(ans, evaluatedGuess);
        
        // Step 5: Check if we accidentally filtered out the correct answer
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
        
        // Optional: Print remaining words count for debugging
        std::cout << "  Filtered from " << beforeSize << " to " << ans.scoreVector.size() << " possible words." << std::endl;
        
        // Step 6: Continue the loop (goes back to step 1)
    }
}