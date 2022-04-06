#include <cstdio>
#include <iostream>
using namespace std;

int n,i,a[1005],b[1005]; //a: new-born b: mature

int main(){
	scanf("%d",&n); //n=15 or 20
	a[1]=0; b[1]=1;
	for (i=2;i<=n;i++){
		a[i]=a[i-1]+b[i-1];
		b[i]=a[i-1];
	}	
	printf("%d\n",a[n]+b[n]);
	return 0;
}
//O(n)
