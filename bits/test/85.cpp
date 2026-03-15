#include<iostream>
#include<cstdio>
using namespace std;
double a,b,c,d,a1,b1,c1,d1;
int num;
int main()
{
	scanf("%lf%lf%lf%lf",&a,&b,&c,&d);
	for(double i=-100.00;i<=100.00;i+=0.001)
	{
		double l=i,r=i+0.001;
		if((a*l*l*l+b*l*l+c*l+d)*(a*r*r*r+b*r*r+c*r+d)<0)
		printf("%.2f ",l),num++;
		if(num==3) break;
	}
	return 0;
}
