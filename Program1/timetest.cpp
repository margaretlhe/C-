//Jordan Schultz, Margaret He
#include "CPUTimer.h"
#include "dsexceptions.h"
#include "vector.h" 
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "SkipList.h"
#include <iostream>
#include <fstream>
#include <string>
vector<CursorNode<int> > cursorSpace(250000);

using namespace std;
  
void RunList(string filename);
void RunCursorList(string filename);
void RunStackAr(string filename);
void RunStackLi(string filename);
void RunQueueAr(string filename);
void RunSkipList(string filename);
int getChoice();

int main()
{
  int choice;
  string filename; 
  ifstream inf;
  CPUTimer timer;
  
  cout << "Filename >> ";
  cin >> filename;


    
    do{
      choice = getChoice();
      timer.reset();
      switch(choice)
      {
        case 1: RunList(filename); break;
        case 2: RunCursorList(filename); break;
        case 3: RunStackAr(filename); break;
        case 4: RunStackLi(filename); break;
        case 5: RunQueueAr(filename); break;
        case 6: RunSkipList(filename); break;  
      }
     
	  cout << "CPU time: " << timer.cur_CPUTime() << endl;
 
    } while(choice > 0);
  

  return 0;

}//main

int getChoice()
{
  int num;
  cout << "" << endl;
  cout << "      ADT Menu" << endl; 
  cout << "0. Quit\n1. LinkedList\n2. CursorList\n3. StackAr" << endl; 
  cout << "4. StackLi\n5. QueueAr\n6. SkipList\nYour choice >> "; 
  cin >> num;
  
  return num;       
  
  
} 
	
	

void RunList(string filename)
{
  char command;
  int value;
  ifstream inf;
  inf.open(filename.c_str());
  inf.ignore(1000, '\n');
  List <int> a; // test obj

  while(inf >> command >> value)
  { //loops through entire file, first string is stored within command, int in value  
    
    if(command == 'i')
    {
      a.insert(value,  a.zeroth()); 
    }

    if(command == 'd')
    {
      a.remove(value); 
  
    }
    //delete from linked list
 
     
  }
}//runList   

void RunCursorList(string filename)
{
  char command;
  int value;
  ifstream inf;
  inf.open(filename.c_str());
  inf.ignore(1000, '\n');
  CursorList <int> a(cursorSpace); // test obj
  
  while(inf >> command >> value)
  { //loops through entire file, first string is stored within command, int in value
 
    if(command == 'i')
    {
    a.insert(value,  a.zeroth());
    }
 
    if(command == 'd')
    {
    a.remove(value);
    }

  }

 
 
}

void RunStackAr(string filename)
{
  char command;
  int value;
  ifstream inf;
  inf.open(filename.c_str());
  inf.ignore(1000, '\n');
  StackAr <int> a(250000); // test object

  while(inf >> command >> value)
  { //loops through entire file, first string is stored within command, int in value

    if(command == 'i')
    {
    a.push(value);
    }

    if(command == 'd')
    {
    a.pop();

    }


  }
}

 
void RunStackLi(string filename)
{
  char command;
  int value;
  ifstream inf;
  inf.open(filename.c_str());
  inf.ignore(1000, '\n');
  StackLi <int> myStack;
    
    while(inf >> command >> value)
    { //loops through entire file, first string is stored within command, int in value

      if(command == 'i')
      {
      myStack.push(value);
      }

      if(command == 'd')
      {
      myStack.pop();

      }

    }    			
}

void RunQueueAr(string filename)
{
  char command;
  int value;
  ifstream inf;
  inf.open(filename.c_str());
  inf.ignore(1000, '\n');
  Queue <int> myQ(250000);

    while(inf >> command >> value)
    { //loops through entire file, first string is stored within command, int in value

      if(command == 'i')
      {
        myQ.enqueue(value);
      }

      if(command == 'd')
      {
        myQ.dequeue();
      }

    }

}

void RunSkipList(string filename)
{
  char command;
  int value;
  ifstream inf;
  inf.open(filename.c_str());
  inf.ignore(1000, '\n');
  SkipList <int> mySkip(0, 250000);

    while(inf >> command >> value)
    { //loops through entire file, first string is stored within command, int in value

      if(command == 'i')
      {
        mySkip.insert(value);
      }

      if(command == 'd')
      {
        mySkip.deleteNode(value);

      }

    }

}		