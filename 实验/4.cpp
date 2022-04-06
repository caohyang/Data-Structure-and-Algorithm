#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

struct node{
	char c;
	char s[20]; //code
	int wgt;
	int parent;
	int left;
	int right;
}p[300]; //0-127: ascii  150-277: new nodes 

const int N=1e6;
int i,j,cur,l,huff_l;
double ratio;
char ch,str[N],str01[N];

void SelectMinVal(node p[],int count,int &ix,int &iy){
	int flag=-1;
	for (i=0;i<count;i++){
		if (!p[i].wgt) continue;
		if (p[i].parent==-1 && flag==-1) {flag=0; ix=i;}
		else 
			if (p[i].parent==-1 && p[i].wgt<p[ix].wgt) ix=i;
	}
	flag=-1;
	for (i=0;i<count;i++){
		if (i==ix || !p[i].wgt) continue;
		if (p[i].parent==-1 && flag==-1) {flag=0; iy=i;}
		else 
			if (p[i].parent==-1 && p[i].wgt<p[iy].wgt) iy=i;
	}
}

void GenSubTree(node p[],int &count,int ix,int iy){
	p[count].wgt=p[ix].wgt+p[iy].wgt;
	p[count].left=ix; p[count].right=iy;
	p[ix].parent=p[iy].parent=count;
	count++;
}

void HuffmanTree(node p[],int n){
	int ix,iy,count=150;
	while (n>1){
		SelectMinVal(p,count,ix,iy);	
		GenSubTree(p,count,ix,iy);
		n--;
	}
}

int main(){
	printf("Input the 01 code: "); scanf("%s",str01); 
	freopen("4-2.txt","r",stdin);
	//preprocessing
	for (i=0;i<128;i++){
		p[i].c=char(i);
		p[i].parent=p[i].left=p[i].right=-1;
	}
	for (i=128;i<300;i++) p[i].parent=p[i].left=p[i].right=-1;
	
	//input & buildtree
	while (scanf("%c",&ch)!=EOF){
		str[l++]=ch;
		for (i=0;i<128;i++)
			if (p[i].c==ch) {p[i].wgt++; break;}
	}
	int tot=0;
	for (i=0;i<128;i++)
		if (p[i].wgt) tot++;
	HuffmanTree(p,tot);
	
	//produce the codes
	for (i=0;i<128;i++){
		if (!p[i].wgt) continue;
		string tmp=""; cur=i;
		while (p[cur].parent!=-1){
			if (p[p[cur].parent].left==cur) tmp='0'+tmp;
			else tmp='1'+tmp;
			cur=p[cur].parent;
		}
		for (j=0;j<tmp.length();j++)
			p[i].s[j]=tmp[j];
	}
	for (i=0;i<128;i++)  //print the codes
		if (p[i].wgt) printf("%c: %s\n",p[i].c,p[i].s);

	//calculate huff_l & ratio
	for (i=0;i<l;i++)
		for (j=0;j<128;j++)
			if (str[i]==p[j].c) {huff_l+=strlen(p[j].s); break;}
	ratio=huff_l*1.0/(8*l);
	printf("The compression ratio is: %.2f%\n",ratio*100);
	
	//decode
	printf("The decoded string is: ");
	i=0; int cur0=299;
	while (p[cur0].left==-1  && p[cur0].right==-1) cur0--;
	cur=cur0; 
	while (str01[i]=='0' || str01[i]=='1'){
		if (p[cur].left==-1 && p[cur].right==-1){
			printf("%c",p[cur].c);
			cur=cur0;
		}
		if (str01[i]=='0') cur=p[cur].left;
		else cur=p[cur].right;
		i++;
	}
	if (p[cur].left==-1 && p[cur].right==-1) printf("%c",p[cur].c);
	return 0;
}
