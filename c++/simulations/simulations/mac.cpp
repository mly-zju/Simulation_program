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
	return x*5+y;
}
int num2coox(int num)
{
	return num/5;
}
int num2cooy(int num)
{
	return num%5;
}
bool is_idle(struct sys_map *map,struct sys_sta sta)
{
	bool idle=true;
	bool same=false;
	int x=sta.x;
	int y=sta.y;
	int left=(y-1>=0)?y-1:0;
	int right=(y+1<=4)?y+1:4;
	int top=(x-1>=0)?x-1:0;
	int bottom=(x+1<=4)?x+1:4;
	if(map[coo2num(top,y)].idle!=true){
		idle=false;
		if(x==top)
			same=true;
	}
	else if(map[coo2num(bottom,y)].idle!=true){
		idle=false;
		if(x==bottom)
			same=true;
	}
	else if(map[coo2num(x,left)].idle!=true){
		idle=false;
		if(y==left)
			same=true;
	}
	else if(map[coo2num(x,right)].idle!=true){
		idle=false;
		if(y==right)
			same=true;
	}
	else if(map[coo2num(top,left)].idle!=true){
		idle=false;
		if(x==top&&y==left)
			same=true;
	}
	else if(map[coo2num(top,right)].idle!=true){
		idle=false;
		if(x==top&&y==right)
			same=true;
	}
	else if(map[coo2num(bottom,left)].idle!=true){
		idle=false;
		if(x==bottom&&y==left)
			same=true;
	}
	else if(map[coo2num(bottom,right)].idle!=true){
		idle=false;
		if(x==bottom&&y==right)
			same=true;
	}
	if(same==true)
		idle=true;
	return idle;
}










void main()
{
	struct sys_map map[25];
	struct sys_sta sta1[25];
	struct sys_sta sta2[25];
	int i=0;
	int j=0;
	int tmp=0;
//init the coordinates of the map
	for(i=0;i<25;i++)
	{
		map[i].x=num2coox(i);
		map[i].y=num2cooy(i);
		//cout<<map[i].x<<" "<<map[i].y<<endl;
		map[i].sta_num=0;
		map[i].idle=true;
	}
//init each sta's parameters
	srand((int)time(0));
	for(i=0;i<25;i++)
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
	for(i=0;i<25;i++)
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
	/*for(i=0;i<25;i++)
		cout<<sta2[i].backoff<<" "<<sta2[i].backoff<<endl;
	map[7].idle=false;
	for(i=0;i<25;i++)
		cout<<i<<" "<<is_idle(map,sta1[i])<<endl;*/

}