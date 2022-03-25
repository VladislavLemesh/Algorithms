#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class Graph
{
private:
	struct arc
	{
		int out;
		int in;
		int weight;
	};
	vector<arc> arcs;
	vector<int> vertex;
	map<int, bool> visited;
public:
	Graph();
	~Graph();
	void AddVertex(int number);
	void DeleteVertex(int number);
	void AddArcs(int out, int in);
	void DeleteArcs(int out, int in);
	void info();
	void DepthFirstSearch(int number);
	void BellmanFord(int out);
};
