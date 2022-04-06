#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N=1e3;
const int MOD=1e9+7;
const int mod=80;
int i,j,s,buf,code,Hash[90];
char str[20],inp[20];
struct person{
	char name[20];
	int age;
	char mail[30];
	char phone[12];
	char sex;
	int key;
}p[N];

int main(){
	printf("Input the name: ");
	scanf("%s",inp);
	freopen("name.txt","r",stdin);
	for (i=0;i<80;i++){
		scanf("%s",p[i].name); p[i].key=0;
		for (j=0;j<strlen(p[i].name);j++)
			if (p[i].name[j]>='A' && p[i].name[j]<='Z')
				p[i].key=(p[i].key*5+(p[i].name[j]-'A'+1))%MOD;
			else if (p[i].name[j]>='a' && p[i].name[j]<='z')
				p[i].key=(p[i].key*5+(p[i].name[j]-'a'+1))%MOD;
			else //p[i].name[j]='-'
				p[i].key=(p[i].key*10)%MOD;
	}
	freopen("age.txt","r",stdin);
	for (i=0;i<80;i++) scanf("%d",&p[i].age);
	freopen("mail.txt","r",stdin);
	for (i=0;i<80;i++) scanf("%s",p[i].mail);
	freopen("phone.txt","r",stdin);
	for (i=0;i<80;i++) scanf("%s",p[i].phone);
	freopen("sex.txt","r",stdin);
	for (i=0;i<80;i++) scanf("%c\n",&p[i].sex);
	
	buf=80;
	for (i=0;i<90;i++) Hash[i]=-1;
	for (i=0;i<80;i++){
		s=(p[i].key+strlen(p[i].name))%mod;
		if (Hash[s]==-1) Hash[s]=i;
		else{
			s=(s+1)%90;
			while (Hash[s]!=-1) s=(s+1)%90;
			Hash[s]=i;
		}
	}
	for (i=0;i<90;i++)
		printf("Hash[%d]: %s\n",i,p[Hash[i]].name);
		
	freopen("name.txt","r",stdin);
	int sum=0,tmp=0;
	for (i=0;i<80;i++){
		scanf("%s",str); code=0; tmp=0;
		for (j=0;j<strlen(str);j++)
			if (str[j]>='A' && str[j]<='Z')
				code=(code*5+(str[j]-'A'+1))%MOD;
			else if (str[j]>='a' && str[j]<='z')
				code=(code*5+(str[j]-'a'+1))%MOD;
			else //str[j]='-'
				code=(code*10)%MOD;
		code=(code+strlen(str))%mod; tmp++;
		if (Hash[code]!=-1){
			if (!strcmp(p[Hash[code]].name,str)) printf("%dst name found in Hash[%d] after searching %d times.\n",i,code,tmp);
			else{
				code=(code+1)%90; tmp++;
				while (strcmp(p[Hash[code]].name,str)!=0) {code=(code+1)%90; tmp++;}
				printf("%dst name found in Hash[%d] after searching %d times.\n",i,j,tmp);
			}
		}
		else{
			printf("Error!\n"); return 0;
		}
		sum+=tmp;
	}
	printf("The average search time is %.3f\n",sum*1.0/80);
	code=0; tmp=0;
	for (j=0;j<strlen(inp);j++){
		if (inp[j]>='A' && inp[j]<='Z')
			code=(code*5+(inp[j]-'A'+1))%MOD;
		else if (inp[j]>='a' && inp[j]<='z')
			code=(code*5+(inp[j]-'a'+1))%MOD;
		else //inp[j]='-'
			code=(code*10)%MOD;
	}
	code=(code+strlen(inp))%mod; tmp++;
	if (Hash[code]!=-1){
		if (!strcmp(p[Hash[code]].name,inp)){
			j=code;
			printf("The input name found in Hash[%d] after searching %d times.\n",code,tmp);
		}
		else{
			code=(code+1)%90; tmp++;
			while (strcmp(p[Hash[code]].name,inp)!=0 && tmp<90) {code=(code+1)%90; tmp++;}
			if (tmp==90){
				printf("Not found!\n"); return 0;
			}
			j=code;
			printf("The input name found in Hash[%d] after searching %d times.\n",j,tmp);
		}
		printf("Detailed information: %s %d %s %s %c\n",p[Hash[j]].name,p[Hash[j]].age,p[Hash[j]].mail,p[Hash[j]].phone,p[Hash[j]].sex);
	}
	else printf("Not found!\n");
	return 0;
}
