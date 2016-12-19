x=0:1:9
hop1=zeros(1,10);
hop2=zeros(1,10);
hop1=[0 2.27 4.63 6.99 9.35 11.69 14.05 16.39 18.74 21.09];
hop2=[0 2.27 3.67 4.37 4.92 5.44 5.94 6.42 6.90 7.38];
plot(x,hop1,'-*r');
grid on;
hold on;
plot(x,hop2,'-ob');
xlabel('L(group unit)');
ylabel('Average Hop Number');
legend('system without hierarchical structure','system with hierarchical structure','location','northwest');
