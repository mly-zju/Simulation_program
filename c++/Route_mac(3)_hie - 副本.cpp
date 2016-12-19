#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
#include "fstream"
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
};
struct sys_map
{
	int x;
	int y;
	int sta_num;
	int tx_num;
};

int coo2num(int x,int y,int side)
{
	return x*5*side+y;
}
int num2coox(int num,int side)
{
	return num/(5*side);
}
int num2cooy(int num,int side)
{
	return num%(5*side);
}
bool is_idle(struct sys_map *map,struct sys_sta sta,int side) //test whether there are other stas transmitting
{
	bool idle=true;
	bool same=false;
	int x=sta.x;
	int y=sta.y;
	int left=(y-1>=0)?y-1:0;
	int right=(y+1<=5*side)?y+1:(5*side-1);
	int top=(x-1>=0)?x-1:0;
	int bottom=(x+1<=5*side)?x+1:(5*side-1);
	if(map[coo2num(top,y,side)].tx_num!=0&&x!=top){
		idle=false;
	}
	else if(map[coo2num(bottom,y,side)].tx_num!=0&&x!=bottom){
		idle=false;
	}
	else if(map[coo2num(x,left,side)].tx_num!=0&&y!=left){
		idle=false;
	}
	if(map[coo2num(x,right,side)].tx_num!=0&&y!=right){
		idle=false;
	}
	else if(map[coo2num(top,left,side)].tx_num!=0&&x!=top&&y!=left){
		idle=false;
	}
	else if(map[coo2num(top,right,side)].tx_num!=0&&x!=top&&y!=right){
		idle=false;
	}
	else if(map[coo2num(bottom,left,side)].tx_num!=0&&x!=bottom&&y!=left){
		idle=false;
	}
	else if(map[coo2num(bottom,right,side)].tx_num!=0&&x!=bottom&&y!=right){
		idle=false;
	}
	else if(map[coo2num(x,y,side)].tx_num>1)
		idle=false;
	return idle;
}

void add_tx(int *tmp,struct sys_sta sta,int side)
{
	int x=sta.x;
	int y=sta.y;
	tmp[coo2num(x,y,side)]++;
}
void minus_tx(int *tmp,struct sys_sta sta,int side)
{
	int x=sta.x;
	int y=sta.y;
	tmp[coo2num(x,y,side)]--;
}

bool contain(int t,int *pk, int num)
{
	int i;
	for(i=0;i<num;i++)
	{
		if(t==pk[i])
		{
			return true; 
		}
	}
	return false;
}

double *csma(int client_num,int load,int side,int fake)
{
	int block=side*side;
	struct sys_map map[25*block];
	struct sys_sta sta[client_num];
	int num_tmp[25*block];
	int i=0;
	int j=0;
	int t=0;
	int tmp=0;
	int data_tx_amount=0;
	int tc_tx_amount=0;
	int data_collision_amount=0;
	int tc_collision_amount=0;
	int data_success_amount=0;
	int tc_success_amount=0;
	double tc_delay=0;
	double data_delay=0;
	double data_amount=0;
	int run_time=10000000;
	int load_num=run_time*load/1000000;
	double x=client_num/(double)(1000000*5*block);
	x=x*run_time;
	int tc_num=x;
	cout<<"tc_num "<<tc_num<<endl;
	load_num=load_num+tc_num;
	int dapk[client_num][load_num];
	double t_r=(double)tc_num/(double)load_num;
	double d_r=1-t_r;
	cout<<"d_r is "<<d_r<<" t_r is "<<t_r<<endl;

	
	for(i=0;i<25*block;i++)
	{
		map[i].x=num2coox(i,side);
		map[i].y=num2cooy(i,side);
		map[i].sta_num=0;
		map[i].tx_num=0;
		num_tmp[i]=0;
	}
//init each sta's parameters
	srand((unsigned int)time(NULL));
	int location[client_num];
	for(i=0;i<client_num;i++)
	{
		location[i]=rand()%100;
	}
	
	for(i=0;i<client_num;i++)
	{
		map[location[i]].sta_num++;
		sta[i].x=num2coox(location[i],side);
		sta[i].y=num2cooy(location[i],side);
		sta[i].transmit=false;
		sta[i].length=0;
		sta[i].cw=CWmin;
		sta[i].backoff=(rand()%sta[i].cw+1)*w_slot;
		sta[i].trigger=false;
		sta[i].data_pk=0;
		sta[i].tc_pk=0;
	}		
//arrange the tc packet schedule
//	for(i=0;i<client_num;i++)
//	{
//		for(j=0;j<tc_num;j++)
//		{
//			tcpk[i][j]=((rand()%10)*(run_time/10)+(rand()%10)*(run_time/100)+(rand()%10)*(run_time/1000)+rand()%(run_time/1000))/w_slot;
//		}
//	}
	for(i=0;i<client_num;i++)
	{
		for(j=0;j<load_num;j++)
		{
			dapk[i][j]=((rand()%10)*(run_time/10)+(rand()%10)*(run_time/100)+(rand()%10)*(run_time/1000)+rand()%(run_time/1000))/w_slot;
		}
	}
		
	for(t=0;t<run_time;t++)
	{
		if(t%w_slot==0)
		{
			for(i=0;i<client_num;i++)
			{
//				if(contain(t/w_slot,tcpk[i],tc_num))
//					sta[i].tc_pk++;
				if(contain(t/w_slot,dapk[i],load_num))
					sta[i].data_pk++;
			}
		}
		for(i=0;i<client_num;i++)
		{
			if(sta[i].data_pk>0)
			{
				if(is_idle(map,sta[i],side)&&sta[i].transmit==false)
				{
					sta[i].backoff--;
					data_delay++;
//					if(sta[i].tc_pk)
//				    	tc_delay++;
					if(sta[i].backoff==0)
					{
						sta[i].transmit=true;
						sta[i].trigger=true;
						sta[i].length=w_frame;
						add_tx(num_tmp,sta[i],side);
						data_tx_amount++;
					}
				}
				else if(sta[i].transmit==true)
				{
					if(sta[i].trigger==true)
					{
						sta[i].trigger=false;
						sta[i].length--;
						if(is_idle(map,sta[i],side))
						{
							data_success_amount++;
							//data_delay+=w_frame*sta[i].data_pk;
//							if(sta[i].tc_pk)
//							    tc_delay+=w_frame;
							data_amount+=w_frame*w_band;
							sta[i].cw=sta[i].cw/2;
							if(sta[i].cw<CWmin)
								sta[i].cw=CWmin;
						}
						else
						{
							data_collision_amount++;
							data_delay+=w_frame;
//							if(sta[i].tc_pk)
//							    tc_delay+=w_frame;
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
							minus_tx(num_tmp,sta[i],side);
							if(is_idle(map,sta[i],side))
								sta[i].data_pk--;
						}
					}
				}
				else{
					data_delay++;
//					if(sta[i].tc_pk)
//					    tc_delay++;
				}
			}
		}
		for(i=0;i<25*block;i++)
			map[i].tx_num=num_tmp[i];
	}	
	double result[3];
	double ratio=(double)data_collision_amount/(double)data_tx_amount;
	result[0]=ratio;
	double delay=(double)data_delay/(double)(data_success_amount*1000);
	result[1]=delay;
	cout<<"data_amount is "<<data_amount<<endl;
	double throughput=(double)data_amount/(double)(run_time/1000000);
	result[2]=throughput*d_r;

	return result;
}

int main()
{
	int load=10;
	double *tmp;
	double result[3];
	int i=0;
	int j=0;
	int side=2;
	int client_num=60*side*side;
	ofstream outfile;
	outfile.open("data6_new2.txt",ios::app);
	while(load<=70)
	{
		for(i=0;i<3;i++)
			result[i]=0;
		for(i=0;i<3;i++)
		{
			tmp=csma(client_num,load,side);
			for(j=0;j<3;j++)
				result[j]+=*(tmp+j);
		}
		outfile<<"load is "<<load<<endl;
		outfile<<"client_num is "<<client_num<<endl;
		for(i=0;i<3;i++)
		{
			result[i]=result[i]/3;
			outfile<<result[i]<<" ";
		}
		outfile<<endl<<endl;
		load+=20;
	}
	outfile.close();
	return 0;
}
