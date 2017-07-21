#if 1
/* 
Problem :http://www.spoj.com/problems/INVCNT/
2 attempt AC didnt use long long ....
*/
#include <iostream>
#include <stdlib.h>
using namespace std;
#define SZ 200001
#define LL long long int 
LL N;
LL arr[SZ];
LL _merge(LL start, LL mid, LL end)
{
	LL inv_count = 0;
	LL sizeL = mid - start + 1;
	LL sizeR = end - mid;
	LL *L = (LL*)malloc(sizeof(LL)*(sizeL + 1));
	LL *R = (LL*)malloc(sizeof(LL)*(sizeR + 1));
	//copy left part
	LL j = start;
	LL i = 1;
	while (j <= mid)
		L[i++] = arr[j++];
	//copy right part
	i = 1;
	j = mid+1;
	while (j <= end)
		R[i++] = arr[j++];
	//merge in array
	LL l = 1;
	LL r = 1;
	i = start;
	while (l <= sizeL && r <= sizeR)
	{
		if (L[l] <= R[r])
		{
			arr[i++] = L[l++];
		}
		else
		{
			/// L is sorted array now if R[r] is lesser then L[l] Means R[r] is also lesser then all remaining numbers
			//  in L aray after l index , so all remaining (including no at l index) will contribute in Inversion count... 
			inv_count = inv_count + sizeL - l +1; 
			arr[i++] = R[r++];
			//inv_count++;			
		}
	}
	while (l <= sizeL )
	{
		arr[i++] = L[l++];				
	}
	while (r <= sizeR)
	{
		arr[i++] = R[r++];
	}
	free(L);
	free(R);
	return inv_count;
}
LL _mergeSort(LL start, LL end)
{
	LL invCount = 0;
	if (start < end)
	{
		LL mid = (start + end)/2;
		invCount  = _mergeSort(start, mid);
		invCount +=  _mergeSort(mid + 1, end);
		invCount += _merge(start, mid, end);
	}
	return invCount;
}
int  main()
{
	std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
	freopen("SPOJ_INVCNT.txt", "r", stdin);
#endif
	LL T;
	cin >> T;
	LL result = 0;
	while (T--)
	{
		cin >> N;
		for (LL i = 1; i <= N; i++)
		{
			cin >> arr[i];
		}
		result=_mergeSort(1, N);
		cout << result << endl;;
	}
	return 0;
}
#endif
