// Matthew Gold and Margaret He

//#include "ExtendibleHash.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>

using namespace std;

int ExtendibleHash::Ehash(int value, int bits)
{
	return value >> (18 - bits) ; //might cause segfault if bits are greater than integer
} // Ehash()

//shiftdown() needs to decrement leaf count

//initialize 
ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) : bits(b), LeafSize(LSize)
{
	sigBit = 1; //which bits to look at.
	keySize = (int)pow(2, sigBit);
	leafCount = 1;
	keys = new int[keySize];
	keys[0] = 0;
	keys[1] = 1;
	children = new int*[keySize];
	children[0] = new int[1+LeafSize]; //[0] = size
	children[1] = children[0];
} // ExtendibleHash()

void ExtendibleHash::insert(const int &object)
{
	int index = find(object);
	if(children[index][0] < LeafSize){
		children[index][0]++; //lat possible: children[index][0] == leafsize, which is ok
		children[index][children[index][0]] = object;
	}
	else{
		split(object);
	}

    //cout << Ehash(object, 0) << Ehash(object, 1) << Ehash(object, 2) << endl;
} // insert()


void ExtendibleHash::remove(const int &object)
{
	int index = find(object);
	for(int i = 1; i < children[index][0]; i++){
		if(children[index][i] == object){
			shiftDown(i, index);
		}
	}
}  // remove()

void ExtendibleHash::shiftDown(int leafIndex, int childIndex)
{
    for(int i = leafIndex; i < children[childIndex][0]-1; i++)
		children[childIndex][i] = children[childIndex][i+1];
	children[childIndex][0]--;
}// shiftDown()

int ExtendibleHash::getBinary(int value)
{
	int number = 0;

	for(int i = 0; i < sigBit; i++){
		number += Ehash(value, i);
		number *= 10;
	}
	number /= 10; //significant bits
	return number;
}

int & ExtendibleHash::find(const int &object) //returns index of array where object would go/be found
{ 
	int* ind = 0; //index of keys
	int number = getBinary(object);

	for(*ind = 0; *ind < keySize; ind++)
	{
		if(number == keys[*ind])
		{
			return *ind;
		}
	}
	*ind = -1;
	return *ind;
}  // find()

void ExtendibleHash::split(const int &object)
{
	//find odd ones out and create a new array
	//find the index
	//assign that index to the new array

	if(leafCount < keySize)
	{

		int iofa = find(object);//index of full array, if returns -1
		int og = Ehash(children[iofa][0], sigBit-1);
		int newArray[LeafSize];
		int arrayCount = 0;
		for(int i = 1; i < LeafSize+1; i++)
		{
			if(og != Ehash(children[iofa][i], sigBit-1))
			{
				newArray[arrayCount] = children[iofa][i];
				shiftDown(i, iofa);
				
			}
		}
		children[find(newArray[0])] = newArray; //assign new parent
	}
	else{
		//resize keys array and children array
		sigBit++;
		keySize = pow(2, sigBit);
		for(int i = 0; i < keySize; i++)
		{
			int* nkeys = new int[keySize];
			int** nchildren = new int*[keySize];
			memcpy(nkeys, keys, keySize * sizeof(int)); //copy old contents into new keys array
			memcpy(nchildren, children, keySize * sizeof(int)); //copy old contents into new children array
			delete [] keys;
			delete [] children;
			keys = nkeys;
			children = nchildren;
			
		}
		leafCount++;
	}
	insert(object);

}  // split()
