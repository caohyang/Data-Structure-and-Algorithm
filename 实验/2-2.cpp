#include <ctime>
#include <queue>
#include <cstdio>
#include <random>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int N=1e5,M=1e3;
float aver;
int i,Service_Num,Clients_Num,tim,min_ind;
int Poisson_Data[N],Arrival_Time[N],Service_Time[N],Wait_Time[N];
struct QUEUE{
	int c[M],id[M];
	int front,rear;	
}q[M];

int len(QUEUE Q) {return Q.rear-Q.front;}
void push(QUEUE &Q,int ind,int x){
	Q.c[Q.rear]=x; 
	Q.id[Q.rear]=ind; 
	Q.rear++;
}
bool check(){
	for (int j=0;j<Service_Num;j++)
		if (len(q[j])) return false;
	return true;
}
void pop(QUEUE &Q,int curtim){
	int ind=Q.id[Q.front];
	Wait_Time[ind]=curtim-Service_Time[ind]-Arrival_Time[ind];
	Q.front++;
}

int main(){
	int tmps=0,cnt=0;
	srand((int)time(NULL));
	printf("Input Service_Num and Clients_Num:\n");
	scanf("%d%d",&Service_Num,&Clients_Num);
	for (i=0;i<Service_Num;i++) q[i].front=q[i].rear=0;
	
	printf("Input the average of poisson_distribution:\n");
	scanf("%f",&aver);
	std::random_device id;
	std::default_random_engine time(id());
	std::poisson_distribution<int>Generator(aver);
	for (i=0;i<Clients_Num;i++){
		Poisson_Data[i]=Generator(time); //Arrival_Time
		tmps+=Poisson_Data[i];
	}
	sort(Poisson_Data,Poisson_Data+Clients_Num);
	for (i=0;i<Clients_Num;i++) {printf("%2d ",Poisson_Data[i]); if (i%10==9) printf("\n");}
	printf("\nThe average arrival time: %.2f\n\n",tmps*1.0/Clients_Num);
	
	tim=Poisson_Data[0];
	do{
		while (Poisson_Data[cnt]==tim && cnt<Clients_Num){
			Arrival_Time[cnt]=tim; Service_Time[cnt]=rand()%6+5;
			printf("No.%3d   Arrival_Time: %3d   Service_Time: %2d\n",cnt,tim,Service_Time[cnt]);
			min_ind=0;
			for (i=1;i<Service_Num;i++)		
				if (len(q[i])<len(q[min_ind])) min_ind=i;
			push(q[min_ind],cnt,Service_Time[cnt]);
			cnt++;
		}
		for (i=0;i<Service_Num;i++)
			if (len(q[i])){
				q[i].c[q[i].front]--;
				if (q[i].c[q[i].front]==-1){
					pop(q[i],tim); q[i].c[q[i].front]--;
				}
			}
		tim++;
	}while (!check());
	
	printf("\n");
	float Sum_Time=0;
	for (i=0;i<Clients_Num;i++){
		printf("No.%3d   Wait_Time: %3d\n",i,Wait_Time[i]);
		Sum_Time+=Wait_Time[i];
	}
	printf("Average wait time: %.2f\n",Sum_Time*1.0/Clients_Num);
	return 0;
}
