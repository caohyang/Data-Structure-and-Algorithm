#include <cstdio>
#include <iostream>
using namespace std;

int n,m,i,a[1005];

int main(){
	scanf("%d%d",&n,&m); //m:15 or 20
	a[1]=a[2]=1;
	for (i=3;i<=n+1;i++)
		a[i]=a[i-1]+a[i-2];
	a[n+2]=a[n+1]+a[n]-a[2];
	for (i=n+3;i<=m;i++)
		a[i]=a[i-1]+a[i-2]-a[i-n-2];
	//for (i=1;i<=m;i++)
	//	printf("%d ",a[i]);
	printf("%d\n",a[m]);
	return 0;
}
//O(m)
