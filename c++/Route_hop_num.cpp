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
};
struct sys_sta
{
	int x;
	int y;
};

int coo2num(int x,int y,int side)
{
	return x*side+y;
}
int num2coox(int num,int side)
{
	return num/side;
}
int num2cooy(int num,int side)
{
	return num%side;
}
int max(int x,int y)
{
	if(x>y)
		return x;
	else return y;
}

double *simu(int side,int density)
{
	int block=side*side;
	struct sys_map map[block][density];
	int i=0;
	int j=0;
	int t=0;
	int t_position=0;
	int r_position=0;
	int delta_x=0;
	int delta_y=0;
	int t_block=0;
	int r_block=0;
	int tmp=0;
	int tmp2=0;
	int tmp3=0;
	int tmp4=0;
	int hop_num=0;
	int t_x=0;
	int t_y=0;
	int r_x=0;
	int r_y=0;
	double average_hop[2]={0,0};
	int total=block*density;
	int tt=0;
	int tt2=0;
	//srand((unsigned int)time(NULL));
	for(i=0;i<block;i++)
	{
		for(j=0;j<density;j++)
		{
			map[i][j].x=rand()%5;
			map[i][j].y=rand()%5;
		}
	}
	
	for(t=0;t<99999;t++)
	{
		t_block=rand()%block;
		r_block=rand()%block;
		t_position=rand()%density;
		while(r_position==t_position)
			r_position=rand()%density;
//		tt=rand()%total;
//		do{tt2=rand()%total;}while(tt2==tt);
//		t_block=tt/density;
//		t_position=tt%density;
//		r_block=tt2/density;
//		r_position=tt2%density;
//		tmp=num2coox(t_block,side)-num2coox(r_block,side);
//		if(tmp>0)
//			delta_x=tmp*5+map[t_block][t_position].x-map[r_block][r_position].x;
//		else if(tmp==0)
//			delta_x=abs(map[t_block][t_position].x-map[r_block][r_position].x);
//		else
//			delta_x=tmp*5+map[r_block][r_position].x-map[t_block][t_position].x;
//		tmp=num2cooy(t_block,side)-num2cooy(r_block,side);
//		if(tmp>0)
//			delta_y=tmp*5+map[t_block][t_position].y-map[r_block][r_position].y;
//		else if(tmp==0)
//			delta_y=abs(map[t_block][t_position].y-map[r_block][r_position].y);
//		else
//			delta_y=tmp*5+map[r_block][r_position].y-map[t_block][t_position].y;
//		hop_num+=max(delta_x,delta_y);
		t_x=num2coox(t_block,side)*5+map[t_block][t_position].x;
		t_y=num2cooy(t_block,side)*5+map[t_block][t_position].y;
		r_x=num2coox(r_block,side)*5+map[r_block][r_position].x;
		r_y=num2cooy(r_block,side)*5+map[r_block][r_position].y;
		hop_num+=max(abs(t_x-r_x),abs(t_y-r_y));
	}
	average_hop[0]=(double)hop_num/99999;
	hop_num=0;
	for(t=0;t<99999;t++)
	{
		t_block=rand()%block;
		r_block=rand()%block;
		t_position=rand()%density;
		while(r_position==t_position)
			r_position=rand()%density;
//		tt=rand()%total;
//		do{tt2=rand()%total;}while(tt2==tt);
//		t_block=tt/density;
//		t_position=tt%density;
//		r_block=tt2/density;
//		r_position=tt2%density;
		tmp=abs(num2coox(t_block,side)-num2coox(r_block,side));
		tmp2=abs(num2cooy(t_block,side)-num2cooy(r_block,side));
		tmp3=max(abs(map[t_block][t_position].x-2),abs(map[t_block][t_position].y-2));
		tmp4=max(abs(map[r_block][r_position].x-2),abs(map[r_block][r_position].y-2));
//		if(t_block==r_block)
//			hop_num+=max(abs(map[t_block][t_position].x-map[r_block][r_position].x),abs(map[t_block][t_position].y-map[r_block][r_position].y));
//		else if(max(abs(map[t_block][t_position].x-map[r_block][r_position].x),abs(map[t_block][t_position].y-map[r_block][r_position].y))==1)
//			hop_num+=max(abs(map[t_block][t_position].x-map[r_block][r_position].x),abs(map[t_block][t_position].y-map[r_block][r_position].y));
		t_x=num2coox(t_block,side)*5+map[t_block][t_position].x;
		t_y=num2cooy(t_block,side)*5+map[t_block][t_position].y;
		r_x=num2coox(r_block,side)*5+map[r_block][r_position].x;
		r_y=num2cooy(r_block,side)*5+map[r_block][r_position].y;
		if(t_block==r_block||max(abs(t_x-r_x),abs(t_y-r_y))<2)
			hop_num+=max(abs(t_x-r_x),abs(t_y-r_y));
		else
			hop_num+=tmp3+tmp4+max(tmp,tmp2);
	}
	average_hop[1]=(double)hop_num/99999;

	return average_hop;
}

int main()
{
	int side=0;
	int density=60;
	double ave_hop[2]={0,0};
	double *tmp;
	int i=0;
	srand((unsigned int)time(NULL));
	for(side=1;side<16;side++)
	{
		for(i=0;i<200;i++)
		{
			tmp=simu(side,density);
			ave_hop[0]+=tmp[0];
			ave_hop[1]+=tmp[1];
			tmp[0]=0;
			tmp[1]=0;
		}
		ave_hop[0]=ave_hop[0]/200;
		ave_hop[1]=ave_hop[1]/200;
		cout<<"When side is "<<side<<" The final average hop number is "<<ave_hop[0]<<" and "<<ave_hop[1]<<endl;
	}
	return 0;
}
