
/*
Problem : http://www.spoj.com/problems/KGSS/
Algorithm : Segment Tree.
Resource : https://www.youtube.com/watch?v=ZBHKZF5w4YU
*/
#if 1
#include <iostream>
#include <stdlib.h>
using namespace std;
#define SZ 100002
#define LL  long long  
LL N;
LL arr[SZ];
LL seg_index[SZ];
typedef struct {
	LL maxVal1;
	LL maxVal2;
}_SEGTREE_NODE;

#define LEFT(a) ((a*2)+1)
#define RIGHT(a) ((a*2)+2)
#define PARENT(a) ((a-1)/2)
_SEGTREE_NODE segTree[3 * SZ];

_SEGTREE_NODE getMAX(_SEGTREE_NODE a, _SEGTREE_NODE b)
{
	_SEGTREE_NODE temp;
	if (a.maxVal1 > b.maxVal1)
	{
		temp.maxVal1 = a.maxVal1; // one value from a is set 
		if (a.maxVal2 > b.maxVal1)
		{
			temp.maxVal2 = a.maxVal2;
		}
		else
		{
			temp.maxVal2 = b.maxVal1;
		}
	}
	else
	{
		temp.maxVal1 = b.maxVal1; // one value from b is set 
		if (b.maxVal2 > a.maxVal1)
		{
			temp.maxVal2 = b.maxVal2;
		}
		else
		{
			temp.maxVal2 = a.maxVal1;
		}
	}

	return temp;
}

void create_seg_tree(LL start, LL end, LL segIndex)
{
	if (start == end)
	{
		segTree[segIndex].maxVal1 = arr[start];
		segTree[segIndex].maxVal2 = 0;
		seg_index[start] = segIndex;
		return;
	}

	LL mid = (start + end) / 2;
	create_seg_tree(start, mid, LEFT(segIndex));
	create_seg_tree(mid + 1, end, RIGHT(segIndex));
	segTree[segIndex] = getMAX(segTree[LEFT(segIndex)], segTree[RIGHT(segIndex)]);
}

_SEGTREE_NODE query_Seg_tree(LL range_start, LL range_end, LL in_start, LL in_end, LL segIndex)
{
	if (range_end < in_start || range_start  > in_end) // out of range
	{
		_SEGTREE_NODE temp;
		temp.maxVal1 = temp.maxVal2 = 0;
		return temp;
	}
	else if (range_start <= in_start  &&   range_end >= in_end)   //complete OVERLAP  our input is completly overlapped by input  also covers EXACT match case
	{
		return segTree[segIndex];
	}
	else
	{
		LL mid = (in_start + in_end) / 2;
		_SEGTREE_NODE a = query_Seg_tree(range_start, range_end, in_start, mid, LEFT(segIndex));
		_SEGTREE_NODE b = query_Seg_tree(range_start, range_end, mid + 1, in_end, RIGHT(segIndex));
		_SEGTREE_NODE temp = getMAX(a, b);
		return temp;
	}
}

void update_recur(LL segIndex)
{
	segTree[segIndex] = getMAX(segTree[LEFT(segIndex)], segTree[RIGHT(segIndex)]);
	if (segIndex == 0)
		return;
	update_recur(PARENT(segIndex));
}
void updateTree(LL segIndex, LL val)
{
	segTree[segIndex].maxVal1 = val;
	segTree[segIndex].maxVal2 = 0;
	update_recur(PARENT(segIndex));
}

int  main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("KGSS_input.txt", "r", stdin);
#endif

	//while (T--)
	{
		cin >> N;
		for (LL i = 0; i < N; i++)
		{
			cin >> arr[i];
		}
		// create Segment Tree
		create_seg_tree(0, N - 1, 0);
		LL quer;
		cin >> quer;
		for (LL i = 1; i <= quer; i++)
		{
			char ch;
			LL a, b;
			cin >> ch >> a >> b;
			if (ch == 'U') //update
			{
				arr[a - 1] = b;
				//create_seg_tree(0, N - 1, 0);  this gives TLE
				LL segTreeIndex = seg_index[a - 1];
				updateTree(segTreeIndex, b);
			}
			else if (ch == 'Q')
			{
				_SEGTREE_NODE temp = query_Seg_tree(a - 1, b - 1, 0, N - 1, 0);
				cout << temp.maxVal1 + temp.maxVal2 << endl;
			}
		}

	}
	return 0;
}
#endif
