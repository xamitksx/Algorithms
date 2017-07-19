/*
video :  https://youtu.be/aQiWF4E8flQ
 */
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int N;
void swap(vector<int> &arr ,int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
void printArr(vector<int> &arr, int start, int end)
{
	for (int i = start; i <= end; i++)
		cout << arr[i]<<" ";
	cout << endl;
}
int partition(vector<int> &arr, int start, int end)
{
	int pivot = arr[end];
	int Wall = start;
	for (int curr = start; curr <= end - 1; curr++)
	{
		if (arr[curr] < pivot )
		{
			if (curr != Wall)
				swap(arr, curr, Wall);
			Wall++;
		}
	}
	// place pivot at wall 
	swap(arr, Wall, end);
	return Wall;
}

void q_sort(vector<int> &arr, int start, int end)
{
	if (start < end)
	{
		int p = partition(arr, start, end);
		printArr(arr, 0, N-1);
		q_sort(arr,start,p-1);
		q_sort(arr,p+1, end);
	}
}
int main()
{
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
#endif
	cin >> N;
	vector<int> arr(N);
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	q_sort(arr, 0, N - 1);
	return 0;
}
