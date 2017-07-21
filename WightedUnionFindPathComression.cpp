#if 1
/*
Qustion : https://www.hackerrank.com/challenges/journey-to-the-moon
Weighted unionFind algorithm
--I tried flattening of union by adding while loop to reach to ultimate root while joining  NO effect
after that I added logic of updating parent to ultimate root recursive When we are counting Groups .. this iincreased TC from 7 --> 10
-- I applied below mentioned way to count and 1 TC which was Timouting is now passing so total TC pass is 10-->11
-- at last remaining 5 TC got passed by putting check if (Rx != Ry)  with out this I was INcreasing SIZEcount even for
same Sets element......
Learning :
1) There are elements in array where we need to multiply
	a,b,c
	a*b + a*c + b*c
	I wrote O(n sqr) code for this :
	for (vector<int>::iterator it = grpSizes.begin(); it != grpSizes.end()-1; ++it)
	{
		for (vector<int>::iterator it2 = it+1; it2 != grpSizes.end(); ++it2)
		{
			ans = ans + *it * *it2;
		}
	}
-----------
this can be done in O(N)
How
for : a,b,c   = a*b + a*c + b*c  = a*b + (a+b)*c;
for : a,b,c,d = a*b + a*c + a*d + b*c + b*d + c*d
=> a*b + (a+b)*c + (a+b+c)*d

2) Dont do UNion for elemenst of same set  . Its problematic ...
3) for path compression Recursive scheme is better as it Flattens the Tree completely
*/
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define MSIZE 100001

int parent[MSIZE] = { 0 };
int grp_sz[MSIZE] = { 0 };

int getRoot(int x)
{
	if (parent[x] != x)
	{
		parent[x] = getRoot(parent[x]);// updates all parents to root
	}
	return parent[x];
}

void wqUnion(int rootX, int rootY)
{
	if (grp_sz[rootX] > grp_sz[rootY])   ///WEIGHTED UNION.....
	{
		parent[rootY] = rootX;
		grp_sz[rootX] = grp_sz[rootX] + grp_sz[rootY];
	}
	else
	{
		parent[rootX] = rootY;
		grp_sz[rootY] = grp_sz[rootX] + grp_sz[rootY];
	}
}

int main() {
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
	//freopen("Output.txt", "w", stdout);
#endif
	int N, P;
	cin >> N >> P;
	for (int i = 0; i<N; i++)
	{
		parent[i] = i;
		grp_sz[i] = 1;
	}
	for (int i = 0; i<P; i++)
	{
		int a, b;
		cin >> a >> b;
		int Rx = getRoot(a);
		int Ry = getRoot(b);
		if (Rx != Ry)   // introducing this Condition made remaining 5 TCs pass
			wqUnion(Rx, Ry);
	}
	vector <int> grpSizes; /// it will have all the group/set sizes 
	for (int p = 0; p<N; p++)
	{
		if (p == parent[p])  // read size of Ultimate ROOT element .....
		{
			grpSizes.push_back(grp_sz[p]);
			grp_sz[p] = 0;
		}
	}
	long long ans = 0;
	long long prevSum = grpSizes[0];
	for (vector<int>::iterator it = grpSizes.begin() + 1; it != grpSizes.end(); ++it)
	{
		ans = ans + prevSum * *it;
		prevSum = prevSum + *it;
	}
	cout << ans;
	return 0;
}
#endif
