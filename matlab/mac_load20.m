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
wifi_tx=[0 26167 70852 95012 95612 96170 96594 96902 97276];              
wifi_collision=[0 6248 31152 45644 49365 51705 54311 56388 58321];
wifi_succeed=wifi_tx-wifi_collision;
wifi_collision_p=wifi_collision./wifi_tx;
wifi_collision_p(1)=0;
wifi_delay=[0 2.91552 17.4856 55.3695 81.6387 106.756 135.531 165.465 197.159]/1000;
wifi_throughput=[0 3.9838 7.94 9.8736 9.2492 8.8928 8.4564 8.1026 7.7908];

zigbee_tx=[0 13509 46074 8753 9356 9281 10097 10153 9923];
zigbee_collision=[0 4128 28335 8719 9346 9278 10092 10152 9922];
zigbee_succeed=zigbee_tx-zigbee_collision;
zigbee_collision_p=zigbee_collision./zigbee_tx;
zigbee_collision_p(1)=0;
zigbee_delay=[0 20.3592 87.7324 2500 10000 33000 45000 80000 90000]/1000;
zigbee_throughput=[0 581622 1099818 2108 620 186 310 62 62];
zigbee_throughput=zigbee_throughput./100000000;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wifi_tx2=[0 23507 63026 92513 93082 93520 93852 94233 94408];
wifi_collision2=[0 4189 25162 42698 46422 49204 51330 53607 55503];
wifi_succeed2=wifi_tx2-wifi_collision2;
wifi_collision_p2=wifi_collision2./wifi_tx2;
wifi_collision_p2(1)=0;
wifi_delay2=[0 2.32179 14.2427 50.8579 77.783 103.278 129.909 159.29 190.689]/1000;
wifi_throughput2=[0 3.8636 7.5726 9.9628 9.332 8.863 8.5042 8.1252 7.781];

zigbee_tx2=[0 611 1201 1736 2430 3094 4080 5183 6386 ];
zigbee_collision2=[0 51 181 342 750 1179 1984 2977 4052];
zigbee_succeed2=zigbee_tx2-zigbee_collision2;
zigbee_collision_p2=zigbee_collision2./zigbee_tx2;
zigbee_collision_p2(1)=0;
zigbee_delay2=[0 4.45248 5.95621 7.16836 9.96725 12.8175 18.4016 26.0167 33.2097]/1000;
zigbee_throughput2=[0 34720 63240 86428 104160 118730 129952 136772 144708];
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