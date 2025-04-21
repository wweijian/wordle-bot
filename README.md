# My terrible Wordle Solver bot -- Wordie

## Information
An avid wordle fan who has played the game since its inception, I want to take an algorithmic approach to solving wordle while learning how to write a program in C++.  
  
This is a probability based model, that takes word with the combined highest occurrence scores of letters as a proxy of the likelihood the word is the answer. If it is wrong, it eliminates all the answers which fails the clues, and try again. Given that the first word "aeros" contains letters with some of the highest occurence scores, it should also eliminate the biggest segments of the possible solutions.  
  
I had no idea the algorithm was going to fare this poorly, and will improve on this some day as I get better at programming. In the meantime, I'm happy that I've coded something that is functional and is useable in further attempts at creating a better algorithm.  

### Takeaways
Throughout this process, I've considered the following the be the important takeaways:  
    1. Learning how to type without letters showing in terminal  
    2. The use of classes, vectors and maps  
    3. Reading of file through the program  


## Set-Up

   ***Do note that this program only runs on unix/linux and the compiler must be of at least version 14**  

    1. Download all the files that are in this repository (do not change the names of the file)  
    2. Go to the main folder on your terminal  
    3. Type make to compile all the necessary files  
    4. Type make run to start the guesser  
    5. Type in any 5-letter word that you know  
    6. Wordie will attempt to guess your word  
    7. After Wordie guesses your word, you can type make clean in the command line to delete the compiled program  



## Input Handling Process
```
function inputAnswer(maxLength):
    1. Save current terminal settings
    2. Configure terminal to not echo characters and disable canonical mode
    3. Prompt user for a 5-letter word
    4. While true:
        a. Clear answer string
        b. While reading characters:
            i. If Enter key pressed, break loop
            ii. If Backspace pressed and answer not empty, remove last character
            iii. If character is printable and answer length < maxLength, add character and display '*'
        c. Validate answer using validateAnswer()
        d. If valid, break loop
    5. Restore original terminal settings
    6. Return validated answer

function validateAnswer(word):
    1. Convert word to lowercase
    2. Load valid words from solutions file
    3. Check if word exists in solutions list
    4. If exists, accept word and return true
    5. If not, provide appropriate error message:
       - If not 5 letters, notify user
       - If 5 letters but not in dictionary, notify user
       - If contains non-alphabet characters, notify user
    6. Return false if validation failed
```

## Core Solver Algorithm
```
function solveFor(answer):
    1. Initialize attempts counter to 0
    2. While true:
        a. Update word scores using letter frequency analysis
        b. Select highest scoring word as guess
        c. Increment attempt counter
        d. Display current guess
        e. If guess matches correct answer:
            i. Display success message with number of attempts
            ii. Break loop
        f. Remove incorrect guess from candidate pool
        g. Evaluate guess against correct answer
        h. Filter remaining candidate words based on evaluation
        i. Verify correct answer still exists in candidate pool
        j. Display number of remaining candidate words
```

## Guess Evaluation Process
```
function evaluateGuess(guessWord, correctAnswer):
    1. Initialize result array with 5 CharacterPosition objects
    2. Set characters in result from guessWord
    3. Create frequency map of letters in correct answer
    4. Mark correct positions:
        For each position i:
            If guessWord[i] == correctAnswer[i]:
                Mark position as correct
                Decrement letter frequency
    5. Mark correct letters in wrong positions:
        For each position i not already marked correct:
            If frequency of letter > 0:
                Mark letter as present
                Decrement letter frequency
    6. Return evaluation result
```

## Word Filtering Logic
```
function filterWordsByGuess(candidateWords, evaluatedGuess):
    Remove words from candidateWords if any of the following are true:
        1. !hasCorrectPositions(word, evaluatedGuess)
        2. !hasRequiredLetterFrequencies(word, evaluatedGuess)
        3. hasUnavailableLetters(word, evaluatedGuess)

function hasCorrectPositions(word, evaluatedGuess):
    For each position i:
        If evaluatedGuess[i] is marked as correct position AND word[i] != evaluatedGuess[i].character:
            Return false
    Return true

function hasRequiredLetterFrequencies(word, evaluatedGuess):
    1. Create frequency map for word
    2. Create required frequency map from correctly identified letters
    3. For each required letter:
        If word's frequency of letter < required frequency:
            Return false
    Return true

function hasUnavailableLetters(word, evaluatedGuess):
    1. Map letters to positions where they're confirmed unavailable
    2. For each unavailable letter:
        a. Count occurrences marked incorrect
        b. Count occurrences marked correct
        c. Count occurrences in candidate word
        d. If word count > correct count, return true
        e. If word contains letter in specific unavailable position, return true
    Return false
```

  *** note: I have since realised in further testing of the wordie that I did not filter out words with letters in the incorrect position, it maybe is something to patch at a later time**  
  

## Scoring Mechanism
```
function updateScore(candidateWords):
    1. Calculate frequency points for each letter:
        a. For each letter in alphabet:
            i. If letter is unavailable, skip it
            ii. Count words containing this letter
            iii. Assign point value equal to count
    2. For each candidate word:
        a. Initialize score to 0
        b. Track which letters have been counted
        c. For each unique letter in word:
            Score += letter's frequency points
        d. Update word's score
```

## Analysis of Implementation Choices

The implementation uses a letter frequency-based heuristic scoring system to determine the next guess, choosing words that contain commonly occurring letters in the remaining candidate pool. This approach performs reasonably well but may not be optimal for several reasons:

1. **Letter Position Significance**: The current implementation scores letters based on their presence in words but doesn't consider their positional significance. Letters are more likely to appear in certain positions.

2. **Information Gain**: The algorithm doesn't explicitly maximize information gain with each guess. An optimal strategy would select words that eliminate the maximum number of candidates regardless of whether they could be the answer.

3. **Hard-Coded First Guesses**: While not currently implemented, having strategic first guesses (like "SLATE" or "CRANE") could immediately eliminate a large portion of the dictionary.

4. **Computational Efficiency**: The current implementation recalculates scores for all words after each guess, which could be optimized for larger dictionaries.

In future iterations, I might consider implementing:

1. A minimax algorithm that chooses words minimizing the maximum remaining dictionary size in the worst case.

2. An entropy-based approach that selects words providing maximum information gain.

3. Pre-computing an optimal decision tree for the first 2-3 guesses.

4. Caching letter frequency calculations to improve performance.

The current approach prioritizes simplicity and readability over pure optimization, which is a reasonable trade-off for a demonstrative implementation. However, against an optimal solver that can consistently solve Wordle in ~3.4 guesses, my implementation likely averages around 5-6 guesses depending on the target word.