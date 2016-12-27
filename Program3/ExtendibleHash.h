//Matthew Gold, Margaret He

#ifndef EXTENDIBLE_HASH_H
  #define EXTENDIBLE_HASH_H

#include <vector>
#include <string>
using namespace std;

class ExtendibleHash
{
  int bits;
  int sigBit;
  int keySize;
  int leafCount;
  int LeafSize;
  string *keys;
  int **children;
  int notThere;

public:
  ExtendibleHash(const int & notFound, int s, int LSize = 2);
  void insert(const int &object);
  void remove(const int &object);
  const int & find(const int &object);
  void split(const int &object);
  int GetBits()const {return bits;}

 std::vector<char> Ehash(int value);
  void shiftDown(int leafIndex, int childIndex);
  string getBinary(vector<char> v, int howMany);
  void print();
  void changeLeaf(int childIndex, const int &object);
  int findIndex(const int &object);


}; // class ExtendibleHashing

#include "ExtendibleHash.cpp"

#endif