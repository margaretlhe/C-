#include <cstdlib>
#include "evac.h"
#include <string.h>
//#include "EvacRunner.h"

using namespace std;

Evac::Evac(City *citie, int numCitie, int numRoad): numCities(numCitie){
	cities = new City[numCitie];
	for(int i = 0; i < numCitie; i++)
		cities[i] = citie[i];

	sortCities(0, numCitie-1);
} // Evac()


void Evac::evacuate(int *evacIDs, int numEvacs, EvacRoute *evacRoutes, int &routeCount){
	City destroyed[numEvacs];
	for(int i = 0; i < numEvacs; i++)
		destroyed[i] = cities[evacIDs[i]];

	maxflow = new MaxFlow(cities, destroyed, numCities, numEvacs);
	maxflow->createBFS();
	maxflow->evacuate();

	routeCount = maxflow->evacRoutes.size();
	for(int i = 0; i < routeCount; i++)
		evacRoutes[i] = maxflow->evacRoutes[i];
} // evacuate

void Evac::sortCities(int left, int right){
	int i = left, j = right;
      City tmp;
      City pivot = cities[(left + right) / 2];

      /* partition */
      while (i <= j) {
            while (cities[i].ID < pivot.ID)
                  i++;
            while (cities[j].ID > pivot.ID)
                  j--;
            if (i <= j) {
                  tmp = cities[i];
                  cities[i] = cities[j];
                  cities[j] = tmp;
                  i++;
                  j--;
            }
      };

      /* recursion */
      if (left < j)
            sortCities(left, j);
      if (i < right)
            sortCities(i, right);
}