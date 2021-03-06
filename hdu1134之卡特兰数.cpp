#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
#include<map>
#include<iomanip>
#define INF 99999999
using namespace std;
const int MAX=1000;
int sum[101][MAX];
void mult(int *A,int *B,int b,int m){//卡特兰数:h(n)=h(n-1)*(4n-2)/(n+1)或h(n)=h(0)*h(n-1)+h(1)*h(n-2)+....+h(n-1)*h(0)或h(n)=c(2n,n). 
	int p=0,seg=4,c=0;
	const int Base=10000;
	for(int i=1;i<=A[0];++i){//先算h(n-1)*(4n-2).
		B[i]=A[i]*b+p;
		if(B[i]>=Base){
			p=B[i]/Base;
			B[i]=B[i]%Base;
		}else p=0;
	}
	B[0]=A[0];
	if(p){B[A[0]+1]=p;B[0]++;}
	for(int i=B[0];i>=1;--i){//求h(n)=h(n-1)*(4n-2)/(n+1). 
		B[i]+=c;
		c=(B[i]%m)*Base;
		B[i]=B[i]/m;
	}
	while(!B[B[0]])B[0]--;
}
int main(){
	int num;
	sum[0][0]=sum[0][1]=sum[1][0]=sum[1][1]=1;
	for(int i=2;i<=100;++i){
		num=4*i-2;
		mult(sum[i-1],sum[i],num,i+1);
	}
	while(cin>>num,num!=-1){
		cout<<sum[num][sum[num][0]];
		for(int i=sum[num][0]-1;i>=1;--i){
				cout<<setfill('0')<<setw(4)<<sum[num][i];
		}
		cout<<endl;
	}
	return 0;
}