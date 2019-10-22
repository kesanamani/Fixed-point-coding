#include<stdio.h>
int rounding(float x)
{
	if(x>0)
{
	int y;float z;
	y=(int)x;
	z=x-y;
	if(z<=0.5)
	{
		return y;
	}
	else
	{
		return y+1;
	}
}
else
{
	int y;float z;
	y=(int)x;
	z=x-y;
	if(z<=-0.5)
	{
		return y;
	}
	else
	{
		return y-1;
	}
}
}
int main()
{
	float a,b,a_temp,b_temp,c;
	int Q_1,Q_2,a_fp,b_fp,c_fp,d;
	printf("Enter two numbers: \n");
	scanf("%f %f",&a,&b);
	printf("Enter Q format \n");
	scanf("%d %d",&Q_1,&Q_2);
	a_temp=(a*(1<<(Q_2)));
	b_temp=(b*(1<<(Q_2)));
	a_fp=rounding(a_temp);
	b_fp=rounding(b_temp);
	printf("1.addition \n 2.subtraction \n");
	scanf("%d",&d);
	if(d==1)
	{
	c_fp=a_fp + b_fp;
	}
	if(d==2)
	{
	c_fp=a_fp - b_fp;
	}
	printf("%d \n",c_fp);
	c=(float)c_fp;
	printf("%f",c/(1<<(Q_2)));

}
