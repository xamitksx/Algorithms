#if 1
/*
Problem : http://www.spoj.com/problems/HORRIBLE/
Resource : https://leetcode.com/articles/recursive-approach-segment-trees-range-sum-queries-lazy-propagation/#3-update-the-value-of-an-element
*/

#include <iostream>
#include <malloc.h>
using namespace std;

#define LEFT(x) (2*x + 1)
#define RIGHT(x) (2*x + 2)

#define LL long long
LL N, Q;
LL * tree = NULL;
LL * lazy = NULL;

void updateLazySegTree(LL treeIndex, LL seglo, LL seghi, LL qlo, LL qhi, LL val)
{
	/// if this node is lazy then we need to update it 
	/* This logic of updation should be there at begining I kept it at LOC A
	Problem in that was for NON ranged nodes it was skipping and not updating the value properly...*/
	if (lazy[treeIndex] != 0)
	{
		tree[treeIndex] = tree[treeIndex] + ((seghi - seglo + 1) * lazy[treeIndex]); //update the segment with new  value
		if (seglo != seghi)
		{
			// update /propaget  laziness of its childs
			lazy[LEFT(treeIndex)] += lazy[treeIndex];
			lazy[RIGHT(treeIndex)] += lazy[treeIndex];
		}
		lazy[treeIndex] = 0; // remove its lazyness
	}

	if (qhi < seglo || qlo > seghi) // completely out of range
	{
		return;
	}

	/* LOC A it was here.... */

	if (qhi >= seghi  &&  seglo >= qlo)  // complete overlap qhi > shi > slo > qlo
	{
		tree[treeIndex] += (seghi - seglo + 1) * val;  //update the segment with new  value
													   // if its not leaf then mark its childs as lazy....
		if (seglo != seghi)
		{
			lazy[LEFT(treeIndex)] += val;
			lazy[RIGHT(treeIndex)] += val;
		}
	}
	else   // partial overlap
	{
		LL mid = seglo + (seghi - seglo) / 2;
		updateLazySegTree(LEFT(treeIndex), seglo, mid, qlo, qhi, val);
		updateLazySegTree(RIGHT(treeIndex), mid + 1, seghi, qlo, qhi, val);
		// merge updates
		tree[treeIndex] = tree[LEFT(treeIndex)] + tree[RIGHT(treeIndex)];		
	}
	return;
}

LL queryLazySegTree(LL treeIndex, LL seglo, LL seghi, LL qlo, LL qhi)
{
	if (qhi < seglo || qlo > seghi) // completely out of range
	{
		return  0;
	}

	if (lazy[treeIndex] != 0)
	{
		tree[treeIndex] = tree[treeIndex] + ((seghi - seglo + 1) * lazy[treeIndex]);
		if (seglo != seghi)
		{
			// update lazy of its childs
			lazy[LEFT(treeIndex)] += lazy[treeIndex];
			lazy[RIGHT(treeIndex)] += lazy[treeIndex];
		}
		lazy[treeIndex] = 0; // remove its lazyness
	}

	if (qhi >= seghi  &&  seglo >= qlo)  // complete overlap qhi-- shi -- slo -- qlo
	{
		return tree[treeIndex];
	}
	else   // partial overlap
	{
		LL mid = seglo + (seghi - seglo) / 2;
		LL left = queryLazySegTree(LEFT(treeIndex), seglo, mid, qlo, qhi);
		LL right = queryLazySegTree(RIGHT(treeIndex), mid + 1, seghi, qlo, qhi);
		return left + right;
	}
}
///////

int main()
{
#ifdef _WIN32
	freopen("input.txt", "r", stdin);
#endif
	int T;
	cin >> T;
	while (T--)
	{
		cin >> N >> Q;
		tree = (LL *)calloc(4 * N, sizeof(LL));
		lazy = (LL *)calloc(4 * N, sizeof(LL));
		while (Q--)
		{
			LL cmd, p, q;
			cin >> cmd >> p >> q;
			if (cmd == 0)
			{
				int val;
				cin >> val;
				updateLazySegTree(0, 0, N - 1, p - 1, q - 1, val);
			}
			else
			{
				LL result = queryLazySegTree(0, 0, N - 1, p - 1, q - 1);
				cout << result << endl;
			}
		}
		free(tree);
		free(lazy);
	}
	return 0;
}
#endif 
