#include <iostream>
#include "EvacRunner.h"
#include "MaxFlow.h"
#include <stdio.h>
#include <cstring>
#include "QueueLL.cpp"


using namespace std;

//x = depth
//y = is in queue
//City.y: found or in queue= -1, notFound = anything else

int min(int road, int source, int dest){
	int min = (road > source ? source:road);
	min = (min > dest ? dest:min);
	min = (0 > min ? 0:min);

	return min;
}

void MaxFlow::createBFS(){
	City *temp;// = NULL;
	QueueLL<City> q;

	for(int i = 0; i < esize; i++){
		temp = &orig[evac[i].ID]; //points to a city in orig
		temp->evacuees = temp->population;
		//temp->population = 0;

		temp->x = -1;
		temp->y = -1;
		q.enqueue(*temp);
	}

    City temp2;
    City *dest;
	//int num = 0;
	while(!q.isEmpty()){
		temp2 = q.dequeue();
		for(int i = 0; i < temp2.roadCount; i++) {
			dest = &orig[temp2.roads[i].destinationCityID];
			if(dest->y != -1) { // is not in queue or visited
				dest->y = -1;
				dest->x = temp2.x - 1;
				q.enqueue(*dest);
			}
		}
	}

	for(int i = 0; i < size; i++){
		if(-orig[i].x > maxDepth && -orig[i].x < maxDepth+10){
			maxDepth = -orig[i].x;
		}
	}
}
// -1 is in Path
// -2 is not in path

void MaxFlow::sortRoads(Road **roads, int left, int right){
	int i = left, j = right;
      Road tmp;
      Road pivot = (*roads)[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (-orig[(*roads)[i].destinationCityID].x < -orig[pivot.destinationCityID].x)
                  i++;
            while (-orig[(*roads)[j].destinationCityID].x > -orig[pivot.destinationCityID].x)
                  j--;
            if (i <= j) {
                  tmp = (*roads)[i];
                  (*roads)[i] = (*roads)[j];
                  (*roads)[j] = tmp;
                  i++;
                  j--;
            }
      }

      /* recursion */
      if (left < j)
            sortRoads(roads, left, j);
      if (i < right)
            sortRoads(roads, i, right);
}

void MaxFlow::evacuate(){
	int hour = 1;

	vector<City*> first = getDepthCities(1);
	vector<City*> second = getDepthCities(2);

	int moved = 0, moved2 = 0;
	int left = 0;
	for(int k = 0; k < esize; k++){
		left += first[k]->population;
		sortRoads(&(first[k]->roads), 0, first[k]->roadCount-1);
	}

	for(int k = 0; k < second.size(); k++){
		sortRoads(&(second[k]->roads), 0, second[k]->roadCount-1);
	}

	while(left > 0){
		moved2 = takePeople(second, hour);
		moved = takePeople(first, hour);
		left -= moved;
		hour++;
	}
}

vector<City*> MaxFlow::getDepthCities(int depth){
	vector<City*> temp;
	for(int i = 0; i < size; i++){
		if(orig[i].x == -depth)
			temp.push_back(&orig[i]);
	}
	return temp;
}

int MaxFlow::takePeople(vector<City*> sources, int hour){
	City *source = NULL; //lower
	City *dest = NULL; //upper
	EvacRoute er;
	int numToSend;
	int total = 0;

    for(int i = 0; i < (signed)sources.size(); i++){
		source = sources[i];
		for(int j = source->roadCount-1; j >= 0 ; j--){
			dest = &orig[source->roads[j].destinationCityID];
				if(-source->x <= -dest->x && dest->population >= dest->evacuees){
					numToSend = min(source->roads[j].peoplePerHour, source->evacuees, dest->population - dest->evacuees);

					source->evacuees -= numToSend;
					dest->evacuees += numToSend;
					er.numPeople = numToSend;

					if(dest->x != -1)
						total += numToSend;

					er.roadID = source->roads[j].ID;
					er.time = hour;
					if(numToSend > 0)
						evacRoutes.push_back(er);
				}
		}

    }
    return total;
}