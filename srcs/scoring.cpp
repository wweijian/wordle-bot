#include "letterPoint.h"
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
    // Get points for each letter
    std::vector<letterPoint> letterPoints = getPoints(ans);
    
    // Create a lookup map for faster access to letter points
    std::unordered_map<char, unsigned int> pointsMap;
    for (const auto& lp : letterPoints) {
        pointsMap[lp.letter] = lp.points;
    }
    
    // Update the score for each word in the scoreVector
    for (auto& scoreEntry : ans.scoreVector) {
        unsigned int totalScore = 0;
        
        // Track which letters we've already counted in this word
        std::vector<bool> counted(26, false);
        
        // For each letter in the word
        for (char c : scoreEntry.word) {
            // If letter hasn't been counted yet and has points assigned
            if (!counted[c - 'a'] && pointsMap.find(c) != pointsMap.end()) {
                totalScore += pointsMap[c];
                counted[c - 'a'] = true;  // Mark this letter as counted
            }
        }
        
        // Update the score
        scoreEntry.score = totalScore;
    }
}