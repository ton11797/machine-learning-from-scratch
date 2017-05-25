#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
class DATA{
private:
	double **x;
	double *y;
	double *o;
	int train,feature;
	double cost;
	double learn;
	int iteration;
public:
	DATA(double l,int m,int n);
	void loaddata(char **);
	void showdata();
	double hypothesis(double *);
	double cost_function();
	bool gradient_descent();
	void run();
	void printo();
};
void DATA::printo(){
	for (int i = 0; i < feature; ++i)
	{
		cout<<" O["<<i<<"]= "<<o[i];
	}
	cout<<endl;
}
void DATA::run(){
	while(gradient_descent());
}
bool DATA::gradient_descent(){
	double sum=0;
	double *tmpo = new double[feature];
	for (int i = 0; i < feature; ++i)
	{
		sum=0;
		for (int j = 0; j < train; ++j)
		{
			sum+=(hypothesis(x[j])-y[j])*x[j][i];
		}
		tmpo[i]=(sum*learn)/train;
	}
	for (int i = 0; i < feature; ++i)
	{
		o[i]=o[i]-tmpo[i];
	}
	iteration++;
	double tmpcost=cost_function();
	if(tmpcost==cost)return 0;else cost= tmpcost;
	return 1;
}
double DATA::cost_function(){
	double sum=0;
	for (int i = 0; i < train; ++i)
	{
		sum+=pow(hypothesis(x[i])-y[i],2);
	}
	return sum/(train*2);
}
double DATA::hypothesis(double *xin){
	double hy=0;
	for (int i = 0; i < feature; ++i)
	{
		hy+=xin[i]*o[i];
	}
	return hy;
}
void DATA::showdata(){
	for (int i = 0; i < train; ++i)
	{
		for (int j = 0; j < feature; ++j)
		{
			cout<<"X"<<j<<" ="<<x[i][j]<<" ";
		}
		cout<<"|Y= "<<y[i]<<endl;;
	}
}
void DATA::loaddata(char *argv[]){
	argv++;
	int ar=0;
	for (int i = 0; i < train; ++i,ar++)
	{
		x[i][0]=1;
		for (int j = 1; j < feature; ++j,ar++)
		{
			x[i][j]=atoi(argv[ar]);
			cout<<atoi(argv[ar]);
		}
		cout<<"|"<<atoi(argv[ar])<<endl;
		y[i]=atoi(argv[ar]);
	}
}
DATA::DATA(double l,int m,int n){
	learn = l;
	train = m;
	feature = n;
	iteration = 0;
	o = new double[feature];
	for(int i=0;i<feature;i++)o[i]=1;
	y = new double[train];
	x = new double*[train];
	for(int i = 0; i < train; ++i)x[i] = new double[feature];
}
int main(int argc, char *argv[])
{
	int m,n;
	float rate;
	cout<<"Input learning rate: ";
	cin>>rate;
	cout<<"How many feature: ";
	cin>>n;
	cout<<"How many training set: ";
	cin>>m;
	DATA dataset(rate,m,n+1);
	dataset.loaddata(argv);
	cout<<"cost ="<<dataset.cost_function()<<endl;
	dataset.run();
	dataset.showdata();
	cout<<"cost ="<<dataset.cost_function()<<endl;
	dataset.printo();
	return 0;
}