#pragma once

#include "checkLetters.h"

using Guess = std::vector<CharacterPosition>;

Guess evaluateGuess(const std::string& guessWord, const Answer& ans);

void markCorrectPositions(Guess& result, const std::string& guessWord, const Answer& ans, std::map<char, int>& answerFreq);
void markCorrectLetters(Guess& result, const std::string& guessWord, std::map<char, int>& answerFreq);

bool hasCorrectPositions(const std::string& word, const Guess& evaluatedGuess);
bool hasRequiredLetterFrequencies(const std::string& word, const Guess& evaluatedGuess);
bool hasUnavailableLetters(const std::string& word, const Guess& evaluatedGuess);
void filterWordsByGuess(Answer& ans, const Guess& evaluatedGuess);

void printGuessEvaluation(const Guess& guess);
std::string maxScoreEntry(const Answer& ans);
void removeGuessFromScoreVector(Answer& ans, const std::string& guessWord);

void solveFor(Answer ans);