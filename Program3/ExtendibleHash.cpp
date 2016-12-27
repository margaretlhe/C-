//Authors: Matthew Gold and Margaret He

#include "ExtendibleHash.h"
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <iterator> 
#include <vector>



using namespace std;
vector<char> ExtendibleHash::Ehash(int value){
	vector<char> ret;
	int i = 0;
	while(i < 18) {
		if (value&1)
			ret.push_back('1');
		else
			ret.push_back('0');
    value>>=1;
    i++;
  }
  reverse(ret.begin(),ret.end());
  return ret;
} // Ehash()

//shiftdown() needs to decrement leaf count

ExtendibleHash::ExtendibleHash(const int & notFound, int b, int LSize) : bits(b), LeafSize(LSize){
	sigBit = 1; //which bits to look at.
	keySize = (int)pow(2, sigBit);
	leafCount = 1;
	keys = new string[keySize];
	keys[0] = "0";
	keys[1] = "1";
	children = new int*[keySize];
	children[0] = new int[1+LeafSize]; //[0] = size
	children[0][0] = 1; //index to insert at
	children[1] = children[0];

	notThere = notFound;
} // ExtendibleHash()

void ExtendibleHash::insert(const int &object){
	int index = findIndex(object);
	if(children[index][0] <= LeafSize){
		children[index][children[index][0]] = object;
		children[index][0]++; //lat possible: children[index][0] == leafsize, which is ok
		printf("\nInserted: %d:", object);
		this->print();
	}
	else{
		changeLeaf(index, object);
	}
} // insert()


void ExtendibleHash::remove(const int &object){
	int index = findIndex(object);
	for(int i = 1; i < children[index][0]+1; i++){
		if(children[index][i] == object){
			shiftDown(i, index);
			break;
		}
	}
	printf("\nDeleted: %d:", object);
	this->print();
}  // remove()

void ExtendibleHash::shiftDown(int leafIndex, int childIndex){
    for(int i = leafIndex; i < children[childIndex][0]; i++){
		children[childIndex][i] = children[childIndex][i+1];
    }

    if(leafIndex == children[childIndex][0])
		children[childIndex][leafIndex] = 0;

	children[childIndex][0] = children[childIndex][0]-1;
}// shiftDown()

string ExtendibleHash::getBinary(vector<char> v, int howMany = 8){
	string number = "";
	for(int i = 0; i < (int)v.size() && i < howMany; i++){
		number += v.at(i);
	}
	return number;
}

int ExtendibleHash::findIndex(const int &object){ //returns index of array where object would go/be found
	int index; //index of keys
	string number = getBinary(Ehash(object), sigBit);

	for(index = 0; index < keySize; index++){
		if(!number.compare(keys[index]))
			break;
	}

	return index;
}  // find()

void ExtendibleHash::changeLeaf(int childIndex, const int &object){
	string orig = getBinary(Ehash(children[childIndex][1]), sigBit); //returns the important bit
	int *nleaf = new int[LeafSize];
	nleaf[0] = 0;

	for(int i = 2; i < children[childIndex][0]; i++){ //start with comparing second value
		//cout << "\n" << orig << ":" << getBinary(Ehash(children[childIndex][i]), sigBit);
		if(orig != getBinary(Ehash(children[childIndex][i]), sigBit)){//if the bits differ
			nleaf[0]++;
			nleaf[nleaf[0]] = children[childIndex][i];
			shiftDown(i, childIndex);
			i--;
		}
	}

	bool isequal = false;
	for(int i = 0; i < keySize; i++){
		if(children[findIndex(object)] == children[i] && findIndex(object) != i)
			isequal = true;
	}


	if(nleaf[0] > 0){ //after leaves are rearranged, the value is inserted again
		children[findIndex(nleaf[1])] = nleaf;
		insert(object);
		leafCount++;
		printf("\nChanged Leaf 1: %d", object);
		this->print();
	}
	else if(!isequal){ //if the new value must be added to a full leaf
		split(object);
	}
	else{ //the leaf was not rearranged but the value goes into a new node
		nleaf[0]++;
		nleaf[1] = object;
		nleaf[0]++;
		children[findIndex(object)] = nleaf;
		leafCount++;
		printf("\nChanged Leaf 2: %d", object);
		this->print();
	}
}

void ExtendibleHash::split(const int &object){
	//vector<int> nkeys;
	vector<int> nchildren;
	sigBit++;
	cout << "sigBit: " << sigBit << endl;
	int index = sigBit;
	int nsize = pow(2, sigBit);
	cout << "nsize: " << nsize << endl;
	string *nkeys = new string[nsize];
	for(int i = 0; i < nsize; i++){
		nkeys[i] = getBinary(Ehash(i), 18).substr(18-index, 18);
	} //re assigns key array
	//int **nchildren = new int*[nsize];
	cout << "keySize: " << keySize << endl;
	for(int i = 0; i < keySize; i++){
		for(int j = 0; j < nsize; j++){
			if(nkeys[j].substr(0, nkeys[j].size()-1) == getBinary(Ehash(children[i][1]), sigBit-1)){
				//nchildren[j] = children[i]; 
				nchildren.assign(children, children + children[i][0]); ////copy contents of array into 
				nchildren.resize(nsize); //resize vector
				
				
			}
		} //reassigns the appropriate pointers
	}
	keySize = nsize;
	keys = nkeys;
	//children = nchildren;
	leafCount++;
	bits++; 
	printf("\nSplit: %d", object);
	this->print();
	insert(object);
}  // split()

void ExtendibleHash::print(){
	printf("\n");
	for(int i = 0; i < keySize; i++){
		cout << keys[i] << ": ";
		for(int j = 0; j < children[i][0]; j++){
			cout << children[i][j] << ", ";
		}
		printf("\n");
	}
}

const int & ExtendibleHash::find(const int &object){
	for(int i = 0; i < keySize; i++){
		for(int j = 0; j < children[i][0]; j++){
			if(children[i][j] == object)
				return object;
		}
	}
	return notThere;
}