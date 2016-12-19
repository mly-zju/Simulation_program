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
wifi_tx=[0 52494 94880 94988 94950 95059 95058 94998 94998];              
wifi_collision=[0 22662 45590 45929 46141 46274 46021 45948 45948];
wifi_succeed=wifi_tx-wifi_collision;
wifi_collision_p=wifi_collision./wifi_tx;
wifi_collision_p(1)=0;
wifi_delay=[0 14.7398 55.581 56.8964 57.073 57.0976 56.7665 57.215 57.215]/1000;
wifi_throughput=[0 5.9664 9.8578 9.8316 9.8218 9.8168 9.8672 9.8098 9.8098];

zigbee_tx=[0 61795 8834 8558 8745 8771 8592 8753 8753];
zigbee_collision=[0 36732 8797 8543 8730 8757 8577 8742 8742];
zigbee_succeed=zigbee_tx-zigbee_collision;
zigbee_collision_p=zigbee_collision./zigbee_tx;
zigbee_collision_p(1)=0;
zigbee_delay=[0 59.7011 81015.8 199843 199824 214094 199835 272439 272439]/1000;
zigbee_throughput=[0 1553906 2294 930 930 868 930 682 682];
zigbee_throughput=zigbee_throughput./100000000;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wifi_tx2=[0 45379 92497 92471 92524 92535 92586 92557 92557];
wifi_collision2=[0 16720 43016 43318 43150 43215 43303 43348 43348];
wifi_succeed2=wifi_tx2-wifi_collision2;
wifi_collision_p2=wifi_collision2./wifi_tx2;
wifi_collision_p2(1)=0;
wifi_delay2=[0 11.542 52.2469 54.7744 54.5454 54.6585 54.7312 54.8204 54.8204]/1000;
wifi_throughput2=[0 5.7316 9.8962 9.8306 9.8746 9.8638 9.8564 9.8418 9.8418];

zigbee_tx2=[0 867 1700 2689 3597 4639 5520 5863 5863];
zigbee_collision2=[0 70 326 911 1500 2301 3080 3342 3342];
zigbee_succeed2=zigbee_tx2-zigbee_collision2;
zigbee_collision_p2=zigbee_collision2./zigbee_tx2;
zigbee_collision_p2(1)=0;
zigbee_delay2=[0 4.84469 7.1698 10.5893 15.0152 19.8135 25.5053 26.6877 26.6877]/1000;
zigbee_throughput2=[0 49414 85188 110236 130014 144956 151280 156302 156302];
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