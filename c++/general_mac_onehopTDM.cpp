#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;
#define CWmin 32
#define CWmax 1024
#define w_slot 9
#define z_slot 320
#define wait 20
#define w_frame 1000
#define z_frame 250
#define w_band 20
#define z_band 0.25
#define BEmin 16
#define BEmax 32
#define dif 0
#define contend 1
#define transmission 2
#define sif 3
#define ack 4
#define collision 5
#define division 128

struct sys_sta_z
{
	int backoff;
	int cw;
	//int load;
	bool transmit;
	//int state;
	int length;
	bool trigger;
	int cca;
	bool idle;
	int nb;
};

struct sys_sta_w
{
	int backoff;
	int cw;
	//int load;
	int state;
	//int state;
	int length;
	bool trigger;
	bool trigger2;
	bool idle;
};

void csma(int client_num)
{
	struct sys_sta_z sta_z[client_num];
	struct sys_sta_w sta_w[client_num];
	int i=0;
	int j=0;
	int t=0;
	int tx_amount=0;
	int colli_amount=0;
	int success_amount=0;
	double data_amount=0;
	int wifi_tx_amount=0;
	int wifi_colli_amount=0;
	int wifi_success_amount=0;
	double wifi_data_amount=0;
	int zigbee_tx_amount=0;
	int zigbee_colli_amount=0;
	int zigbee_success_amount=0;
	int zigbee_data_amount=0;
	int tx_num=0;
	int tmp=0;
	int run_time=100000000;
	
	for(i=0;i<client_num;i++)
	{
		sta_w[i].cw=CWmin;
		sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
		sta_w[i].state=dif;
		sta_w[i].length=34;
		sta_w[i].trigger=false;
		sta_w[i].trigger2=false;
	}
	for(i=0;i<client_num;i++)
	{
		sta_z[i].cw=BEmin;
		sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
		sta_z[i].transmit=false;
		sta_z[i].length=0;
		sta_z[i].trigger=false;
		sta_z[i].cca=z_slot;
		sta_z[i].idle=false;
		sta_z[i].nb=0;
	}
	
	for(t=0;t<run_time;t++)
	{
		if(t<=round(run_time/division))
		{
			for(i=0;i<client_num;i++)
			{
				if(sta_z[i].transmit==false)
				{
					if(sta_z[i].backoff>0)
						sta_z[i].backoff--;
					if(sta_z[i].backoff==0)
					{
						if(sta_z[i].cca>=z_slot-wait)
						{
							if(tx_num==0)
								sta_z[i].cca--;
							else
							{
								sta_z[i].cca=z_slot;
								sta_z[i].nb=0;
								sta_z[i].cw=sta_z[i].cw*2;
								if(sta_z[i].cw>BEmax)
									sta_z[i].cw=BEmax;
								sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
							}
						}
						else
						{
							sta_z[i].cca--;
							if(sta_z[i].cca==0)
							{
								sta_z[i].nb++;
								if(sta_z[i].nb==1)
									sta_z[i].cca=z_slot;
								else if(sta_z[i].nb==2)
								{
									sta_z[i].transmit=true;
									sta_z[i].length=z_frame;
									sta_z[i].trigger=true;
									sta_z[i].cca=z_slot;
									sta_z[i].idle=false;
									sta_z[i].nb=0;
									tx_amount++;
									zigbee_tx_amount++;
									tmp++;
									sta_z[i].cw=BEmin;
									sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
								}
							}
						}
					}
				}
				else if(sta_z[i].transmit==true)
				{
					if(sta_z[i].trigger==true)
					{
						sta_z[i].trigger=false;
						sta_z[i].length--;
						if(tx_num>1)
						{
							colli_amount++;
							zigbee_colli_amount++;
						}
						else
						{
							data_amount+=z_frame*z_band;
							zigbee_data_amount+=z_frame*z_band;
							success_amount++;
							zigbee_success_amount++;
						}
					}
					else
					{
						sta_z[i].length--;
						if(sta_z[i].length==0)
						{
							sta_z[i].transmit=false;
							tmp--;
						}
					}
				}
			}
		}
		else
		{
			for(i=0;i<client_num;i++)
			{
				if(sta_w[i].state==dif)
				{
					if(tx_num==0)
						sta_w[i].length--;
					else 
						sta_w[i].length=34;
					if(sta_w[i].length==0)
						sta_w[i].state=contend;
				}
				else if(sta_w[i].state==contend)
				{
					if(tx_num==0)
						sta_w[i].backoff--;
					if(sta_w[i].backoff==0)
					{
						sta_w[i].state=transmission;
						sta_w[i].length=w_frame;
						tx_amount++;
						wifi_tx_amount++;
						tmp++;
						sta_w[i].trigger=true;
					}
				}
				else if(sta_w[i].state==transmission)
				{
					if(sta_w[i].trigger==true&&tx_num>1)
					{
						sta_w[i].state=collision;
						colli_amount++;
						wifi_colli_amount++;
						sta_w[i].cw=sta_w[i].cw*2;
						if(sta_w[i].cw>CWmax)
							sta_w[i].cw=CWmax;
						sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
						sta_w[i].trigger=false;
					}
					sta_w[i].length--;
					if(sta_w[i].length==0)
					{
						sta_w[i].state=sif;
						sta_w[i].trigger=false;
						sta_w[i].length=16;
						tmp--;
					}
				}
				else if(sta_w[i].state==collision)
				{
					sta_w[i].length--;
					if(sta_w[i].length==0)
					{
						sta_w[i].state=dif;
						sta_w[i].length=34;
						tmp--;
					}
				}
				else if(sta_w[i].state==sif)
				{
					sta_w[i].length--;
					if(sta_w[i].length==0)
					{
						sta_w[i].state=ack;
						sta_w[i].length=39;
						tmp++;
					}
				}
				else if(sta_w[i].state==ack)
				{
					sta_w[i].length--;
					if(sta_w[i].length==0)
					{
						sta_w[i].state=dif;
						sta_w[i].length=34;
						tmp--;
						if(tx_num>1)
						{
							colli_amount++;
							wifi_colli_amount++;
							sta_w[i].cw=sta_w[i].cw*2;
							if(sta_w[i].cw>CWmax)
								sta_w[i].cw=CWmax;
							sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
						}
						else
						{
							success_amount++;
							wifi_success_amount++;
							data_amount+=w_frame*w_band;
							wifi_data_amount+=w_frame*w_band;
							sta_w[i].cw=sta_w[i].cw/2;
							if(sta_w[i].cw<CWmin)
								sta_w[i].cw=CWmin;
							sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
						}
					}
				}
			}
		}
		if(t==round(run_time/division))
			tmp=0;
		tx_num=tmp;
	}
	cout<<"The client num is "<<client_num<<endl;
	cout<<"The total tx amount is "<<tx_amount<<endl;
	cout<<"The total collision amount is "<<colli_amount<<endl;
	cout<<"The total success amount is "<<success_amount<<endl;
	cout<<"The total data amount is "<<data_amount<<endl;
	cout<<"The wifi tx amount is "<<wifi_tx_amount<<endl;
	cout<<"The wifi collision amount is "<<wifi_colli_amount<<endl;
	cout<<"The wifi success amount is "<<wifi_success_amount<<endl;
	double ratio=(float)wifi_colli_amount/(float)wifi_tx_amount;
	cout<<"The wifi collision ratio is "<<ratio<<endl;
	cout<<"The wifi data amount is "<<wifi_data_amount<<endl;
	cout<<endl;
	cout<<"The zigbee tx amount is "<<zigbee_tx_amount<<endl;
	cout<<"The zigbee collision amount is "<<zigbee_colli_amount<<endl;
	cout<<"The zigbee success amount is "<<zigbee_success_amount<<endl;
	ratio=(float)zigbee_colli_amount/(float)zigbee_tx_amount;
	cout<<"The zigbee collision ratio is "<<ratio<<endl;
	cout<<"The zigbee data amount is "<<zigbee_data_amount<<endl;
	ratio=(float)zigbee_success_amount/(float)success_amount;
	cout<<"The ratio is "<<ratio<<endl;
	cout<<endl;
}

int main()
{
	int client_num=5;
	srand((unsigned int)time(NULL));
	while(client_num<25)
	{
		csma(client_num);
		client_num+=5;
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

