#pragma once

#include <iostream> 
#include <fstream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <unordered_map>

struct Scores {
    std::string word;
    unsigned int score;

    Scores(const std::string& w, unsigned int s) 
        :   word(w), 
            score(s) 
    {}
};

class Answer
{
    public:
        Answer()
            :   correct(inputAnswer(5)),
                scoreVector(createScores(loadAnswersFromFile("data/14855solutions.txt"))),
                unavailableLetters({'g','q'}),
                attempt(0)
        {}
        const std::string            correct;
        std::vector<Scores>          scoreVector;
        std::vector<char>            unavailableLetters;
        int                          attempt;

    private:
        static std::string inputAnswer(unsigned int maxLength);
        static bool isOnlyLetters(const std::string& input);
        static bool validateAnswer (std::string& word);
        static std::vector<std::string> loadAnswersFromFile(const std::string& filename);
        static std::vector<Scores> createScores(const std::vector<std::string>& words);
};