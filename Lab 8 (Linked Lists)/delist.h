#ifndef DELIST_H
#define DELIST_H

struct DEItem {
  int val;
  DEItem* prev;
  DEItem* next;
};

class DEList {
 public:
  // Constructs an empty Double-Ended List
  DEList();
  // Destructor to clean-up memory of current list
  ~DEList();
  // returns a Boolean 'true' if the list is empty
  bool empty();
  // returns number of items in the list
  int size();
  // returns front item or -1 if empty list
  int front();
  // returns back item or -1 if empty list
  int back();
  // Adds a new integer to the front of the list
  void push_front(int new_val);
  // Adds a new integer to the back of the list
  void push_back(int new_val);
  // Removes the front item of the list (if it exists)
  void pop_front();
  // Removes the back item of the list (if it exists)
  void pop_back();

 private:
  // ADD your data members here:
  //add pointers to objects for the head and tail of the list
  DEItem* head; 
  DEItem* tail; 

};


#endif
