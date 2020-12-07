// wscramble.cpp
// Word Scramble guessing game
// Illustrates string library functions, character arrays,
//  arrays of pointers, etc.
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <fstream>

using namespace std;

// Scramble the letters of this string randomly
void permute(char items[], int len);

/* Delete the array below and replace by reading in words from a file 
   in main() */
//const char* wordBank[] = {
   //"computer", "president", "trojan", "program", "coffee",
   //"library", "football", "popcorn", "science", "engineer"};

//const int numWords = 10;

int main(int argc, char* argv[]) {
  srand(time(0));
  char guess[80];

  bool wordGuessed = false;
  int numTurns = 10;

  /* Add code to declare the wordBank array, read in each word
     and store it */
  
  if (argc < 2) {
    return 0; 
  }
  ifstream file;
  file.open(argv[1]); 
  if (file.fail()) {
    cout << "Couldn't open file" << endl; 
    return 0; 
  }
  //read in the integer
  int numWords; 
  file >> numWords; 
  if (file.fail()) {
    cout << "Didn't enter an int"; 
    return 0;
  }
  //dynamic memory allocation 
  char** wordBank;
  wordBank = new char* [numWords]; 
  
  //buffer array - use to copy the words into wordBank 
  char buffer [41]; 
  for (int i = 0; i < numWords; i++) {
    file >> buffer; 
    char* arr = new char[sizeof(buffer)]; 
    for (int i = 0; i < sizeof(buffer); i++) {
      arr[i] = buffer[i]; 
    } 
    //set address
    wordBank[i] = arr; 
  }
  //close input file 
  file.close(); 
    
  // Pick a random word from the wordBank
  int target = rand() % numWords;
  int targetLen = strlen(wordBank[target]);

  // Make a dynamically-allocated copy of the word and scramble it
  char* word = new char[targetLen+1];
  strcpy(word, wordBank[target]);
  permute(word, targetLen);
  
  // An individual game continues until a word
  //  is guessed correctly or 10 turns have elapsed
  while (!wordGuessed && numTurns > 0) {
    cout << "Scrambled word: " << word << endl;
    cout << "What do you guess the original word is? ";
    cin >> guess;
    /* Complete the next line of code */
    if (strcmp(guess, wordBank[target]) == 0) {
      wordGuessed = true; 
    }  
     // ADD code to check if the guess is equal to the chosen word.
                  // wordGuessed should be true if they are equal, and false otherwise
    
        
    numTurns--;   // Every guess counts as a turn
  }
  if (wordGuessed) {
    cout << "You win!" << endl;
  }
  else {
    cout << "Too many turns...You lose!" << endl;
  }
  /* Free up any necessary memory */
    
  delete [] word;
  //delete the individual contents within wordBank, which have been
  //dynamically allocated - this is where the error was
  for (int i = 0; i < numWords; i++) {
    delete [] wordBank[i]; 
  }
  
  delete [] wordBank; 
  return 0;
}

// Scramble the letters. See "Knuth shuffle".
void permute(char items[], int len) {
  for (int i = len-1; i > 0; --i) {
    int r = rand() % i;
    char temp = items[i];
    items[i] = items[r];
    items[r] = temp;
  }
}

