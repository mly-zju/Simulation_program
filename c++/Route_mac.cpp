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
};
struct sys_sta
{
	int x;
	int y;
	int backoff;
	int cw;
	bool transmit;
	int length;
	bool trigger;
	int data_pk;
	int tc_pk;
	int tc_src[5];//record the source of received tc
	int tc_queue[5];
	int *tc_log; 
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
	if(map[coo2num(top,y)].tx_num!=0&&x!=top){
		idle=false;
	}
	else if(map[coo2num(bottom,y)].tx_num!=0&&x!=bottom){
		idle=false;
	}
	else if(map[coo2num(x,left)].tx_num!=0&&y!=left){
		idle=false;
	}
	if(map[coo2num(x,right)].tx_num!=0&&y!=right){
		idle=false;
	}
	else if(map[coo2num(top,left)].tx_num!=0&&x!=top&&y!=left){
		idle=false;
	}
	else if(map[coo2num(top,right)].tx_num!=0&&x!=top&&y!=right){
		idle=false;
	}
	else if(map[coo2num(bottom,left)].tx_num!=0&&x!=bottom&&y!=left){
		idle=false;
	}
	else if(map[coo2num(bottom,right)].tx_num!=0&&x!=bottom&&y!=right){
		idle=false;
	}
	else if(map[coo2num(x,y)].tx_num>1)
		idle=false;
	return idle;
}
void add_tx(int *tmp,struct sys_sta sta)
{
	int x=sta.x;
	int y=sta.y;
	tmp[coo2num(x,y)]++;
}
void minus_tx(int *tmp,struct sys_sta sta)
{
	int x=sta.x;
	int y=sta.y;
	tmp[coo2num(x,y)]--;
}

bool contain(int t,int *pk, int num)
{
	int i;
	for(i=0;i<num;i++£©
		if(t==pk[i])
			return true; 
	return false;
}

int main()
{
	struct sys_map map[25];
	struct sys_map sta[50];
	int num_tmp[25];
	int i=0;
	int j=0;
	int t=0;
	int tmp=0;
	int data_tx_amount=0;
	int tc_tx_amount=0;
	int data_collision_amount=0;
	int tc_collision_amount=0;
	double data_amount=0;
//	struct packet_map tcpk[50][2];
//	struct packet_map dapk[50][100];
	int tcpk[50][2];
	int dapk[50][100];

//init the coordinates of the map
	for(i=0;i<25;i++)
	{
		map[i].x=num2coox(i);
		map[i].y=num2cooy(i);
		map[i].sta_num=0;
		map[i].tx_num=0;
		num_tmp[i]=0;
	}
//init each sta's parameters
	srand((unsigned int)time(NULL));
	int location[50];
	for(i=0;i<50;i++)
	{
		location[i]=rand()%25;
	}
	
	for(i=0;i<50;i++)
	{
		map[location[i]].sta_num++;
		sta[i].x=num2coox(location[i]);
		sta[i].y=num2cooy(location[i]);
		sta[i].transmit=false;
		sta[i].length=0;
		sta[i].cw=CWmin;
		sta[i].backoff=(rand()%sta[i].cw+1)*w_slot;
		sta[i].trigger=false;
		sta[i].data_pk=0;
		sta[i].tc_pk=0;
		for(j=0;j<5;j++){
			sta[i].tc_src[j]=-1;
			sta[i].tc_queue[j]=-1;
		}
		sta[i].tc_log=(int *)malloc(sizeof(int)*50);
		for(j=0;j<50;j++)
			sta[i].tc_log[j]=-1;
	}		
//arrange the tc packet schedule
	for(i=0;i<50;i++)
	{
		tcpk[i][0].time=((rand()%5)*1000000+(rand()%10)*100000+rand()%100000)/w_slot;
		tcpk[i][1].time=((rand()%5)*1000000+(rand()%10)*100000+rand()%100000)/w_slot+5000000/w_slot;
	}
	for(i=0;i<50;i++)
	{
		for(j=0;j<100;j++)
			dapk[i][j]=((rand()%10)*1000000+(rand()%10)*100000+rand()%100000)/w_slot;
	}
		
	for(t=0;t<10000000;t++)
	{
		if(t%w_slot==0)
		{
			for(i=0;i<50;i++)
			{
				if(contain(t/w_slot,tcpk[i],2))
				{
					sta[i].tc_pk++;
					sta[i].tc_src[sta[i].tc_pk-1]=i;
					if(t<5000000)
						sta[i].tc_queue[sta[i].tc_pk-1]=0;
					else
						sta[i].tc_queue[sta[i].tc_pk-1]=1;
				}
				if(contain(t/w_slot,dapk[i],100))
					sta[i].data_pk++;
			}
		}
		for(i=0;i<50;i++)
		{
			if(sta[i].tc_pk>0)
			{
				if(is_idle(map,sta[i])&&sta[i].transmit==false)
				{
					sta[i].backoff--;
					if(sta[i].backoff==0)
					{
						sta[i].transmit=true;
						sta[i].trigger=true;
						sta[i].length=w_frame;
						//num_tmp[coo2num(sta[i].x,sta[i].y)]++;
						add_tx(num_tmp,sta[i]);
						//map[coo2num(sta[i].x,sta[i].y)].start=true;
						tx_amount++;
					}
				}
				else if(sta[i].transmit==true)
				{
					if(sta[i].trigger==true)
					{
						sta[i].trigger=false;
						sta[i].length--;
						if(is_idle(map,sta[i]))
						{
							success_amount++;
							success_amount_w++;
							data_amount+=w_frame*w_band;
							sta[i].cw=sta[i].cw/2;
							if(sta[i].cw<CWmin)
								sta[i].cw=CWmin;
						}
						else
						{
							colli_amount++;
							colli_amount_w++;
							sta[i].cw=sta[i].cw*2;
							if(sta[i].cw>CWmax)
								sta[i].cw=CWmax;
						}
					}
					else
					{
						sta[i].length--;
						if(sta[i].length==0)
						{
							sta[i].transmit=false;
							sta[i].backoff=(rand()%sta[i].cw+1)*w_slot;
							//num_tmp[coo2num(sta[i].x,sta[i].y)]--;
							minus_tx(num_tmp,sta[i]);
						}
					}
				}
			}
		}
		for(i=0;i<25;i++)
			map[i].tx_num=num_tmp[i];
	}	
		
		
	
	return 0;
}
