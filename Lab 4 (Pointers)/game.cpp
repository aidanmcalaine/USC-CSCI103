// game.cpp
// Hangman game illustrates string library functions, 
// character arrays, arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// Prototype. we'll define this below.
int processGuess(char* word, const char* targetWord, char guess);

// Define an array of strings (since a string is just a char array)
//  and since string are just char *'s, we really want an array of char *'s
const char* wordBank[] = {"computer", "president", "trojan", "program",
                          "coffee", "library", "football", "popcorn", 
                          "science", "engineer"};

const int numWords = 10;

int main()
{
  srand(time(0));
  char guess;
  bool wordGuessed = false;
  int numTurns = 10;
  int counter = 0; 

  // Pick a random word from the wordBank
  const char* targetWord = wordBank[rand() % numWords];

  // More initialization code as needed
  char word[80];  // a blank array to use to build up the answer
                  // It should be initialized with *'s and then
                  //  change them to the actual letters when the 
                  //  user guesses the letter
  
  //initialize with *s
  for (int i = 0; i < strlen(targetWord); i++) {
    word[i] = '*'; 
  }
  word[strlen(targetWord)] = '\0'; 
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (numTurns != 0) {
    //print out current word
    cout << "Current word: " << word << endl;
    
    //prompt/take input
    cout << numTurns << " remain...Enter a letter to guess:" << endl; 
    cin >> guess; 
 
    counter = processGuess(word, targetWord, guess);  
    if (counter == 0) {
      numTurns -= 1; 
    }
    if (strcmp(word, targetWord) == 0) {
      cout << "You won!" << endl; 
      return 0; 
    }
  }
  // Print out end of game status
  cout << "You lost!" << endl; 
  return 0;
}

// Given the current version of the word, target/selected word, and
// the character that the user just guessed, change the word to 
// "turn on" any occurrences the guess character and return a count
// of how many occurrences of 'guess' were found
int processGuess(char* word, const char* targetWord, char guess)
{
  int count = 0;
  //check if the letter exists
  for (int i = 0; i < strlen(targetWord); i++) {
    if (targetWord[i] == guess) {
      word[i] = guess; 
      count++; 
    }
  }
  return count; 
}