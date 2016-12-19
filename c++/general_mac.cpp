#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;
#define CWmin 32
#define CWmax 1024
#define w_slot 9
#define z_slot 320
#define w_frame 500
#define z_frame 250
#define w_band 20
#define z_band 0.25
#define BEmin 8
#define BEmax 32

struct sys_map
{
	int x;
	int y;
	int sta_num;
	int tx_num;
	//bool w_tx;
	//int length;
	//bool start;
};
struct sys_sta
{
	int x;
	int y;
	int backoff;
	int cw;
	//int load;
	bool transmit;
	//int state;
	int length;
	bool trigger;
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
bool is_idle(struct sys_map *map,struct sys_sta sta) //test whether there are other stas transmitting
{
	bool idle=true;
	bool same=false;
	int x=sta.x;
	int y=sta.y;
	int left=(y-1>=0)?y-1:0;
	int right=(y+1<=4)?y+1:4;
	int top=(x-1>=0)?x-1:0;
	int bottom=(x+1<=4)?x+1:4;
	if(map[coo2num(top,y)].tx_num!=0){
		idle=false;
		if(x==top)
			same=true;
	}
	else if(map[coo2num(bottom,y)].tx_num!=0){
		idle=false;
		if(x==bottom)
			same=true;
	}
	else if(map[coo2num(x,left)].tx_num!=0){
		idle=false;
		if(y==left)
			same=true;
	}
	else if(map[coo2num(x,right)].tx_num!=0){
		idle=false;
		if(y==right)
			same=true;
	}
	else if(map[coo2num(top,left)].tx_num!=0){
		idle=false;
		if(x==top&&y==left)
			same=true;
	}
	else if(map[coo2num(top,right)].tx_num!=0){
		idle=false;
		if(x==top&&y==right)
			same=true;
	}
	else if(map[coo2num(bottom,left)].tx_num!=0){
		idle=false;
		if(x==bottom&&y==left)
			same=true;
	}
	else if(map[coo2num(bottom,right)].tx_num!=0){
		idle=false;
		if(x==bottom&&y==right)
			same=true;
	}
	if(same==true)
		idle=true;
	if(map[coo2num(x,y)].tx_num>1)
		idle=false;
	return idle;
}
void add_tx(int *tmp,struct sys_sta sta)
{
	int x=sta.x;
	int y=sta.y;
	tmp[coo2num(x,y)]++;
	/*
	if(x-1>=0)
	{
		tmp[coo2num(x-1,y)]++;
		if(y-1>=0)
			tmp[coo2num(x-1,y-1)]++;
		if(y+1<=4)
			tmp[coo2num(x-1,y+1)]++;
	}
	if(x+1<=4)
	{
		tmp[coo2num(x+1,y)]++;
		if(y-1>=0)
			tmp[coo2num(x+1,y-1)]++;
		if(y+1<=4)
			tmp[coo2num(x+1,y+1)]++;
	}
	if(y-1>=0)
		tmp[coo2num(x,y-1)]++;
	if(y+1>=0)
		tmp[coo2num(x,y+1)]++;
	*/
}
void minus_tx(int *tmp,struct sys_sta sta)
{
	int x=sta.x;
	int y=sta.y;
	tmp[coo2num(x,y)]--;
	/*
	if(x-1>=0)
	{
		tmp[coo2num(x-1,y)]--;
		if(y-1>=0)
			tmp[coo2num(x-1,y-1)]--;
		if(y+1<=4)
			tmp[coo2num(x-1,y+1)]--;
	}
	if(x+1<=4)
	{
		tmp[coo2num(x+1,y)]--;
		if(y-1>=0)
			tmp[coo2num(x+1,y-1)]--;
		if(y+1<=4)
			tmp[coo2num(x+1,y+1)]--;
	}
	if(y-1>=0)
		tmp[coo2num(x,y-1)]--;
	if(y+1>=0)
		tmp[coo2num(x,y+1)]--;
		*/
}


int main()
{
	struct sys_map map[25];
	int num_tmp[25];
	int i=0;
	int j=0;
	int t=0;
	int tmp=0;
	int tx_amount=0;
	int colli_amount=0;
	int success_amount=0;
	double data_amount=0;
	int success_amount_w=0;
	int success_amount_z=0;
	int colli_amount_w=0;
	int colli_amount_z=0;
	int tx_amount_z=0;
	int tx_amount_w=0;
	int client_num=120;
	int run_time=3200000;
	struct sys_sta sta_z[client_num/2];
	struct sys_sta sta_w[client_num/2];
	srand((unsigned int)time(NULL));
for(j=0;j<50;j++)
{
//init the coordinates of the map
	for(i=0;i<25;i++)
	{
		map[i].x=num2coox(i);
		map[i].y=num2cooy(i);
		//cout<<map[i].x<<" "<<map[i].y<<endl;
		map[i].sta_num=0;
		map[i].tx_num=0;
		//map[i].w_tx=false;
		//map[i].length=0;
		//map[i].start=false;
		num_tmp[i]=0;
	}
//init each sta's parameters
	//srand((unsigned int)time(0));
//	int location_z[10]={0,2,6,8,12,14,16,18,20,22};
//	int location_w[10]={1,3,7,9,11,13,15,17,21,23};
	int location_z[client_num/2];
	int location_w[client_num/2];
	for(i=0;i<client_num/2;i++)
	{
		location_z[i]=rand()%25;
		location_w[i]=rand()%25;
	}
	for(i=0;i<client_num/2;i++)
	{
		map[location_z[i]].sta_num++;
		sta_z[i].x=num2coox(location_z[i]);
		sta_z[i].y=num2cooy(location_z[i]);
		//sta_z[i].state=1;
		sta_z[i].transmit=false;
		sta_z[i].length=0;
		sta_z[i].cw=BEmin;
		sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
		sta_z[i].trigger=false;
	}
	//srand((int)time(0));
	for(i=0;i<client_num/2;i++)
	{
		map[location_w[i]].sta_num++;
		sta_w[i].x=num2coox(location_w[i]);
		sta_w[i].y=num2cooy(location_w[i]);
		//sta_w[i].state=1;
		sta_w[i].transmit=false;
		sta_w[i].length=0;
		sta_w[i].cw=CWmin;
		sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
		sta_w[i].trigger=false;
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
	/*
	for(i=0;i<25;i++)
		cout<<sta_w[i].backoff<<" "<<sta_w[i].backoff<<endl;
	map[7].tx_num=1;
	for(i=0;i<25;i++)
		cout<<i<<" "<<is_idle(map,sta_z[i])<<endl;*/
		
	for(t=0;t<run_time;t++)
	{
			//srand((unsigned int)time(NULL));
//each sta_z's contention period
//		if(t<=400000)
//		{
		for(i=0;i<client_num/2;i++)
		{
			if(is_idle(map,sta_z[i])&&sta_z[i].transmit==false)
			{
				sta_z[i].backoff--;
				if(sta_z[i].backoff==0)
				{
					sta_z[i].transmit=true;
					sta_z[i].trigger=true;
					sta_z[i].length=z_frame;
					//num_tmp[coo2num(sta_z[i].x,sta_z[i].y)]++;
					add_tx(num_tmp,sta_z[i]);
					//map[coo2num(sta_w[i].x,sta_w[i].y)].start=true;
					tx_amount++;
				}
			}
			else if(sta_z[i].transmit==true)
			{
				if(sta_z[i].trigger==true)
				{
					sta_z[i].trigger=false;
					sta_z[i].length--;
					if(is_idle(map,sta_z[i]))
					{
						success_amount++;
						success_amount_z++;
						data_amount+=z_frame*z_band;
						sta_z[i].cw=sta_z[i].cw/2;
						if(sta_z[i].cw<BEmin)
							sta_z[i].cw=BEmin;
					}
					else
					{
						colli_amount++;
						colli_amount_z++;
						sta_z[i].cw=sta_z[i].cw*2;
						if(sta_z[i].cw>BEmax)
							sta_z[i].cw=BEmax;
					}
				}
				else
				{
					sta_z[i].length--;
					if(sta_z[i].length==0)
					{
						sta_z[i].transmit=false;
						sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
						//num_tmp[coo2num(sta_z[i].x,sta_z[i].y)]--;
						minus_tx(num_tmp,sta_z[i]);
					}
				}
			}
		}
//		}
//each sta_w's contention period
		for(i=0;i<client_num/2;i++)
		{
			if(is_idle(map,sta_w[i])&&sta_w[i].transmit==false)
			{
				sta_w[i].backoff--;
				if(sta_w[i].backoff==0)
				{
					sta_w[i].transmit=true;
					sta_w[i].trigger=true;
					sta_w[i].length=w_frame;
					//num_tmp[coo2num(sta_w[i].x,sta_w[i].y)]++;
					add_tx(num_tmp,sta_w[i]);
					//map[coo2num(sta_w[i].x,sta_w[i].y)].start=true;
					tx_amount++;
				}
			}
			else if(sta_w[i].transmit==true)
			{
				if(sta_w[i].trigger==true)
				{
					sta_w[i].trigger=false;
					sta_w[i].length--;
					if(is_idle(map,sta_w[i]))
					{
						success_amount++;
						success_amount_w++;
						data_amount+=w_frame*w_band;
						sta_w[i].cw=sta_w[i].cw/2;
						if(sta_w[i].cw<CWmin)
							sta_w[i].cw=CWmin;
					}
					else
					{
						colli_amount++;
						colli_amount_w++;
						sta_w[i].cw=sta_w[i].cw*2;
						if(sta_w[i].cw>CWmax)
							sta_w[i].cw=CWmax;
					}
				}
				else
				{
					sta_w[i].length--;
					if(sta_w[i].length==0)
					{
						sta_w[i].transmit=false;
						sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
						//num_tmp[coo2num(sta_w[i].x,sta_w[i].y)]--;
						minus_tx(num_tmp,sta_w[i]);
					}
				}
			}
		}
//update the system's parameter
//        if(t==400000)
//            for(i=0;i<10;i++)
//				if(sta_z[i].transmit)
//				    minus_tx(num_tmp,sta_z[i]);   
		for(i=0;i<25;i++)
			map[i].tx_num=num_tmp[i];
	}	
	tx_amount_w=success_amount_w+colli_amount_w;
	tx_amount_z=success_amount_z+colli_amount_z;
}
	cout<<"The total transmission amount is "<<tx_amount<<" that is "<<colli_amount+success_amount<<endl;
	cout<<"The total collision amount is "<<colli_amount<<endl;
	cout<<"The total success tx is "<<success_amount<<endl;
	cout<<"The total success of wifi is "<<success_amount_w<<endl;
	cout<<"The total collision of wifi is "<<colli_amount_w<<endl;
	cout<<"The total tx of wifi is "<<tx_amount_w<<endl;
	cout<<"The total success of zigbee is "<<success_amount_z<<endl;
	cout<<"The total collision of zigbee is "<<colli_amount_z<<endl;
	cout<<"The total tx of zigbee is "<<tx_amount_z<<endl;
	cout<<"The total data amount is "<<data_amount<<endl;
	cout<<endl;
	return 0;
}
