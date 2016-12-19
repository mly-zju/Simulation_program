clc;
i=0;
j=0;
count=0;
sum1=0;
sum2=0;
for i=1:5
    for j=1:5
        count=count+1;
        sum1=sum1+5-i+j;
        if (i==5&&(j==1||j==2))||(i==4&&j==1)
            sum2=sum2+5-i+j;
        else
            sum2=sum2+abs(i-3)+1+abs(j-3);
        end
    end
end
for i=1:5
    for j=1:5
        if(i~=j)
            count=count+2;
            sum1=sum1+2*abs(i-j);
            sum2=sum2+2*abs(i-j);
        end
    end
end
sum1/count
sum2/count
sum2/sum1