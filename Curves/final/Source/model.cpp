#ifndef HEADER_EH
#define HEADER_EH
#include "exh.h"
#endif

long double model::factorial(int x){
	long double fact=1;
	int p=1;
	if(x==0 || x==1)
		return 1;
	else{
		while(p<=x){
			fact*=p;
			p++;}
		}
	return fact;
}
long double model::binomial( int f, int n){
    model cm;
	double com=cm.factorial(n)/(cm.factorial(f)*cm.factorial(n-f));
	return com;
}

//polynomial interpretation for N points
float model::interpolation ( POINT *control_p, float x, int N )
{
  float y;

  float x_n = 1.0, x_d = 1.0;
  float sum = 0.0;

  for(int i=0;i<N;++i) {
    x_n = x_d = 1.0;
    for(int j=0;j<N;++j) {
      if(j == i) continue;
      x_n = x_n * ( x-control_p[j].x );		 	//x - x2
    }
    for ( int j = 0; j < N; ++j ) {
      if ( j == i ) continue;
      x_d = x_d * ( control_p[i].x - control_p[j].x );	//x1 - x2
    }
    sum += x_n / x_d * control_p[i].y;
  }
  y = sum;

  return y;
}

POINT model::bernstein(POINT *control_p,float t,int n)
{
    model cm;
    POINT N;N.x=N.y=0;//n=nr de puncte
    for(i=0;i<=n;i++)
    {
        N.x+=control_p[i].x*cm.binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
        N.y+=control_p[i].y*cm.binomial(i,n)*pow(t,i)*pow((1-t),(n-i));
    }
	return N;
}
