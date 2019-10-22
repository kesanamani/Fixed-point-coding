#include <stdio.h>
#include <math.h>
int rounding(long double x)
{
	if(x>0)
	{
		long int y;long double z;
		y=(long int)x;
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
		int y;long double z;
		y=(long int)x;
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
	long double a[]={-8.31662009587695e-13, 0.634029328751641, -0.767445067471676,
				1.21423064425930 ,-0.398089786809545 ,0.577773754381422 ,0.836673932101677,
				-0.308971047587158 ,1.58778525229245, -0.182021563971272,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	long double b[]={0.256258710000824 ,-0.299311523023751 ,1.18013824251201 ,-0.724526570403471,
				0.963365491184473 ,0.0611683879836982 ,-0.126424722362053,
				1.08772832230303 ,-0.743741290000000, 1.08772832230147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int a_size= 10;
	int b_size= 10;
	int q_1,q_2;
	printf("enter Qformat (a,b)");
	scanf("%d %d",&q_1,&q_2);
	int a_fp[1000]={0},b_fp[1000]={0};
	long double a_temp[a_size];
	for(int i=0;i<a_size;i++)
	{
		a_temp[i]=a[i]*(1<<q_2);
		a_fp[i]=rounding(a_temp[i]);
	}
	long double b_temp[b_size];
	for(int i=0;i<b_size;i++)
	{
		b_temp[i]=b[i]*(1<<q_2);
		b_fp[i]=rounding(b_temp[i]);
	}
	long int cor_fp[100]={0};
	for(int k=-10;k<=10;k++)
	{
		cor_fp[10+k]=0;
		for(int m=0;m<=9;m++)
		{
			cor_fp[10+k]=cor_fp[k]+(a_fp[m] *b_fp[m-k]);
		}
	}
	long double cor_fl[100]={0};
	for(int k=-10;k<=10;k++)
	{
		cor_fl[10+k]=0;
		for(int m=0;m<=9;m++)
		{
			cor_fl[10+k]=cor_fl[k]+(a[m] *b[m-k]);
		}
	}

	long double cor[21];
	printf("correlation with fp  direct correlation   error \n");
	for (int i = 0; i <=20; i++)
	{
		cor[i]=(long double)cor_fp[i];
		cor[i]=cor[i]/(1<<(q_2+q_2));
		printf("%Lf \t\t %Lf \t %Lf\n",cor[i],cor_fl[i],cor[i]-cor_fl[i]);
	}
}
