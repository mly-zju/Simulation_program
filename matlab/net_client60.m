clc;
x=0:10:80;
wifi_tx=zeros(1,9);
wifi_collision=zeros(1,9);
wifi_succceed=zeros(1,9);
wifi_throughput=zeros(1,9);
wifi_delay=zeros(1,9);
wifi_collision_p=zeros(1,9);

wifi_tx2=zeros(1,9);
wifi_collision2=zeros(1,9);
wifi_succceed2=zeros(1,9);
wifi_throughput2=zeros(1,9);
wifi_delay2=zeros(1,9);
wifi_collison_p2=zeros(1,9);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wifi_collision_p=[0 0.254515 0.304094 0.32886 0.350532 0.357665 0.36236 0.369412 0.374753];
wifi_delay=[0 4.12532 5.47237 6.56165 7.47434 7.87556 8.10772 8.43044 8.5526];
wifi_throughput=[0 2.19287 4.30965 6.3949 8.2901 10.0133 11.4308 12.5113 13.8494];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
wifi_collision_p2=[0 0.0753938  0.117288 0.161001 0.221391 0.271752 0.323361 0.338024 0.348157];
wifi_delay2=[0 2.85686 3.31455 3.59001 4.06251 4.6632 5.64066 6.61688 7.19364];
wifi_throughput2=[0 2.18571 4.33688 6.56129 8.65755 11.0727 13.2157 14.7966 16.2181];

figure(1);
hold on;
grid on;
plot(x,wifi_collision_p,'-*r');
plot(x,wifi_collision_p2,'-ob');
legend('wifi system without hierarchical structure','wifi system with hierarchical structure','location','northwest');
xlabel('data load(pk/s)');
ylabel('collision probability');
figure(2);
hold on;
grid on;
plot(x,wifi_throughput,'-*r');
plot(x,wifi_throughput2,'-ob');
xlabel('data load(pk/s)');
ylabel('Throughput (Mbps/s)');
legend('wifi system without hierarchical structure','wifi system with hierarchical structure','location','northwest');
figure(3);
hold on;
grid on;
plot(x,wifi_delay,'-*r');
plot(x,wifi_delay2,'-ob');
legend('wifi system without hierarchical structure','wifi system with hierarchical structure','location','northwest');
xlabel('data load(pk/s)');
ylabel('Delay (s)');