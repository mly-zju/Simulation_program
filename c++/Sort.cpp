#include <iostream>

using namespace std;

//class Animal {
//	public:
//		Animal();
//		int getAge(){
//			cout<<"The age is "<<age<<endl;
//		}
//	protected:
//		int age;
//};
//
//Animal::Animal() {
//	age=18;
//};
//
//class Dog: public Animal {
//	public:
//		Dog():Animal(){
//			age=19;
//		};
//};
//
//int main(){
//	Animal test;
//	test.getAge();
//	Dog dog;
//	dog.getAge();
//	return 0;
//}

//int quickSort(int start, int end, int *que){
//	int record=que[start];
//	int i=start;
//	int j=end;
//	bool back=true;
//	if(start<end){
//		while(i<j){
//			if(back){
//				if(que[j]>=record)
//					j--;
//				else{
//					que[i]=que[j];
//					i++;
//					back=false;
//				}
//			}
//			else{
//				if(que[i]<record)
//					i++;
//				else{
//					que[j]=que[i];
//					j--;
//					back=true;
//				}
//			}
//		}
//		que[i]=record;
//		quickSort(start,i,que);
//		quickSort(i+1,end,que);
//	}
//	else{
//		return 1;
//	}
//}
void merge(int src[], int tmp[], int start, int middle, int end){
	int i=start;
	int j=middle+1;
	int k=start;
	while(i!=middle+1&&j!=end+1){
		if(src[i]<=src[j])
			tmp[k++]=src[i++];
		else
			tmp[k++]=src[j++];
	}
	while(i!=middle+1)
		tmp[k++]=src[i++];
	while(j!=end+1)
		tmp[k++]=src[j++];
	for(i=start;i<=end;i++){
		src[i]=tmp[i];
	}
}

void mergeSort(int src[], int tmp[], int start, int end){
	if(end>start){
		int m=start+(end-start)/2;
		mergeSort(src,tmp,start,m);
		mergeSort(src,tmp,m+1,end);
		merge(src,tmp,start,m,end);
	}
	else
		return ;
}

int main(){
	int q[10]={3,2,4,5,1,7,0,4,2,9};
	int tmp[10];
	int i=0;
	int j=9;
//	quickSort(i,j,q);
	mergeSort(q,tmp,0,9);
    for(i=0;i<10;i++){
    	cout<<q[i]<<" ";
    }
}
