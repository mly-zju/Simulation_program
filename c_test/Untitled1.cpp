#include <iostream>
using namespace std;

class Base1{
	public:
};

class Base2{
	public:
		Base2();
};


Base2::Base2(){
	cout<<"Base2"<<endl;
}

class SubBase:public Base1, public Base2{
	public:
		SubBase();
};

SubBase::SubBase(){
	cout<<"subBase"<<endl;
}

class Box{
	public:
		int width;
		int height;
		Box operator+(const Box& b){
			Box box;
			box.width=this->width+b.width;
			box.height=this->height+b.height;
			return box;
		}
};

int main(){
	SubBase test;
	Box a,b;
	a.width=1;
	a.height=1;
	b.width=1;
	b.height=1;
	Box c;
	c=a+b;
	cout<<c.width<<" "<<c.height<<endl;
	return 0;
}
