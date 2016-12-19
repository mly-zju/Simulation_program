#include "stdafx.h"
#include "iostream"
#include "time.h"
#include "stdlib.h"
using namespace std;
#define CWmin 128
#define CWmax 1024

struct sys_map
{
	int x;
	int y;
	int sta_num;
	bool idle;
};
struct sys_sta
{
	int x;
	int y;
	int backoff;
	int cw;
	int load;
	bool transmit;
	int state;
	int length;
};

int coo2num(int x,int y)
{
	int num=0;
	if(x==0)
		num=y;
	else if(x==1)
		num=3+y;
	else if(x==2)
		num=7+y;
	else if(x==3)
		num=12+y;
	else if(x==4)
		num=16+y;
	return num;
}
int num2coox(int num)
{
	int x=0;
	if(num<3)
		x=0;
	else if(num<7)
		x=1;
	else if(num<12)
		x=2;
	else if(num<16)
		x=3;
	else
		x=4;
	return x;
}
int num2cooy(int num)
{
	int x=num2coox(num);
	int y=0;
	if(x==0)
		y=num;
	else if(x==1)
		y=num-3;
	else if(x==2)
		y=num-7;
	else if(x==3)
		y=num-12;
	else if(x==4)
		y=num-16;
	return y;
}




		


void main()
{
	struct sys_map map[19];
	struct sys_sta sta1[19];
	struct sys_sta sta2[19];
	int i=0;
	int j=0;
	int tmp=0;
//init the coordinates of the map
	for(i=0;i<19;i++)
	{
		map[i].x=num2coox(i);
		map[i].y=num2cooy(i);
		//cout<<map[i].x<<" "<<map[i].y<<endl;
		map[i].sta_num=0;
		map[i].idle=true;
	}
//init each sta's parameters
	srand((int)time(0));
	for(i=0;i<19;i++)
	{
		map[i].sta_num++;
		sta1[i].x=num2coox(i);
		sta1[i].y=num2cooy(i);
		sta1[i].state=1;
		sta1[i].transmit=false;
		sta1[i].length=0;
		sta1[i].cw=CWmin;
		sta1[i].backoff=rand()%sta1[i].cw;
	}
	srand((int)time(0));
	for(i=0;i<19;i++)
	{
		map[i].sta_num++;
		sta2[i].x=num2coox(i);
		sta2[i].y=num2cooy(i);
		sta2[i].state=1;
		sta2[i].transmit=false;
		sta2[i].length=0;
		sta2[i].cw=CWmin;
		sta2[i].backoff=rand()%sta2[i].cw;
	}
	/*
	for(i=19;i<30;i++)
	{
		tmp=rand()%19;//generate random numbers between 0 and 18
		map[tmp].sta_num++;
		sta[i].x=num2coox(tmp);
		sta[i].y=num2cooy(tmp);
		//cout<<tmp<<" "<<sta[i].x<<" "<<sta[i].y<<endl;
	}
//show the topology of the network
	for(i=0;i<5;i++)
	{
		if(i==0||i==4)
		{
			cout<<"  ";
			for(j=0;j<3;j++)
				cout<<map[coo2num(i,j)].sta_num<<" ";
			cout<<endl;
		}
		else if(i==1||i==3)
		{
			cout<<" ";
			for(j=0;j<4;j++)
				cout<<map[coo2num(i,j)].sta_num<<" ";
			cout<<endl;
		}
		else
		{
			for(j=0;j<5;j++)
				cout<<map[coo2num(i,j)].sta_num<<" ";
			cout<<endl;
		}
	}*/
}