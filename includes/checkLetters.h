#pragma once

#include "letterPoint.h"
#include "answer.h"
#include <string>
#include <vector>
#include <map>

class CharacterPosition {
public:
    char c;
    bool correctLetter;     // Letter exists in the answer
    bool correctPosition;   // Letter is in the correct position
    
    CharacterPosition() : c('\0'), correctLetter(false), correctPosition(false) {}
    CharacterPosition(char ch) : c(ch), correctLetter(false), correctPosition(false) {}
    CharacterPosition(char ch, bool isCorrectLetter, bool isCorrectPosition) 
        : c(ch), 
          correctLetter(isCorrectLetter),
          correctPosition(isCorrectPosition) {}
};
