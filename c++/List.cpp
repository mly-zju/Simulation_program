#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;

int main()
{
	int i=0;
	int j=0;
	srand((unsigned int)time(0));
	for(i=0;i<1000;i++)
	{
		cout<<rand()%10<<" ";
		if(i%10==0)
		cout<<endl;
	}
	return 0;
}
