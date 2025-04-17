#include <iostream>
#include <vector>
#include <string>
#include "Answer.h"


std::vector<unsigned int> countLetterInstance(const std::vector<std::string>& words, const Answer& answer) {
    std::vector<unsigned int> letterCounts(26, 0); // Start with a vector of size 26 initialized to 0

    for (const std::string& word : words) {
        std::vector<bool> seen(26, false); // Reset for each word

        for (char c : word) {
            if (std::isalpha(c)) {
                int index = c - 'a';  // Calculate the index (0 for 'a', 1 for 'b', ..., 25 for 'z')

                // Make sure the letter is not in the unavailableLetters
                bool isUnavailable = false;
                for (char unavailable : answer.unavailableLetters) {
                    if (unavailable == c) {
                        isUnavailable = true;
                        break;
                    }
                }

                if (!isUnavailable && !seen[index]) {
                    ++letterCounts[index];  // Count the letter once per word
                    seen[index] = true; // Avoid double counting for the same word
                }
            }
        }
    }

    return letterCounts;
}


void solveFor(Answer wordleAns)
{
	std::vector<unsigned int> a = countLetterInstance(wordleAns.remainingSolutions, wordleAns);

	int i = 0;
	char c = 'a';
	while (c <= 'z')
	{
		std::cout << a[i] << " number of words have the letter " << c << std::endl;
		i++;
		c++;
	}
}

int main ()
{
	Answer wordleAns;
	solveFor(wordleAns);	
}