//Authors: Matthew Gold and Margaret He

//#include "ExtendibleHash.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string.h>

/*b1
i115370
i184277
i9272
b2*/

using namespace std;
int Ehash(int value, int bits){
	int constant = 1 << (bits-1);
	if( value & constant )
		return 1;
	return 0;
} // Ehash()

//shiftdown() needs to decrement leaf count

ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) : bits(b), LeafSize(LSize){
	sigBit = 1; //which bits to look at.
	keySize = (int)pow(2, sigBit);
	leafCount = 1;
	keys = new int[keySize];
	keys[0] = 0;
	keys[1] = 1;
	children = new int*[keySize];
	children[0] = new int[1+LeafSize]; //[0] = size
	children[0][0] = 1; //index to insert at
	children[1] = children[0];
} // ExtendibleHash()

void ExtendibleHash::insert(const int &object){
	int index = find(object);
	if(index != -1 && children[index][0] < LeafSize){
		children[index][children[index][0]] = object;
		this->print();
		children[index][0]++; //lat possible: children[index][0] == leafsize, which is ok
	}
	else{
		split(object);
	}

    //cout << Ehash(object, 0) << Ehash(object, 1) << Ehash(object, 2) << endl;
} // insert()


void ExtendibleHash::remove(const int &object){
	int index = find(object);
	for(int i = 1; i < children[index][0]; i++){
		if(children[index][i] == object){
			//printf("V: %d\n", children[index][i]);
			shiftDown(i, index);
		}
	}
}  // remove()

void ExtendibleHash::shiftDown(int leafIndex, int childIndex){
	//printf("LI: %d CI: %d I: %d\n" , leafIndex, childIndex, children[childIndex][0]);
    for(int i = leafIndex; i < children[childIndex][0]-1; i++){
		//printf("check: %d %d\n", leafIndex, i);
		children[childIndex][i] = children[childIndex][i+1];
    }
	children[childIndex][0]--;
	//printf("LI: %d CI: %d I: %d\n" , leafIndex, childIndex, children[childIndex][0]);
}// shiftDown()

int ExtendibleHash::getBinary(int value, bool forResize){
	int number = 0;

	for(int i = 0; i < sigBit; i++){
		if(forResize)
			number += Ehash(value, i); //+0
		else
			number += Ehash(value, 18-i);
		number *= 10;
	}
	number /= 10; //significant bits
	//printf("number: %d %d\n", sigBit, number);
	return number;
}

const int & ExtendibleHash::find(const int &object){ //returns index of array where object would go/be found
	int index; //index of keys
	int number = getBinary(object, false);

	for(index = 0; index < keySize; index++)
		if(number == keys[index])
			return index;

	return -1;
}  // find()

void ExtendibleHash::split(const int &object){
	int iofa = find(object);
	if(children[iofa][0] < LeafSize && leafCount < keySize){
		printf("Changed Leaf\n");

		int og = Ehash(children[iofa][1], 18-sigBit+1);
		int newArray[LeafSize];
		newArray[0] = 0;
		for(int i = 2; i < LeafSize+1; i++){
			if(og != Ehash(children[iofa][i], 18-sigBit+1)){
				newArray[newArray[0]+1] = children[iofa][i];
				newArray[0]++;
				shiftDown(i, iofa);
			}
		}
		if(newArray[0] > 0){
			children[find(newArray[1])] = newArray;
			insert(object);
			printf("iiiiiiiii v");
            leafCount++;
			return;
		}
		else{
			newArray[0]++;
			newArray[1] = object;
			children[find(newArray[1])] = newArray;
			//int index = find(newArray[1]);
			leafCount++;
			this->print();
			//printf("[%d, %d]: %d\n", index, children[index][0], children[index][children[index][0]]);
			//printf("^ KeySize: %d, LeafCount: %d\n", keySize, leafCount);
			return;
		}

	}
	//else{
		//resize keys array and children array
		printf("Split\n"); 

		sigBit++;
		int keySize2 = pow(2, sigBit);
		int *nkeys = new int[keySize2];
		for(int i = 0; i < keySize2; i++){
			nkeys[i] = getBinary(i, true);
			//printf("%d\n", nkeys[i]);
		}
		int **nchildren = new int*[keySize2];
		for(int i = 0; i < keySize; i++){
			for(int j = 0; j < keySize2; j++){
				if(nkeys[j]/10 == getBinary(children[i][1], false))
					nchildren[j] = children[i];
			}
			//look at previous keys
			//if fist number in array start with that key (previous ones), assign key to point to that array
		}
		keySize = keySize2;
		keys = nkeys;
		children = nchildren;
		//sigBit++;
		leafCount++;
		insert(object);
	//}

}  // split()

void ExtendibleHash::print(){
	printf("\n");
	for(int i = 0; i < keySize; i++){
		printf("[%d]: ", i);
		for(int j = 0; j < LeafSize+1; j++){
			printf("%d, ", children[i][j]);
		}
		printf("\n");
	}
}