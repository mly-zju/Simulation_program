clc;
x=0:10:80;
zigbee_tx=zeros(1,9);
zigbee_collision=zeros(1,9);
zigbee_succceed=zeros(1,9);
zigbee_throughput=zeros(1,9);
zigbee_delay=zeros(1,9);
zigbee_collison_p=zeros(1,9);
wifi_tx=zeros(1,9);
wifi_collision=zeros(1,9);
wifi_succceed=zeros(1,9);
wifi_throughput=zeros(1,9);
wifi_delay=zeros(1,9);
wifi_collision_p=zeros(1,9);

zigbee_tx2=zeros(1,9);
zigbee_collision2=zeros(1,9);
zigbee_succceed2=zeros(1,9);
zigbee_throughput2=zeros(1,9);
zigbee_delay2=zeros(1,9);
zigbee_collison_p2=zeros(1,9);
wifi_tx2=zeros(1,9);
wifi_collision2=zeros(1,9);
wifi_succceed2=zeros(1,9);
wifi_throughput2=zeros(1,9);
wifi_delay2=zeros(1,9);
wifi_collison_p2=zeros(1,9);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wifi_tx=[0 44396 94169 94937 95648 96166 96521 96521 96521];              
wifi_collision=[0 14553 41153 45861 49150 51826 54284 56284 58284];
wifi_succeed=wifi_tx-wifi_collision;
wifi_collision_p=wifi_collision./wifi_tx;
wifi_collision_p(1)=0;
wifi_delay=[0 5.99168 33.1657 57.1175 81.2054 107.207 135.635 159.635 179.635]/1000;
wifi_throughput=[0 5.9686 10.6032 9.815 9.2994 8.8678 8.4472 8.0472 7.8472];

zigbee_tx=[0 14212 7494 8854 9066 9519 9921 9921 9921];
zigbee_collision=[0 4806 7453 8837 9060 9517 9917 9919 9920];
zigbee_succeed=zigbee_tx-zigbee_collision;
zigbee_collision_p=zigbee_collision./zigbee_tx;
zigbee_collision_p(1)=0;
zigbee_delay=[0 34.6288 2500 5000 10000 50000 60000 80000 90000]/1000;
zigbee_throughput=[0 583172 2542 1054 372 248 208 148 124];
zigbee_throughput=zigbee_throughput./100000000;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wifi_tx2=[0 40995 91680 92662 93105 93498 93793 93793 93793];
wifi_collision2=[0 12085 38312 43287 46503 49121 51150 52150 53150];
wifi_succeed2=wifi_tx2-wifi_collision2;
wifi_collision_p2=wifi_collision2./wifi_tx2;
wifi_collision_p2(1)=0;
wifi_delay2=[0 4.47841 7.60687 10.493 16.2435 23.346 35.6041 44.6041 56.6041]/1000;
wifi_throughput2=[0 5.782 10.6736 9.8748 9.3202 8.8752 8.5284 8.2284 7.9284];

zigbee_tx2=[0 870 1783 2674 3758 5067 7409 7409 7409];
zigbee_collision2=[0 64 375 862 1644 2759 4859 5559 5959];
zigbee_succeed2=zigbee_tx2-zigbee_collision2;
zigbee_collision_p2=zigbee_collision2./zigbee_tx2;
zigbee_collision_p2(1)=0;
zigbee_delay2=[0 4.47841 7.60687 10.493 16.2435 23.346 39.6041 43.6041 49.6041]/1000;
zigbee_throughput2=[0 49972 87296 112344 131068 143096 151900 151900 151900];
zigbee_throughput2=zigbee_throughput2./100000000;


figure(1);
subplot(2,1,1);
hold on;
grid on;
plot(x,wifi_collision_p,'-*r');
plot(x,wifi_collision_p2,'-ob');
legend('wifi system without TDM','wifi system with TDM','location','northwest');
xlabel('client number');
ylabel('collision probability');
subplot(2,1,2);
hold on;
grid on;
plot(x,zigbee_collision_p,'-*r');
plot(x,zigbee_collision_p2,'-ob');
legend('zigbee system without TDM','zigbee system with TDM','location','northwest');
xlabel('client number');
ylabel('collision probability');
figure(2);
hold on;
grid on;
subplot(2,1,1);
hold on;
grid on;
plot(x,wifi_throughput,'-*r');
plot(x,wifi_throughput2,'-ob');
xlabel('client number');
ylabel('Throughput (Mbps/s)');
legend('wifi system without TDM','wifi system with TDM','location','northwest');
subplot(2,1,2);
hold on;
grid on;
plot(x,zigbee_throughput,'-*r');
plot(x,zigbee_throughput2,'-ob');
xlabel('client number');
ylabel('Throughput (Mbps/s)');
legend('zigbee system without TDM','zigbee system with TDM','location','northwest');
figure(3);
subplot(2,1,1);
hold on;
grid on;
plot(x,wifi_delay,'-*r');
plot(x,wifi_delay2,'-ob');
legend('wifi system without TDM','wifi system with TDM','location','northwest');
xlabel('client number');
ylabel('Delay (s)');
subplot(2,1,2);
hold on;
grid on;
plot(x,zigbee_delay,'-*r');
plot(x,zigbee_delay2,'-ob');
legend('zigbee system without TDM','zigbee system with TDM','location','northwest');
xlabel('client number');
ylabel('Delay (s)');
set(gca,'yscale','log');