/* 
mazeio.cpp

Author: Aidan McAlaine 

Short description of this file:
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a 
 *  2D dynamically  allocated array.
 * 
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem, 
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and 
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns 
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
   // FILL THIS IN
  
  //read in the file 
  ifstream ifile;
  ifile.open(filename); 
  if (ifile.fail()) {
    cout << "Couldn't open file" << endl; 
    return NULL; 
  }
  
  //read in values 
  ifile >> *rows >> *cols; 
  if (ifile.fail()) {
    cout << "No values to read in" << endl; 
    return NULL; 
  }
  char** maze = new char*[*rows]; 
  for (int i = 0; i < *rows; i++) {
    maze[i] = new char[*cols]; 
  }
  //need to assign the char values to maze
  char input; 
  
  for (int i = 0; i < *rows; i++) {
    for (int j = 0; j < *cols; j++) {
      ifile >> input; 
      if (ifile.fail()) {
        cout << "Nothing to read in!" << endl; 
        return NULL; 
      }
      maze[i][j] = input;       
    }
  }
  return maze; 
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols) 
{
   // FILL THIS IN
  cout << rows << " " << cols << endl; 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << maze[i][j]; 
    }
    cout << "\n"; 
  }
}

