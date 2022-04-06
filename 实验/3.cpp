//句子相似度：忽略标点符号，以单词为单位，两个句子的相似度计为最长公共子串（可不连续）的长度/较短字符串的长度。 
//段落相似度：对段落1，取每个句子在段落2的每个句子中的最长公共子串的长度最大值并求和，再除以段落1的长度。对段落2同理，取较大值。
//文章相似度：类比段落相似度。
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int N=1e3;
char inp[50],c;
double rate;
int len1,len2,words_cnt1,words_cnt2;
int i,j,dp[N+1][N+1];
string word;

struct node{
	string words[N];
}s1[N],s2[N];

bool cmp(string t1,string t2){
	if (!t1.length() || !t2.length()) return false;
	if (t1.length()!=t2.length()) return false;
	for (int k=0;k<t1.length();k++)	
		if (!(t1[k]==t2[k] || t1[k]-t2[k]==32 || t1[k]-t2[k]==-32)) return false;
	cout << t1 << " <--> " << t2 << endl;
	return true;
}

int main(){
	printf("Compare two sentences(s),paragraphs(p) or articles(a)? ");
	scanf("%s",inp);
	if (inp[0]=='s'){    //s1[0]: sentence1  s2[0]: sentence2
		//input
		freopen("3-s1.txt","r",stdin);
		word=""; len1=0; words_cnt1=0; printf("s1: ");
		while (scanf("%c",&c)!=EOF){
			printf("%c",c); len1++; 
			if (c!=',' && c!='.' && c!='!' && c!='?' && c!=' ' && c!='\'' && c!='\n'){
				word+=c;
			}
			else{
				s1[0].words[words_cnt1++]=word;
				word="";
			}
		}
		printf("\n");
		
		freopen("3-s2.txt","r",stdin);
		word=""; len2=0; words_cnt2=0; printf("s2: ");
		while (scanf("%c",&c)!=EOF){
			printf("%c",c); len2++; 
			if (c!=',' && c!='.' && c!='!' && c!='?' && c!=' ' && c!='\'' && c!='\n'){
				word+=c;
			}
			else{
				s2[0].words[words_cnt2++]=word;
				word="";
			}
		}
		printf("\n");
		
		//solve
		for (i=0;i<N;i++) dp[i][0]=dp[0][i]=0;
		for (i=0;i<words_cnt1;i++)
			for (j=0;j<words_cnt2;j++){
				if (cmp(s1[0].words[i],s2[0].words[j]))
					dp[i+1][j+1]=dp[i][j]+s1[0].words[i].length();
				else
					dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
			}
		rate=dp[words_cnt1][words_cnt2]*1.0/min(len1,len2);
		printf("len1=%d, len2=%d\n",len1,len2);
		printf("Overlapping length: %d\n",dp[words_cnt1][words_cnt2]);
		printf("Overlapping rate: %.2f%\n",rate*100.0);
	}
	else if (inp[0]=='p'){
		//input
		int sen_cnt1,sen_cnt2,wc1[N],wc2[N];
		freopen("3-p1.txt","r",stdin);
		word=""; len1=0; words_cnt1=0; sen_cnt1=0; printf("s1: ");
		while (scanf("%c",&c)!=EOF){
			printf("%c",c); len1++; 
			if (c!=',' && c!='.' && c!='!' && c!='?' && c!=' ' && c!='\''){
				word+=c;
			}
			else if (c==',' || c=='\'' || c==' '){
				s1[sen_cnt1].words[words_cnt1++]=word;
				word="";
			}
			else{
				wc1[sen_cnt1++]=words_cnt1;
				words_cnt1=0;
			}
		}
		printf("\n");
		
		freopen("3-p2.txt","r",stdin);
		word=""; len2=0; words_cnt2=0; sen_cnt2=0; printf("s2: ");
		while (scanf("%c",&c)!=EOF){
			printf("%c",c); len2++; 
			if (c!=',' && c!='.' && c!='!' && c!='?' && c!=' ' && c!='\'' && c!='\n'){
				word+=c;
			}
			else if (c==',' || c=='\'' || c==' '){
				s2[sen_cnt2].words[words_cnt2++]=word;
				word="";
			}
			else{
				wc2[sen_cnt2++]=words_cnt2;
				words_cnt2=0;
			}
		}
		printf("\n");
		
		//solve
		double rate1,rate2;
		int sum=0,tmpmaxv=0;
		for (int p=0;p<sen_cnt1;p++){
			words_cnt1=wc1[p]; tmpmaxv=0;
			for (int q=0;q<sen_cnt2;q++){
				words_cnt2=wc2[q];
				for (i=0;i<N;i++) dp[i][0]=dp[0][i]=0;
				for (i=0;i<words_cnt1;i++)
					for (j=0;j<words_cnt2;j++){
						if (cmp(s1[p].words[i],s2[q].words[j]))
							dp[i+1][j+1]=dp[i][j]+s1[p].words[i].length();
						else
							dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
					}
				if (dp[words_cnt1][words_cnt2]>tmpmaxv)
					tmpmaxv=dp[words_cnt1][words_cnt2];
			}
			sum+=tmpmaxv;
		}
		rate1=sum*1.0/len1;
		printf("len1=%d, len2=%d\n",len1,len2);
		printf("Overlapping length1: %d\n",sum);
		
		sum=0;
		for (int p=0;p<sen_cnt2;p++){
			words_cnt1=wc2[p]; tmpmaxv=0;
			for (int q=0;q<sen_cnt1;q++){
				words_cnt2=wc2[q];
				for (i=0;i<N;i++) dp[i][0]=dp[0][i]=0;
				for (i=0;i<words_cnt1;i++)
					for (j=0;j<words_cnt2;j++){
						if (cmp(s2[p].words[i],s1[q].words[j]))
							dp[i+1][j+1]=dp[i][j]+s2[p].words[i].length();
						else
							dp[i+1][j+1]=max(dp[i][j+1],dp[i+1][j]);
					}
				if (dp[words_cnt1][words_cnt2]>tmpmaxv)
					tmpmaxv=dp[words_cnt1][words_cnt2];
			}
			sum+=tmpmaxv;
		}
		rate2=sum*1.0/len2;
		printf("Overlapping length2: %d\n",sum);
		rate=max(rate1,rate2);
		printf("Overlapping rate: %.2f%\n",rate*100.0);
	}
	else{
		printf("Service not available\n");
	}
	return 0;
} 
