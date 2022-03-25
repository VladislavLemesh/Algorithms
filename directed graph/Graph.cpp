#include "Graph.h"

Graph::Graph()
{
	ifstream fin;
	fin.open("Info.txt");
	if (fin.is_open())
	{
		int size, outGraphValue = -1, inGraphValue = -1, weightGraphValue = -1;
		bool arcExists = false;
		if (fin.peek() == EOF)
		{
			cout << "Fail empty" << endl;
			exit(0);
		}
		else
		{
			fin >> size;
			if ((size < 5) || (size > 100))
			{
				cout << "incorrect value" << endl;
				exit(0);
			}
			vertex.resize(size);
			for (int i = 0; i < size; i++)
			{
				vertex[i] = i + 1;
			}
			for (int i = 0; !fin.eof(); i++)
			{
				fin >> outGraphValue;
				fin >> inGraphValue;
				arcExists = false;
				for (int i = 0; i < arcs.size(); i++)
				{
					if ((outGraphValue == arcs[i].out) && (inGraphValue == arcs[i].in))
					{
						fin >> weightGraphValue;
						arcExists = true;
					}
				}
				if (arcExists)
				{
					continue;
				}
				if ((outGraphValue < 1) || (outGraphValue > size))
				{
					cout << "incorrect value" << endl;
					exit(0);
				}
				arcs.push_back({ outGraphValue,0,0 });
				if ((inGraphValue < 1) || (inGraphValue > size))
				{
					cout << "incorrect value" << endl;
					exit(0);
				}
				arcs[i].in = inGraphValue;
				fin >> weightGraphValue;
				if (weightGraphValue < 1)
				{
					cout << "incorrect value" << endl;
					exit(0);
				}
				arcs[i].weight = weightGraphValue;
			}
			for (int j = 1; j < arcs.size(); j++)
			{
				for (int i = 0; i < arcs.size() - 1; i++)
				{
					if (arcs[i].out > arcs[i + 1].out)
					{
						auto t = arcs[i];
						arcs[i] = arcs[i + 1];
						arcs[i + 1] = t;
					}
				}
			}
			for (int j = 1; j < arcs.size(); j++)
			{
				for (int i = 0; i < arcs.size() - 1; i++)
				{
					if ((arcs[i].out == arcs[i + 1].out) && (arcs[i].in > arcs[i + 1].in))
					{
						auto t = arcs[i];
						arcs[i] = arcs[i + 1];
						arcs[i + 1] = t;
					}
				}
			}
		}
	}
	else
	{
		cout << "could not open file" << endl;
		exit(0);
	}
	fin.close();
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		visited.emplace((*it), false);
	}
}

Graph::~Graph()
{
	arcs.clear();
	vertex.clear();
}

void Graph::AddVertex(int number)
{
	if (number > vertex.size())
	{
		cout << "the vertex number must not exceed the size of the graph" << endl;
		return;
	}
	for (int i = 0; i < vertex.size(); i++)
	{
		if (vertex[i] == number)
		{
			cout << "vertex already exists" << endl;
			return;
		}
	}
	vertex.push_back(number);
	for (int j = 1; j < vertex.size(); j++)
	{
		for (int i = 0; i < vertex.size() - 1; i++)
		{
			if (vertex[i] > vertex[i + 1])
			{
				auto t = vertex[i];
				vertex[i] = vertex[i + 1];
				vertex[i + 1] = t;
			}
		}
	}
}

void Graph::DeleteVertex(int number)
{
	if (!arcs.empty())
	{
		for (vector<arc>::iterator it = arcs.begin(); it != arcs.end();)
		{
			if (((*it).out == number) || ((*it).in == number))
			{
				it = arcs.erase(it);
				continue;
			}
			it++;
		}
	}
	if (vertex.empty())
	{
		cout << "GraphNotExist" << endl;
		return;
	}
	else
	{
		for (vector<int>::iterator it = vertex.begin(); it != vertex.end(); it++)
		{
			if ((*it) == number)
			{
				vertex.erase(it);
				return;
			}
		}
		cout << "vertex not found" << endl;
	}
}

void Graph::AddArcs(int out, int in)
{
	int c = 0;
	int weight;
	for (int i = 0; i < arcs.size(); i++)
	{
		if ((out == arcs[i].out) && (in == arcs[i].in))
		{
			cout << "arcs already exists" << endl;
			return;
		}
	}
	for (int i = 0; i < vertex.size(); i++)
	{
		if ((out != vertex[i]))
		{
			c++;
		}
		if (c == vertex.size())
		{
			cout << "vertex not found" << endl;
			return;
		}
	}
	c = 0;
	for (int i = 0; i < vertex.size(); i++)
	{
		if ((in != vertex[i]))
		{
			c++;
		}
		if (c == vertex.size())
		{
			cout << "vertex not found" << endl;
			return;
		}
	}
	cout << "enter weight: ";
	cin >> weight;
	if (weight > 0)
	{
		arcs.push_back({ out, in, weight });
		for (int j = 1; j < arcs.size(); j++)
		{
			for (int i = 0; i < arcs.size() - 1; i++)
			{
				if (arcs[i].out > arcs[i + 1].out)
				{
					auto t = arcs[i];
					arcs[i] = arcs[i + 1];
					arcs[i + 1] = t;
				}
			}
		}
		for (int j = 1; j < arcs.size(); j++)
		{
			for (int i = 0; i < arcs.size() - 1; i++)
			{
				if ((arcs[i].out == arcs[i + 1].out) && (arcs[i].in > arcs[i + 1].in))
				{
					auto t = arcs[i];
					arcs[i] = arcs[i + 1];
					arcs[i + 1] = t;
				}
			}
		}
	}
	else
	{
		cout << "incorrect value" << endl;
	}
}

void Graph::DeleteArcs(int out, int in)
{
	if (!arcs.empty())
	{
		for (vector<arc>::iterator it = arcs.begin(); it != arcs.end(); it++)
		{
			if ((out == (*it).out) && (in == (*it).in))
			{
				it = arcs.erase(it);
				it = it - 1;
			}
		}
	}
	else
	{
		cout << "the list of graph arcs is empty";
		return;
	}
}

void Graph::info()
{
	auto it = vertex.begin();
	int i = 1;
	while (it != vertex.end())
	{
		int sumArcs = 0;
		if ((*it) == i)
		{
			for (int j = 0; j < arcs.size(); j++)
			{
				if (arcs[j].out == (*it))
				{
					sumArcs++;
				}
			}
			cout << i << "\t" << sumArcs << "\t";
			for (int j = 0; j < arcs.size(); j++)
			{
				if (arcs[j].out == (*it))
				{
					cout << arcs[j].in << "\t";
				}
			}
			cout << endl;
			it = it + 1;
			i++;
		}
		else
		{
			cout << i << "\t" << endl;
			i++;
		}
	}
}

void Graph::DepthFirstSearch(int number)
{
	visited[number] = true;
	cout << number << "\t";
	for (auto itArcs = arcs.begin(); itArcs != arcs.end(); itArcs++)
	{
		if ((*itArcs).out == number)
		{
			if (!visited[(*itArcs).in])
			{
				DepthFirstSearch((*itArcs).in);
			}
			else return;
		}
	}
}

void Graph::BellmanFord(int out)
{
	int V = vertex.size();
	int E = arcs.size();
	vector<int> dist;
	dist.resize(V + 1);

	for (int i = 0; i <= V; i++)
	{
		dist[i] = INT_MAX;
	}
	dist[out] = 0;

	for (int i = 1; i <= V; i++) {
		for (int j = 0; j < E; j++) {
			int u = arcs[j].out;
			int v = arcs[j].in;
			int weight = arcs[j].weight;
			if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	cout << "Distance from vertex\n" << endl;
	for (int i = 1; i <= V; ++i)
		if (dist[i] != INT_MAX)
		{
			cout << i << "\t" << dist[i] << endl;
		}
		else
		{
			cout << i << "\t" << "arcs not found" << endl;
		}
	return;
}