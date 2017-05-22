#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
class DATA{
private:
	double x[50];
	double y[50];
	int num;
	double a,b;
	double cost;
	double learn;
public:
	DATA(double l){num=0;a=0;b=0;learn=l;}
	void adddata(double x,double y);
	double hypothesis(double y);
	void cout_function();
	void gradient_descent();
	void report();
	double get_cost(){return cost;}
};
void DATA::report(){
	cout<<"A="<<a<<" B="<<b<<" cost="<<cost<<endl;
}
void DATA::gradient_descent(){
	double temp1,temp2,summation=0;
	for (int i = 0; i < num; ++i)
	{
		summation += hypothesis(x[i]) - y[i];
	}
	temp1 = (summation*learn)/num;
	for (int i = 0; i < num; ++i)
	{
		summation += (hypothesis(x[i]) - y[i])*x[i];
	}
	temp2 = (summation*learn)/num;
	a=a-temp1;
	b=b-temp2;
	//cout<<"Ga="<<temp1<<" Gb="<<temp2;
}
void DATA::cout_function(){
	double summation=0;
	for (int i = 0; i < num; ++i)
	{
		summation += pow((hypothesis(x[i]) - y[i]),2);
	}
	cost = summation/(num*2);
}
double DATA::hypothesis(double x){
	return a+(b*x);
}
void DATA::adddata(double ax,double ay){
	x[num]=ax;
	y[num]=ay;
	num++;
}
int main(int argc, char const *argv[])
{
	double t,x,y;
	int step=0;
	double cost=0;
	float rate;
	cout<<"Input learning rate: ";
	cin>>rate;
	DATA dataset(rate);
	for (int i = 1; i < argc; i+=2)
	{
		dataset.adddata(atoi(argv[i]),atoi(argv[i+1]));
	}
	while(1){
		dataset.cout_function();
		dataset.gradient_descent();
		dataset.report();
		step++;
		if(cost == dataset.get_cost())break;
		cost = dataset.get_cost();
	}
	cout<<"step ="<<step;
	return 0;
}