#include <iostream>
#include "delist.h"

using namespace std;

int main()
{
  DEList list;
  list.push_back(1);
  cout << "Added 1 to the list and now front is " << list.front() << endl;
  list.pop_front();
  cout << "Removed item" << endl;
  list.push_front(2);
  cout << "Added 2 to the list and now back is " << list.back() << endl;
  list.pop_back();
  cout << "Removed item" << endl;

  for(int i=0; i < 5; i++){
    list.push_back(10+i);
    list.push_front(20+i);
  }
  cout << "List size after adding 10 elements is " << list.size() << endl;
  while(!list.empty()){
    cout << "Popping front item = " << list.front() << endl;
    list.pop_front();
  }
  cout << "Trying to pop an item that doesn't exist" << endl;
  list.pop_front();

  cout << "Looking at values from front() and back() of empty list: ";
  cout << list.front() << " " << list.back() << endl;
  cout << "Repopulating list" << endl;
  for(int i=0; i < 5; i++){
    list.push_back(10+i);
    list.push_front(20+i);
  }
  while(!list.empty()){
    cout << "Popping back item = " << list.back() << endl;
    list.pop_back();
  }
  cout << "Trying to pop an item that doesn't exist" << endl;
  list.pop_back();

  list.push_back(100);
  list.push_front(101);
  cout << "Goodbye!" << endl;
  return 0;
}
