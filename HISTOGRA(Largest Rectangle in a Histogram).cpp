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
long long max_size = 0;

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
		max_size = 0;
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
				//int new_ht =  0;
				int new_wd = 0; 
				///NEED to POP out from ARRAY till we get no <=ht
				while(HT[top] > ht)
				{
					
					new_wd = new_wd + WIDTH[top];
					long long new_size = HT[top] *  new_wd ;
					if( new_size > max_size )
						max_size = new_size ;
					///POP
					top--;
				}
				////PUSH////
				HT[++top] = ht;
				WIDTH[top] = new_wd + 1;
			}//else
		}//while
		///////AT end POP all and update maxsize;
		int wd = 0;
		while(top!=0)
		{
			wd = wd + WIDTH[top];
			long long size = HT[top] *  wd ;
			if( size > max_size )
				max_size = size ;
			///POP
					top--;
		}
		////RESULT
		cout<<max_size<<endl;
	}//while infinite
	return 0;
}
#endif
