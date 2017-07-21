#if 1
/*
Problem : http://www.spoj.com/problems/BENEFACT/
To find Longest path convert all weights as negative and find shortest path with Dijkastra. shortest in -ve will be Longest in +ve 
apply Dijkastra  for all nodes which have Degree 1 leaf node.
---
DataStructure Used Priority Queue
*/
#include <iostream>
#include <string.h>
#include <vector>
using namespace std;
#define VERTEX 50000
#define INT_MAX 0x7FFFFFFF
#define MIN(a,b)  ((a<b)?a:b)
typedef struct{
	int v;
	long c;
}__NODE;
int NEXT = 0;
class PQ
{
private:
	int index[VERTEX + 1];
	__NODE heap[VERTEX + 1];
	int size;

	int LEFT(int k) { return 2 * k; }
	int RIGHT(int k) { return 2 * k + 1; }
	int PARENT(int k){ return k / 2; }
	void sink(int k);
	void swim(int k);
	void SWAPI(int a, int b);
	bool IsLess(int a, int b){ return (heap[a].c < heap[b].c) ? true : false; }
	bool IsMore(int a, int b){ return (heap[a].c > heap[b].c) ? true : false; }

public:
	PQ() :size(0), maxSize(0){};
	int maxSize;
	void decreaseKey(int vertex, int val);
	void InsertKey(int val, int vertex);
	__NODE delTOP(void);
	long getkey(int v);
	bool IsEmpty(void) { return (size == 0) ? true : false; };
	void reset(void);

};

class PQ pq;
typedef vector < pair<int, long> > _LIST;
long dijkastra(int source ,int N, vector < _LIST > &aList)
{
	long dist = 0;;
	pq.maxSize = N;
	bool done[VERTEX + 1] = { false };
	
	for (int i = 1; i <= N; i++)
	{
		pq.InsertKey(i, INT_MAX);
		done[i] = false;
	}
	pq.decreaseKey(source, 0);  // source = 0
	while (pq.IsEmpty() == false)
	{
		__NODE U = pq.delTOP();  //EXTRACT- MIN from Priority QUEUE		
		if (dist > U.c)
		{
			dist = U.c;
			NEXT = U.v;
		}
		done[U.v] = true; //set min_v to done 
		////RELAXATION
		for (int i = 0; i < (int)aList[U.v].size(); i++)
		{
			int u = U.v;
			int v = aList[U.v][i].first;
			long Euv = aList[U.v][i].second;
			if (done[v] == false && U.c + Euv < pq.getkey(v))
			{
				//update dist 
				pq.decreaseKey(v, U.c + Euv);
			}
		}
	}
	pq.reset();		//RESET  PQ 
	return dist;
}
int main()
{
	int T;
//	freopen("BENEFACT_input.txt","r",stdin);
	cin >> T;
	while (T--)
	{
		int N;
		cin >> N;
		int E = N - 1;
		vector <_LIST> adjList(N + 1);
		for (int i = 1; i <= E; i++)
		{
			int u, v, c;
			cin >> u >> v >> c;
			c = c *(-1);
			adjList[u].push_back(make_pair(v, c));
			adjList[v].push_back(make_pair(u, c)); //undirected Graph
		}
		// apply Dijkastra  for all nodes which have Degree 1 
		long res = INT_MAX;
		long temp = 0;
		for (int i = 1; i <= N; i++)
		{
			if (adjList[i].size() == 1)
			{
				temp = dijkastra(i, N, adjList);
				res = MIN(res, temp);
				break;
			}
		}
		temp = dijkastra(NEXT, N, adjList);
		res = MIN(res, temp);
		cout << res*(-1) << endl;
	}
	return 0;
}
/* Get Key(distance ) value from Heap of Vertex V*/
long PQ::getkey(int v)
{
	return heap[index[v]].c;
}
void PQ::reset(void)
{
	//for (int i = 1; i <= maxSize; i++)
	{
		//	heap[i].v = heap[i].c = index[i] = -1;
	}
	size = 0;
	maxSize = 0;
}
/*Swap Two Elements of given indexes Also updateds the index Array*/
void PQ::SWAPI(int a, int b){
	__NODE t = heap[a]; heap[a] = heap[b]; heap[b] = t;
	index[heap[a].v] = a;
	index[heap[b].v] = b;
}
/*Inreases size of Heap and Insert element at Last Index and Maintains the MIN condition of HEAP by SWIM*/
void PQ::InsertKey(int vertex, int val)
{
	heap[++size].c = val; //Increase Last Index and Insert Element there 
	heap[size].v = vertex;
	index[vertex] = size;
	swim(size); // Heapify from Last element Bottom UP
}
/*Update(decrease) value of Key(Distance) and MAintaince MIN HEAP by Heapifying from updated index.*/
void PQ::decreaseKey(int vertex, int val)
{
	int v = index[vertex]; //get Heap Index "v" for given vertex 
	heap[v].c = val;  //update value
	swim(v);  // Heapify 
}
/* BOTTOM up HEAPIFY  pushes Larger no to TOP  */
void PQ::swim(int k)
{
	while (k > 1 && IsMore(PARENT(k), k))
	{
		SWAPI(k, PARENT(k));
		k = k / 2; 	//k = PARENT(k)
	}
}
/*TOP DOWN  HEAPIFY pushes Smaller non to BOTTOM */
void PQ::sink(int k)
{
	while (k <= size / 2)
	{
		int j = LEFT(k);
		//if (j + 1 <= size && IsLess(LEFT(k),RIGHT(k)))
		if (j + 1 <= size && IsMore(j, j + 1))
			j++;
		if (IsMore(k, j))
		{
			SWAPI(k, j);
			k = j;
		}
		else
			break;
	}

}
/* Deletes TOP of HEAP (MIN Value) Replaces last value with ROOT and HEAPIFY....*/
__NODE PQ::delTOP(void)
{
	__NODE ret = heap[1];
	SWAPI(1, size);
	index[heap[size].v] = -1;
	//heap[size].c = -1; // delete last entry	
	//heap[size].v = -1;
	size--;
	sink(1);
	return ret;
}
#endif
