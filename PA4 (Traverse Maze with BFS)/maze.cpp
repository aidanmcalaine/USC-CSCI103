/* 
maze.cpp

Author:

Short description of this file:
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
   int rows, cols, result;
   char** mymaze=NULL;
   
   if(argc < 2)
   {
       cout << "Please provide a maze input file" << endl;
       return 1;
   }
   mymaze = read_maze(argv[1], &rows, &cols); // FILL THIS IN
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
   result = maze_search(mymaze, rows, cols); // TO BE CHANGED

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 2) {
     cout << "Error, input format incorrect" << endl; 
     return 1; 
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
   for (int i = 0; i < rows; i++) {
     delete[] mymaze[i]; 
   }
   delete[] mymaze; 
   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
  //Step 1
  Location start; 
  Location end; 
  int countS = 0; 
  int countF = 0; 
  bool path = false; 
  //check to see if the maze is valid 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      if (!(maze[i][j] == '#' || maze[i][j] == '.' || 
            maze[i][j] == 'S' || maze[i][j] == 'F')) {
        //means that the maze is not valid, because it contains a different characters
        cout << "Error, input format incorrect" << endl; 
        return -1; 
      }     
    }
  }
  //begin by finding the starting and finishing location 
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (maze[i][j] == 'S') {
        start.row = i; 
        start.col = j; 
        countS++; 
      }
      else if (maze[i][j] == 'F') {
        end.row = i; 
        end.col = j; 
        countF++; 
      }
    }
  }
  //return -1 if necessary
  if (!(countS == 1 && countF == 1)) {
    cout << "Maze is not valid" << endl; 
    return -1; 
  }
  
  //Step 2
  Location predecessorInitial; 
  predecessorInitial.row = -1; 
  predecessorInitial.col = -1; 
  
  //set up queue 
  Queue queue(rows*cols); 
  
  //create predecessor 
  Location** predecessor = new Location*[rows];
  for (int i = 0; i < rows; i++) {
    predecessor[i] = new Location[cols]; 
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      predecessor[i][j] = predecessorInitial; 
    }
  }
  
  //create visited array 
  int** visited = new int*[rows]; 
  for (int i = 0; i < rows; i++) {
    visited[i] = new int[cols]; 
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      visited[i][j] = 0; 
    }
  }
  
  //Step 3 
  
  //put the location into the queue
  queue.add_to_back(start); 
  //loop 
  while (!(queue.is_empty())) {
    
    //extract first location 
    Location curr = queue.remove_from_front();  
    
    //visit each neighbor 
    //North 
    Location north; 
    north.row = curr.row - 1; 
    north.col = curr.col; 
    //check to see if it in the array 
    if ((north.col >= 0 && north.col < cols) && 
             (north.row >= 0 && north.row < rows)) {
       
      //check if we have found the finish 
      if (maze[north.row][north.col] == 'F') {
        //backtrace
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col]; 
        }
        path = true; 
        break;   
      }
      
      //check to see if it is an open space
      else if (maze[north.row][north.col]== '.' 
               && visited[north.row][north.col] ==0) {
        //add it to the back of the queue
        queue.add_to_back(north);
        //mark it as visited 
        visited[north.row][north.col] = 1; 
        //record predecessor 
        predecessor[north.row][north.col] = curr; 
      }
    }
        
    //West
    Location west; 
    west.row = curr.row; 
    west.col = curr.col - 1; 
    //check to see if it in the array 
    if ((west.col >= 0 && west.col < cols) && 
             (west.row >= 0 && west.row < rows)) {  
      
      //check if we have found the finish 
      if (maze[west.row][west.col] == 'F') {
        //backtrace
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col];  
        }
        path = true; 
        break; 
      }
          
      //check to see if it is an open space
      else if (maze[west.row][west.col]=='.' && 
               visited[west.row][west.col] == 0) {  
        //add it to the back of the queue
        queue.add_to_back(west);
        //mark it as visited 
        visited[west.row][west.col] = 1; 
        //record predecessor 
        predecessor[west.row][west.col] = curr; 
      }
    }
         
    //South
    Location south; 
    south.row = curr.row + 1; 
    south.col = curr.col; 
     //check to see if it in the array 
    if ((south.col >= 0 && south.col < cols) && 
             (south.row >= 0 && south.row < rows)) {
           
      //check if we have found the finish 
      if (maze[south.row][south.col] == 'F') {
        //if f, then we can backtrace until we find S
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col];  
        }
        path = true; 
        break;   
      }
     
       //check to see if it is an open space
      else if (maze[south.row][south.col] =='.' 
               && visited[south.row][south.col] == 0) {     
        //add it to the back of the queue
        queue.add_to_back(south);
        //mark it as visited 
        visited[south.row][south.col] = 1; 
        //record predecessor 
        predecessor[south.row][south.col] = curr; 
      }
    }
       
    //East
    Location east; 
    east.row = curr.row; 
    east.col = curr.col + 1;     
     //check to see if it in the array 
    if ((east.col >= 0 && east.col < cols) && 
             (east.row >= 0 && east.row < rows)) {
      
      //check if we have found the finish 
      if (maze[east.row][east.col] == 'F') {
        //backtrace
        while (maze[curr.row][curr.col] != 'S') {
          maze[curr.row][curr.col] = '*'; 
          curr = predecessor[curr.row][curr.col]; 
         
        }
        path = true; 
        break;   
      }
      //check to see if it is an open space
      else if (maze[east.row][east.col]=='.' 
               && visited[east.row][east.col] == 0) {
        //add it to the back of the queue
        queue.add_to_back(east);
        //mark it as visited 
        visited[east.row][east.col] = 1; 
        //record predecessor 
        predecessor[east.row][east.col] = curr; 
      }
    }
  }
  
  //Delete all memory 
  for (int i = 0; i < rows; i++) {
    delete[] predecessor[i]; 
    delete[] visited[i]; 
  }
  delete[] predecessor; 
  delete[] visited; 
  
  //return correct values 
  if (path) {
    return 1; 
  }
  else {
    return 0; 
  }
}
