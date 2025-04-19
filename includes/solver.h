#pragma once
#include "answer.h"

class letterPoint {
    
	public: 
		letterPoint(const char c, unsigned int pt) 
			: 	letter(c), 
				points(pt)
		{}
		char letter;
		unsigned int points;
		static void solveFor(Answer& ans);
	private:
		static std::vector<letterPoint> getPoints(Answer& ans);
		static unsigned int countLetterInstances(const std::vector<Scores>& scoreVector, char letter);
		static void updateScore(Answer& ans);
		static bool isUnavailable(char letter, const std::vector<char>& unavailableLetters);

};		
	