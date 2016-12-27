// Author: Sean Davis
#ifndef evacH
#define evacH

#include "EvacRunner.h"
#include "MaxFlow.h"


class Evac{

	int numCities;
	City *cities;
	MaxFlow *maxflow;


public:
	Evac(City *c, int nc, int nR);
	void evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes, int &routeCount); // student sets evacRoutes and routeCount

	City findCity(int cityID);
	void sortCities(int left, int right);

}; // class Evac



#endif