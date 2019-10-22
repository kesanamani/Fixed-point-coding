#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <c6x.h>
const int q=6;
double cos_val[64] = {1.000000,-1.000000,-0.500000,0.000000,0.309017,0.500000,0.623490,0.707107,0.766044,0.809017,0.841254,0.866025,0.885456,0.900969,0.913545,0.923880,0.932472,0.939693,0.945817,0.951057,0.955573,0.959493,0.962917,0.965926,0.968583,0.970942,0.973045,0.974928,0.976621,0.978148,0.979530,0.980785,0.981929,0.982973,0.983930,0.984808,0.985616,0.986361,0.987050,0.987688,0.988280,0.988831,0.989343,0.989821,0.990268,0.990686,0.991077,0.991445,0.991790,0.992115,0.992421,0.992709,0.992981,0.993238,0.993482,0.993712,0.993931,0.994138,0.994335,0.994522,0.994700,0.994869,0.995031,0.995185};
double sin_val[64] = {0.000000,0.000000,0.866025,1.000000,0.951057,0.866025,0.781831,0.707107,0.642788,0.587785,0.540641,0.500000,0.464723,0.433884,0.406737,0.382683,0.361242,0.342020,0.324699,0.309017,0.294755,0.281733,0.269797,0.258819,0.248690,0.239316,0.230616,0.222521,0.214970,0.207912,0.201299,0.195090,0.189251,0.183750,0.178557,0.173648,0.169001,0.164595,0.160411,0.156434,0.152649,0.149042,0.145601,0.142315,0.139173,0.136167,0.133287,0.130526,0.127877,0.125333,0.122888,0.120537,0.118273,0.116093,0.113991,0.111964,0.110008,0.108119,0.106293,0.104528,0.102821,0.101168,0.099568,0.098017};
short int rounding(float x)
{
    if(x>=0)
{
    short int y;float z;
    y=(short int)x;
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
    short int y;float z;
    y=(short int)x;
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
struct cmplx
{
    short int real;
    short int img;
};
struct cmplx_d
{
    double real;
    double img;
};
struct cmplx add(struct cmplx a,struct cmplx b)
{
    struct cmplx temp;
    temp.real =_add2(a.real,b.real);
    temp.img =_add2(a.img,b.img);
    return temp;
}
struct cmplx subt(struct cmplx a,struct cmplx b)
{
    struct cmplx temp;
    temp.real =_addsub(a.real,b.real);
    temp.img =_addsub(a.img,b.img);
    return temp;
}
struct cmplx mult(struct cmplx a,struct cmplx b)
{
    struct cmplx temp;
    temp.real =_addsub(((a.real *b.real)/(1<<q)),((a.img *b.img)/(1<<q)));
    temp.img =_add2(((a.real *b.img)/(1<<q)),((a.img *b.real)/(1<<q)));
    return temp;
}

// struct cmplx pow_z( short int n)
// {
//     struct cmplx temp;
//     temp.real =cos(2*pi/n);
//     temp.img = sin(2*pi/n);
//     return temp;
// }
struct cmplx *fft(struct cmplx *x,short int n)
{
    if(n==1) return x;
    struct cmplx w;
    struct cmplx w_n;
    w_n.real =cos_val[n-1]*(1<<q);
    w_n.img = -sin_val[n-1]*(1<<q);
    w.real=(1<<q);
    w.img =0;
    struct cmplx *x_even;
    struct cmplx *x_odd;
    struct cmplx *y_even;
    struct cmplx *y_odd;
    struct cmplx *y;
    x_even = (struct cmplx *)malloc(n/2 * sizeof(struct cmplx));
    x_odd = (struct cmplx *)malloc(n/2 * sizeof(struct cmplx));
    y = (struct cmplx *)malloc(n * sizeof(struct cmplx));
    for(int i = 0 ; i < n/2 ; i++)
    {
        x_even[i] = x[2*i];
        x_odd[i] = x[2*i + 1];
    }
    y_even =fft(x_even,n/2);
    y_odd =fft(x_odd,n/2);
    for (int k = 0; k < n/2; k++)
    {
        //printf("%d       %d\n",w.real,w.img );
        y[k]=add(y_even[k],mult(w,y_odd[k]));
        //printf("%d       %d\n",y[k].real,y[k].img );

        y[k+(n/2)]=subt(y_even[k],mult(w,y_odd[k]));
        w=mult(w,w_n);

    }
    return y;


}

int main()
{
    double x_r[] ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};   //input real values(can be size of 2^n <=64)
    double x_im[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};      // input imaginary values(can be size of 2^n <=64)
    int n=sizeof(x_r)/sizeof(double);
    //printf("%d\n",n );
    struct cmplx * x;
    struct cmplx_d *x_d;
    x = (struct cmplx *)malloc(n * sizeof(struct cmplx));
    x_d = (struct cmplx_d *)malloc(n * sizeof(struct cmplx_d));
    for(int i=0;i<n;i++)
    {
        x[i].real = rounding(x_r[i]*(1<<q));
        //printf("%d\n",x[i].real );
        x[i].img =rounding(x_im[i] * (1<<q));
    }
    x=fft(x,n);
    for(int i=0;i<n;i++)
    {
        x_d[i].real=(double)x[i].real;
        x_d[i].real=x_d[i].real/(1<<q);
        x_d[i].img=(double)x[i].img;
        x_d[i].img=x_d[i].img/(1<<q);

        printf("%lf %lf\n",x_d[i].real,x_d[i].img);
    }

    return 0;
}