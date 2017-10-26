#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <functional>
using namespace std;

//DEFINE THE VALUE 
#define NAME_FILE_SOURCE  "input.txt"
#define DEPTH_FIRST_SEARCH 1
#define BREATH_FIRST_SEARCH 2
#define UNIFORM_COST_SEARCH 3
#define GREENDY_BEST_FIRST_SEARCH 4
#define A_STAR_ALGORITHM 5
struct VertiCleGraph
{
	int nextVerticle;
	int distance;
};

int number_verticle;
int start_verticle;
int end_verticle;
vector <VertiCleGraph> *graph;
int *heristicValue;

int *path_of_depth_first_search;
int *path_of_breadth_first_search;
int *path_of_uniform_cost_search;
int *path_of_A_star_search;

vector<int> trace_of_depth_first_search;
vector<int> trace_of_breadth_first_search;
vector<int> trace_of_uniform_cost_search;
vector<int> trace_of_A_star_search;

//fucntion prototype
void ReadInputFile();
void DepthFirtSerach();
void BreadthFirstSearch();
void UniformCostSearch();
void AStarAlgorithm();


void ReadInputFile()
{
	ifstream in; in.open(NAME_FILE_SOURCE);//read file input
	in >> number_verticle;//read the number verticle of graph
	in >> start_verticle >> end_verticle;//read the start and end verticle

	graph = new vector<VertiCleGraph>[number_verticle];
	heristicValue = new int[number_verticle];


	//read imfomation for graph
	for (int i = 0; i < number_verticle; i++)
	{
		for (int j = 0; j < number_verticle; j++)
		{
			int temp;
			in >> temp;
			if (temp)
			{
				VertiCleGraph source;
				source.nextVerticle = j;
				source.distance = temp;
				graph[i].push_back(source);
			}
		}
	}

	//read heristic
	for (int i = 0; i < number_verticle; i++)
	{
		in >> heristicValue[i];
	}
}

void DepthFirtSerach()
{
	bool  *checkVisited = new bool[number_verticle];
	path_of_depth_first_search = new int[number_verticle];


	for (int i = 0; i < number_verticle; i++)
	{
		checkVisited[i] = false;
		path_of_depth_first_search[i] = -1;
	}

	stack <int> stackDFS;
	stackDFS.push(start_verticle);
	checkVisited[start_verticle] = true;
	trace_of_depth_first_search.push_back(start_verticle);

	while (!stackDFS.empty())
	{
		int s = stackDFS.top();
		stackDFS.pop();

		if (!checkVisited[s])
		{

			trace_of_depth_first_search.push_back(s);
			if (s == end_verticle)
				break;
			checkVisited[s] = true;
		}

		for (int i = graph[s].size() - 1; i >= 0; i--)
		{
			if (!checkVisited[graph[s][i].nextVerticle])
			{
				path_of_depth_first_search[graph[s][i].nextVerticle] = s;
				stackDFS.push(graph[s][i].nextVerticle);
			}
		}
	}

	delete checkVisited;
}

void AStarAlgorithm()
{
	bool *checkVisited = new bool[number_verticle];
	path_of_A_star_search = new int[number_verticle];
	for (int i = 0; i < number_verticle; i++)
	{
		checkVisited[i] = false;
		path_of_A_star_search[i] = -1;
	}

	priority_queue<std::pair<int, int>, vector<pair<int, int>>, std::greater<std::pair<int, int>>> priorityQueue;
	priorityQueue.push(std::make_pair(start_verticle, heristicValue[start_verticle]));
	checkVisited[start_verticle] = true;
	trace_of_A_star_search.push_back(start_verticle);
	while (!priorityQueue.empty())
	{
		int verticle = priorityQueue.top().first;
		int hValue = priorityQueue.top().second;
		priorityQueue.pop();

		if (!checkVisited[verticle])
		{
			trace_of_A_star_search.push_back(verticle);
			checkVisited[verticle] = true;
			if (verticle == end_verticle)
			{
				break;
			}
		}

		for (int i = 0; i < graph[verticle].size(); i++)
		{
			int nv = graph[verticle][i].nextVerticle;
			if (!checkVisited[nv])
			{
				path_of_A_star_search[nv] = verticle;
				priorityQueue.push(std::make_pair(nv,
					graph[verticle][i].distance +
					heristicValue[graph[verticle][i].nextVerticle]));
			}
		}

	}
}

void BreadthFirstSearch()
{
	bool *checkVisited = new bool[number_verticle];
	for (int i = 0; i < number_verticle; i++)
	{
		checkVisited[i] = false;
	}

	queue<int> queueBFS;
	queueBFS.push(start_verticle);
	checkVisited[start_verticle] = true;

	while (!queueBFS.empty())
	{
		int q = queueBFS.front();
		queueBFS.pop();

		if (!checkVisited[q])
		{
			cout << q << " ";
			if (q == end_verticle)
				break;
			checkVisited[q] = true;
		}

		for (int i = 0; i < graph[q].size(); i++)
		{
			if (!checkVisited[graph[q][i].nextVerticle])
			{
				queueBFS.push(graph[q][i].nextVerticle);
			}
		}
	}
}

void UniformCostSearch()
{
	bool *checkVisisted = new bool[number_verticle];
	path_of_uniform_cost_search = new int[number_verticle];
	for (int i = 0; i < number_verticle; i++)
	{
		checkVisisted[i] = false;
		path_of_uniform_cost_search[i] = -1;
	}
	//seting priorique for UNIFORM COST SEARCH ALGORITHM

	priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priorityQueue;

	priorityQueue.push(std::make_pair(start_verticle, 0));
	trace_of_uniform_cost_search.push_back(start_verticle);

	checkVisisted[start_verticle] = true;

	while (!priorityQueue.empty())
	{
		int verticle = priorityQueue.top().first; //the verticle
		int weigth = priorityQueue.top().second; //the heristic value of verticle 

		priorityQueue.pop();

		if (!checkVisisted[verticle])
		{
			checkVisisted[verticle] = true;
			trace_of_uniform_cost_search.push_back(verticle);
			if (verticle == end_verticle)
			{
				break;
			}
		}

		for (int i = 0; i < graph[verticle].size(); i++)
		{
			if (!checkVisisted[graph[verticle][i].nextVerticle])
			{
				path_of_uniform_cost_search[graph[verticle][i].nextVerticle] = verticle;
				priorityQueue.push(
					std::make_pair(graph[verticle][i].nextVerticle, 
					weigth + graph[verticle][i].distance));
			}
		}
	}
}

void ExportToFile(int TYPE_SEARCH_ALGORITHM)
{
	int *path = NULL;
	vector<int> trace;
	switch (TYPE_SEARCH_ALGORITHM)
	{
	case DEPTH_FIRST_SEARCH:
	{
							   path = path_of_depth_first_search;
							   trace = trace_of_depth_first_search;
							   break;
	}
	case BREATH_FIRST_SEARCH:
	{
								path = path_of_breadth_first_search;
								trace = trace_of_breadth_first_search;
								break;
	}
	case UNIFORM_COST_SEARCH:
	{
								path = path_of_uniform_cost_search;
								trace = trace_of_uniform_cost_search;
								break;
	}
	case A_STAR_ALGORITHM:
	{
							    path = path_of_A_star_search;
							    trace = trace_of_A_star_search;
							    break;
	}
	default:
		break;
	}

	for (int i = 0; i < trace.size(); i++)
	{
		cout << trace[i] << "  ";
	}

	//export path form start to end 

	vector<int> res;
	int possition = end_verticle;
	while (possition != -1)
	{
		res.push_back(possition);
		possition = path[possition];
		if (possition == start_verticle)
		{
			res.push_back(possition);
			break;
		}
	}

	cout << endl;
	for (int i = res.size() - 1; i >= 0; i--)
	{
		cout << res[i] << "  ";
	}
}
int main()
{
	ReadInputFile();
	AStarAlgorithm();
	ExportToFile(A_STAR_ALGORITHM);
	//DepthFirtSerach();
	//UniformCostSearch();
	//ExportToFile(DEPTH_FIRST_SEARCH);
	//ExportToFile(DEPTH_FIRST_SEARCH);
	//	BreadthFirstSearch();
	system("pause");
	return 0;
}