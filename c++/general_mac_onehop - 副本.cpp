#include "iostream"
#include "time.h"
#include "stdlib.h"
#include "math.h"
using namespace std;
#define CWmin 32
#define CWmax 1024
#define w_slot 9
#define z_slot 32
#define w_frame 1000
#define z_frame 250
#define w_band 20
#define z_band 0.25
#define BEmin 4
#define BEmax 16

struct sys_sta
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
	int dif;
	int sif;
};

void csma(int client_num)
{
	struct sys_sta sta_z[client_num],sta_w[client_num];
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
	int run_time=10000000;
	
	for(i=0;i<client_num;i++)
	{
		sta_w[i].cw=CWmin;
		sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
		sta_w[i].transmit=false;
		sta_w[i].length=0;
		sta_w[i].trigger=false;
		sta_w[i].dif=34;
		sta_w[i].sif=16;
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
	}
	
	for(t=0;t<run_time;t++)
	{
		for(i=0;i<client_num;i++)
		{
			if(tx_num==0&&sta_w[i].transmit==false)
			{
				if(sta_w[i].dif>0)
					sta_w[i].dif--;
				else
				{
					sta_w[i].backoff--;
					if(sta_w[i].backoff==0)
					{
						sta_w[i].transmit=true;
						sta_w[i].length=w_frame;
						sta_w[i].trigger=true;
						sta_w[i].dif=34;
						tmp++;
					}
				}
			}
			else if(sta_w[i].transmit==true)
			{
				if(sta_w[i].trigger==true)
				{
					sta_w[i].trigger=false;
					sta_w[i].length--;
					tx_amount++;
					wifi_tx_amount++;
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
						data_amount+=w_frame*w_band;
						wifi_data_amount+=w_frame*w_band;
						success_amount++;
						wifi_success_amount++;
						sta_w[i].cw=sta_w[i].cw/2;
						if(sta_w[i].cw<CWmin)
							sta_w[i].cw=CWmin;
						sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
					}
				}
				else
				{
					sta_w[i].length--;
					if(sta_w[i].length==0)
					{
						sta_w[i].transmit=false;
						tmp--;
					}
				}
			}
		}
		
//		for(i=0;i<client_num;i++)
//		{
//			if(sta_z[i].transmit==false)
//			{
//				if(sta_z[i].backoff>0)
//					sta_z[i].backoff--;
//				if(sta_z[i].backoff==0)
//				{
//					if(tx_num==0)
//					{
//						sta_z[i].cca--;
//						if(sta_z[i].cca==0)
//						{
//						sta_z[i].transmit=true;
//						sta_z[i].length=z_frame;
//						sta_z[i].trigger=true;
//						sta_z[i].cca=z_slot;
//						sta_z[i].idle=false;
//						tmp++;
//						sta_z[i].cw=BEmin;
//						sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
//						}
//					}
//					else
//					{
//						sta_z[i].cca=z_slot;
//						sta_z[i].cw=sta_z[i].cw*2;
//						if(sta_z[i].cw>BEmax)
//							sta_z[i].cw=BEmax;
//						sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
//					}
//				}
//			}
//			else if(sta_z[i].transmit==true)
//			{
//				if(sta_z[i].trigger==true)
//				{
//					sta_z[i].trigger=false;
//					sta_z[i].length--;
//					tx_amount++;
//					zigbee_tx_amount++;
//					if(tx_num>1)
//					{
//						colli_amount++;
//						zigbee_colli_amount++;
//					}
//					else
//					{
//						data_amount+=z_frame*z_band;
//						zigbee_data_amount+=z_frame*z_band;
//						success_amount++;
//						zigbee_success_amount++;
//					}
//				}
//				else
//				{
//					sta_z[i].length--;
//					if(sta_z[i].length==0)
//					{
//						sta_z[i].transmit=false;
//						tmp--;
//					}
//				}
//			}
//		}
		
		for(i=0;i<client_num;i++)
		{
			if(sta_z[i].transmit==false)
			{
				if(sta_z[i].backoff>0)
					sta_z[i].backoff--;
				if(sta_z[i].backoff==0)
				{
					if(sta_z[i].cca==z_slot)
					{
						if(tx_num==0)
							sta_z[i].cca--;
						else
						{
							sta_z[i].cca=z_slot;
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
						sta_z[i].transmit=true;
						sta_z[i].length=z_frame;
						sta_z[i].trigger=true;
						sta_z[i].cca=z_slot;
						sta_z[i].idle=false;
						tmp++;
						sta_z[i].cw=BEmin;
						sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
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
					tx_amount++;
					zigbee_tx_amount++;
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
	cout<<"The wifi data amount is "<<wifi_data_amount<<endl;
	cout<<"The zigbee tx amount is "<<zigbee_tx_amount<<endl;
	cout<<"The zigbee collision amount is "<<zigbee_colli_amount<<endl;
	cout<<"The zigbee success amount is "<<zigbee_success_amount<<endl;
	cout<<"The zigbee data amount is "<<zigbee_data_amount<<endl;
	double ratio=(float)zigbee_success_amount/(float)success_amount;
	cout<<"The ratio is "<<ratio<<endl;
	cout<<endl;
}

int main()
{
	int client_num=5;
	srand((unsigned int)time(NULL));
	while(client_num<55)
	{
		csma(client_num);
		client_num+=5;
	}
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

