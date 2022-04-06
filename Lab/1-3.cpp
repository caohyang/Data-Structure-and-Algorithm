#include <cstdio>
#include <iostream>
using namespace std;

int n,m,i,j,k,p,sum=1;
int a[100005]; //a[i]: number of birth in month i
//birth T -- death T+k+m*(p-1)
//Assume that a pair of rabbits need k months to mature and give their first birth,\
  after which they give birth every m months. They die after p generations.

int main(){
	scanf("%d%d%d%d",&k,&m,&p,&n);
	if (n<=2) {printf("1\n"); return 0;}
	a[1]=1; a[2]=0;
	for (i=3;i<=n;i++){
		j=i-k;
		while (j>0){
			a[i]+=a[j];
			sum+=a[j];
			j-=m;
		}
		//j+k+m*(p-1)==i
		j=i-(k+m*(p-1));
		if (j>=1){
			sum-=a[j];
			a[j]=0;
		}
	}
	printf("%d\n",sum);
	return 0;
}
//O(n^2/k)
