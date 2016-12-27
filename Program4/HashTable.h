#ifndef _Hash_Table_H_
#define _Hash_Table_H_

#include <string.h>
#include <iostream>

#include "vector"
using namespace std;

class HashTable{

	struct HashEntry{
		HashTable *HTitem;
		char* Citem;
		int value;

		HashEntry(int i = -1): value(i){}
	};

		int start;
		int portSize;
		int packetSize;
		int packetCount;
		vector<HashEntry> table;

	public:
		HashTable(int tableSize): table(tableSize){
			portSize = tableSize;
			packetCount = 0;
			packetSize = 10;
			start = -1;
		}

		void insert(int portNum, int packetNum, char packet[257]){
			int index = portNum % portSize;
			while(table[index].value != -1 && table[index].value != portNum){ //while it is filled or not = to the right index
				if(index == portSize-1)
					index = -1;
				index++;
			}
			if(table[index].value == -1){ //if it is empty
				table[index] = HashEntry(portNum);
				table[index].HTitem = new HashTable(packetSize);
			}

			table[index].HTitem->insert(packetNum, packet);
		}

		void insert(int packetNum, char packet[257]){
			packetCount++;
			if(packetCount >= packetSize/2)
				rehash();
			int index = packetNum % packetSize;
			while(table[index].value != -1){
				if(index == packetSize-1)
					index = -1;
				index++;
			}

			table[index] = HashEntry(packetNum);
			table[index].Citem = packet;
		}

		char* getPort(int portNum){
			int index = portNum % portSize;
			while(table[index].value != portNum){
				if(index == portSize-1)
					index = -1;
				index++;
			}

			return (table[index].HTitem)->getPackets();
		}

		char* getPackets(){
			string message = "";
			for(int i = start+1; i < packetSize; i++){
				if(table[i].value != -1){
					message += (string)table[i].Citem;
					start = i;
				}
			}
			return const_cast<char*>(message.c_str());
		}

		void rehash(){
			table.resize(2*packetSize);
			packetSize *= 2;
		}
};

#endif