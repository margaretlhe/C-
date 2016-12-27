#ifndef MAXFLOW_H_INCLUDED
#define MAXFLOW_H_INCLUDED

#include "EvacRunner.h"
#include <vector>
#include <stack>

using namespace std;
class MaxFlow{
public:
	City* orig, *evac;
	int size;

	vector<EvacRoute> evacRoutes;
	//EvacRoute *evacRoutes;
	int esize;
	stack<City> s;
	int maxDepth;
	int depthSize;
	City* sources;

	MaxFlow(City *o, City *e, int s, int es): orig(o), evac(e), size(s), esize(es), maxDepth(0){};

	void createDFS();
	void recursionDFS(int depth, int visitedValue);
	static int sortCities(const void* a, const void* b);
	City* findCity(int cityID);

	void evacuate();
	City* getDepthCities(int depth);
	bool popInCities(City *current, int arraySize);
	bool evacueesInCities(int arraySize);
	void takePeople(int depth, int hour);
};

#endif // MAXFLOW_H_INCLUDED