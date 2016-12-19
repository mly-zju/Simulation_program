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
#define wait 40
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
#define division 32

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
	int nb;
	int packet;
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
	int packet;
};

struct packet_map
{
	int time;
	int sta;
};

bool contain(int t, struct packet_map *m, int load)
{
	int i=0;
	for(i=0;i<load;i++)
		if(t==m[i].time)
			return true;
	return false;
}

void csma(int client_num, int load)
{
	
	struct sys_sta_z sta_z[client_num];
	struct sys_sta_w sta_w[client_num];
	struct packet_map tmp_map;
	int i=0;
	int j=0;
	int t=0;
	int w=0;
	int z=0;
	int test=0;
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
	int multi=run_time/1000000;
	int z_load=load*client_num*1.04;
	int w_load=load*client_num;
	double z_delay=0;
	double w_delay=0;
	int load_num=z_load+w_load;
	struct packet_map wpk[w_load];
	struct packet_map zpk[z_load];
	int zigbee_time=run_time/division;
	ofstream outfile;
	outfile.open("data2.txt",ios::app);
	
	for(i=0;i<client_num;i++)
	{
		sta_w[i].cw=CWmin;
		sta_w[i].backoff=(rand()%sta_w[i].cw+1)*w_slot;
		sta_w[i].state=dif;
		sta_w[i].length=34;
		sta_w[i].trigger=false;
		sta_w[i].packet=0;
	}
	for(i=0;i<client_num;i++)
	{
		sta_z[i].cw=BEmin;
		sta_z[i].backoff=(rand()%sta_z[i].cw+1)*z_slot;
		sta_z[i].transmit=false;
		sta_z[i].length=0;
		sta_z[i].trigger=false;
		sta_z[i].cca=z_slot;
		sta_z[i].nb=0;
		sta_z[i].packet=0;
	}
	for(i=0;i<w_load;i++)
	{
		wpk[i].sta=0;
		wpk[i].time=0;
	}
	for(i=0;i<z_load;i++)
	{
		zpk[i].sta=0;
		zpk[i].time=0;
	}
	tmp_map.sta=0;
	tmp_map.time=0;
	for(i=0;i<w_load-1;i++)
	{
		for(j=0;j<w_load-i-1;j++)
		{
			if(wpk[j].time>wpk[j+1].time)
			{
				tmp_map=wpk[j];
				wpk[j]=wpk[j+1];
				wpk[j+1]=tmp_map;
			}
		}
	}
	tmp_map.sta=0;
	tmp_map.time=0;
	for(i=0;i<z_load-1;i++)
	{
		for(j=0;j<z_load-i-1;j++)
		{
			if(zpk[j].time>zpk[j+1].time)
			{
				tmp_map=zpk[j];
				zpk[j]=zpk[j+1];
				zpk[j+1]=tmp_map;
			}
		}
	}
//	for(i=0;i<z_load;i++)
//		cout<<zpk[i].time<<" "<<zpk[i].sta<<endl;
	
	for(t=0;t<run_time;t++)
	{
		if(t%1000000==0&&t<=zigbee_time)
		{
			w=0;
			z=0;
//			for(i=0;i<w_load;i++)
//			{
//				wpk[i].time=(rand()%10)*100000+(rand()%10)*10000+rand()%10000+t+zigbee_time;
//				if(wpk[i].time>100000000)
//					wpk[i].time-=zigbee_time;
//				wpk[i].time=wpk[i].time/w_slot;
//				wpk[i].sta=rand()%client_num;
//			}
			for(i=0;i<z_load;i++)
			{
				zpk[i].time=(rand()%10)*100000+(rand()%10)*10000+rand()%10000+t;
				zpk[i].time=zpk[i].time/z_slot;
				zpk[i].sta=rand()%client_num;
			}
			
		}
		else if(t%1000000==0&&t>zigbee_time)
		{
			w=0;
			z=0;
			for(i=0;i<w_load;i++)
			{
				wpk[i].time=(rand()%10)*100000+(rand()%10)*10000+rand()%10000+t;
				wpk[i].time=wpk[i].time/w_slot;
				wpk[i].sta=rand()%client_num;
			}
//			for(i=0;i<z_load;i++)
//			{
//				zpk[i].time=(rand()%10)*100000+(rand()%10)*10000+rand()%10000+t;
//				zpk[i].time=zpk[i].time/z_slot;
//				zpk[i].sta=rand()%client_num;
//			}
		}
		if(t%w_slot==0)
		{
			if(contain(t/w_slot,wpk,w_load))
			{
				sta_w[wpk[w].sta].packet++;
				w++;
				//cout<<"w is "<<w<<endl;
			}
		}
		if(t%z_slot==0)
		{
			if(contain(t/z_slot,zpk,z_load))
			{
				sta_z[zpk[z].sta].packet++;
				z++;
			}
		}
		if(t>zigbee_time)
		{
			for(i=0;i<client_num;i++)
			{
				if(sta_w[i].packet>0)
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
						w_delay++;
						if(tx_num==0)
						{
							sta_w[i].backoff--;
						}
						if(sta_w[i].backoff==0)
						{
							sta_w[i].state=transmission;
							//cout<<"tx time is "<<t<<endl;
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
							//w_delay+=w_frame;
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
							w_delay+=w_frame;
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
//							w_delay+=w_frame*sta_w[i].packet;
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
								sta_w[i].packet--;
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
		}
		else if(t<=zigbee_time)
		{
			for(i=0;i<client_num;i++)
			{
				if(sta_z[i].packet>0)
				{
					if(sta_z[i].transmit==false)
					{
						if(sta_z[i].backoff>0)
						{
							sta_z[i].backoff--;
							z_delay++;
						}
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
									z_delay+=z_slot;
									if(sta_z[i].nb==1)
										sta_z[i].cca=z_slot;
									else if(sta_z[i].nb==2)
									{
									sta_z[i].transmit=true;
									sta_z[i].length=z_frame;
									sta_z[i].trigger=true;
									sta_z[i].cca=z_slot;
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
								z_delay+=z_frame;
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
								if(tx_num==1)
									sta_z[i].packet--;
								sta_z[i].transmit=false;
								//sta_z[i].packet--;
								tmp--;
							}
						}
					}
				}
			}
		}
		if(t==zigbee_time)
			tmp=0;
		tx_num=tmp;
	}
	outfile<<"The load is "<<load<<endl;
	outfile<<"The client_num is "<<client_num<<endl;
	outfile<<"The wifi tx amount is "<<wifi_tx_amount<<endl;
	outfile<<"The wifi collision amount is "<<wifi_colli_amount<<endl;
	outfile<<"The wifi success amount is "<<wifi_success_amount<<endl;
	double ratio=(float)wifi_colli_amount/(float)wifi_tx_amount;
	outfile<<"The wifi collision ratio is "<<ratio<<endl;
	outfile<<"The wifi data amount is "<<wifi_data_amount<<endl;
	double delay=(double)w_delay/(double)(wifi_success_amount*1000);
	outfile<<"The wifi delay is "<<delay<<endl;
	outfile<<endl;
	outfile<<"The zigbee tx amount is "<<zigbee_tx_amount<<endl;
	outfile<<"The zigbee collision amount is "<<zigbee_colli_amount<<endl;
//	outfile<<"The zigbee success amount is "<<zigbee_success_amount<<endl;
	ratio=(float)zigbee_colli_amount/(float)zigbee_tx_amount;
	outfile<<"The zigbee collision ratio is "<<ratio<<endl;
	outfile<<"The zigbee data amount is "<<zigbee_data_amount<<endl;
	delay=(double)z_delay/(double)(zigbee_success_amount*1000);
	outfile<<"The zigbee delay is "<<delay<<endl;
	outfile<<endl;
	outfile.close();
}

int main()
{
	int client_num=10;
	int load=200;
	while(client_num<=90)
	{
		srand((unsigned int)time(NULL));
		csma(client_num,load);
		client_num+=10;
	}
	cout<<"********************************"<<endl;
//	load=10;
//	client_num=10;
//	while(load<=70)
//	{
//		srand((unsigned int)time(NULL));
//		csma(client_num,load);
//		load+=10;
//	}
//	cout<<"*********************************"<<endl;
//	load=120;
//	client_num=20;
//	while(load<=120)
//	{
//		srand((unsigned int)time(NULL));
//		csma(client_num,load);
//		load+=50;
//	}
//	cout<<"*********************************"<<endl;
//	load=70;
//	client_num=30;
//	while(load<=70)
//	{
//		srand((unsigned int)time(NULL));
//		csma(client_num,load);
//		load+=10;
//	}
//	cout<<"*********************************"<<endl;
//	return 0;
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

