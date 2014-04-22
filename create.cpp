#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<cmath>
#include<algorithm>
#include<set>
#include<limits.h>
#include<queue>
using namespace std;

#define MAXN 100

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}
int main()
{
	int i,j;
	srand(time(NULL));
	double xoff,yoff,genx,geny;	
	xoff=0.7;
	yoff=0.7;
	for (i=1;i<=10;i++){
		for (j=1;j<=10;j++){
			genx=fRand(xoff*(i-1),xoff*i);
			geny=fRand(yoff*(j-1),yoff*j);
			cout << genx << " " << geny << endl;
		}
	}	
	return 0;
}
