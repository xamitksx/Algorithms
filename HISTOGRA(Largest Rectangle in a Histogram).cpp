#if 1
/*
Problem : http://www.spoj.com/problems/HISTOGRA/
Get Largest rectangle from the Histogram.
*/
#include <iostream>
#include <cstdio>
using namespace std;
//#define TEST
#define SZ 100005

long long HT[SZ];
int WIDTH[SZ];

int main()
{
#ifdef TEST
	freopen("HISTOGRA_input.txt","r",stdin);
#endif
	int noOfItem;
	while(1)
	{
		cin>>noOfItem;
		if(noOfItem==0)
			break;
		long long max_area = 0;
		HT[0]=0;
		WIDTH[0]=0;
		int top=0;
		while(noOfItem--)
		{
			long long ht = 0;
			cin>>ht;
			if( ht >= HT[top])
			{
				HT[++top] = ht;
				WIDTH[top] = 1;
			}
			else
			{
				int TotalPoppedWidth = 0; 
				///NEED to POP out from ARRAY till we get no <=ht
				while(HT[top] > ht)
				{
			 		//Stack will always have heights in Non Decreasing order.. 
					TotalPoppedWidth = TotalPoppedWidth + WIDTH[top];
					long long area = HT[top] *  TotalPoppedWidth ;
					if( area > max_area )
						max_area = area ;
					///POP
					top--;
				}
				////PUSH////
				HT[++top] = ht;
				WIDTH[top] = TotalPoppedWidth + 1;  ///TotalPoppedWidth  and width of current Bar.
			}//else
		}//while
		///////AT end POP all and update maxsize;
		int wd = 0;
		while(top!=0)
		{
			wd = wd + WIDTH[top];
			long long area = HT[top] *  wd ;
			if( area > max_area )
				max_area = area ;
			///POP
					top--;
		}
		////RESULT
		cout<<max_area<<endl;
	}//while infinite
	return 0;
}
#endif
