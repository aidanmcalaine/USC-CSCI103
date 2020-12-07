#include "delist.h"
#include <iostream> 

using namespace std; 

DEList::DEList() {
  //constructs an empty double ended list
  head = NULL; 
  tail = NULL; 
}
DEList::~DEList() {
  //destructor to clean up memory of current list
  DEItem* temp = head; 
  //iterate through nodes from head to tail 
  while (temp != tail) {
    head = head->next; 
    delete temp; 
    temp = head; 
  }
  //delete last node
  delete head; 
}

bool DEList::empty() {
  //returns a Boolean 'true' if the list is empty
  if (head == NULL&& tail == NULL) {
    return true; 
  } 
  else{
    return false; 
  }
}
int DEList::size() {
  if (empty()) {
    return 0; 
  }
  int size = 0; 
  DEItem* temp = head; 
  //Iterate through the objects in the list 
  while (temp != NULL) {
    size++; 
    temp = temp->next; 
  }
  return size; 
}
int DEList::front() {
  //returns front item or -1 if an empty list 
  if (!empty()) {
    return head->val; 
  }
  else {
    return -1; 
  }
}
int DEList::back() {
  //returns back item or -1 if an empty list
  if (!empty()) {
    return tail->val; 
  }
  else {
    return -1; 
  }
}
void DEList::push_front(int new_val) {
  //add a new integer to the front of the list
  DEItem* newItem = new DEItem; 
  //give newItem the correct value 
  newItem->val = new_val; 
  //next should be head, prev should be null 
  newItem->next = head; 
  newItem->prev = NULL; 
  //if empty, both head and tail should update 
  if (empty()) {
    head = newItem; 
    tail = newItem; 
  }
  //if not empty, only head will update, not tail 
  else {
    head->prev = newItem; 
    head = newItem; 
  }
}
void DEList::push_back(int new_val) {
  //add a new integer to the front of the list
  DEItem* newItem = new DEItem; 
  //give newItem the correct value 
  newItem->val = new_val; 
  //next should be null, prev should be tail 
  newItem->next = NULL; 
  newItem->prev = tail; 
  //if empty, both head and tail should update
  if (empty()) {
    head = newItem; 
    tail = newItem; 
  }
  //if not empty, only tail will update, not head
  else {
    tail->next = newItem; 
    tail = newItem; 
  }
}
void DEList::pop_front() {
  //remove the front item of the list (if it exists)
  if (!empty()) {
    //if list only has 1 element 
    if (size() == 1) {
      delete head;       
      head = NULL; 
      tail = NULL; 
    }
    else {
      //create new variable for 2nd item in list and delete first
      DEItem* temp = head->next;
      temp->prev = NULL; 
      delete head; 
      head = temp; 
    }
  }
  else {
    cerr << "This list is already empty" << endl; 
  } 
}
void DEList::pop_back() {
  if (!empty()) {
    //if there is 1 element
    if (size() == 1) {
      delete head;      
      head = NULL; 
      tail = NULL; 
    }
    else {
      //create a new variable for 2nd to last item and delete last
      DEItem* temp = tail->prev; 
      temp->next = NULL; 
      delete tail; 
      tail = temp; 
    }
  }
  else {
    cerr << "This list is already empty" << endl; 
  }  
}