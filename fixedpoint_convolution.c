#include <stdio.h>
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
void p_arr(long int a[],int size)
{
	for(int i=0;i<size;i++)
	{
		printf("%ld \n",a[i]);
	}
	printf("\n");
}
int main()
{
	int q_1,q_2;
	long double a[]={0.256258710002038 ,0.963365491187825 ,-0.743741290000000 ,0.963365491190122,
				0.256258709998790, -0.450848071183266, 1.25625871000000 ,-0.450848071189536,
				0.256258710000382, 0.963365491183852 ,-0.743741290000000, 0.963365491188951,
				0.256258710000446 ,-0.450848071184437 ,1.25625871000000 ,-0.450848071188365,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	long double b[]={ 0.256258710000824 ,-0.299311523023751 ,1.18013824251201 ,-0.724526570403471,
				0.963365491184473, 0.0611683879836982, -0.126424722362053, 1.08772832230303
				-0.743741290000000 ,1.08772832230147,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	

	int a_size=(sizeof(a)/sizeof(long double))-30;
	int b_size=(sizeof(b)/sizeof(long double))-30;
	printf("enter Qformat (a,b)");
	scanf("%d %d",&q_1,&q_2);
	long int a_fp[50]={0},b_fp[50]={0};
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
	long double con_fl[a_size+b_size-1];
	for(int i=0;i<a_size+b_size-1;i++)
	{
		long double temp3=0;
		for(int j=0;j<=i;j++)
		{
			
			temp3=temp3+(a[j]*b[i-j]);
			
			
		}
		con_fl[i]=temp3;
		//printf("%Lf \n",con_fl[i]);
		
	}

	long int con_fp[a_size+b_size-1];
	for(int i=0;i<a_size+b_size-1;i++)
	{
		long int temp2=0;
		for(int j=0;j<=i;j++)
		{
			temp2=temp2+(a_fp[j]*b_fp[i-j]);
		}
		con_fp[i]=temp2;
		
		
	}
	long double con[a_size+b_size-1];
	printf("convolution with fp  direct conv   error \n");
	for (int i = 0; i < a_size+b_size-1; i++)
	{
		con[i]=(long double)con_fp[i];
		con[i]=con[i]/(1<<(q_2+q_2));
		printf("%Lf \t\t %Lf \t %Lf\n",con[i],con_fl[i],con[i]-con_fl[i]);
	}
	
	

}

