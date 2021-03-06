/*分析:先求出点u,v的最近公共祖先f,然后求u->f->v的利润最大值maxval
对于这个maxval可能有三种情况:
1:maxval是u->f的maxval
2:maxval是f->v的maxval
3:maxval是u->f的最小w[i]减去f->v的最大w[i]
分析到这很明显需要设置4个变量来求maxval:
up[u]表示u->f的最大maxval
down[u]表示f->u的最大maxval
maxw[u]表示u-f的最大w[i]
minw[u]表示u-f的最小w[i]
所以maxval=max(max(up[u],down[v]),maxw[v]-minw[u]);
现在问题就是如何快速的求出这四个变量,在这里我们可以对u,v的LCA(u,v)进行分类解决
对于LCA(u,v)是f的询问全部求出,然后再求LCA(u,v)是f的父亲的询问
这样当我们求LCA(u,v)是f的父亲的询问的时候就可以借用已经求出的LCA(u,v)是f的询问
 的结果,这样就不用反复去求u->f的那四个变量值,u->father[f]也能快速求出
 这个变化主要在寻找father[v]这个过程中进行,具体看代码 
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
#include <iomanip>
#define INF 99999999
typedef long long LL;
using namespace std;

const int MAX=50000+10;
int n,m,size;
int uu[MAX],vv[MAX],ww[MAX],sum[MAX];
int up[MAX],down[MAX],maxw[MAX],minw[MAX],father[MAX];
int head[MAX],head2[MAX],head3[MAX];
bool mark[MAX];

struct Edge{
	int v,id,next;
	Edge(){}
	Edge(int V,int ID,int NEXT):v(V),id(ID),next(NEXT){}
}edge[MAX*2],edge2[MAX*2],edge3[MAX*2];

void Init(int num){
	for(int i=0;i<=num;++i)head[i]=head2[i]=head3[i]=-1,mark[i]=false;
	size=0; 
}

void InsertEdge(int u,int v,int id){
	edge[size]=Edge(v,id,head[u]);
	head[u]=size++;
}

void InsertEdge2(int u,int v,int id){
	edge2[size]=Edge(v,id,head2[u]);
	head2[u]=size++;
}

void InsertEdge3(int u,int v,int id){
	edge3[size]=Edge(v,id,head3[u]);
	head3[u]=size++;
}

int findset(int v){
	if(v == father[v])return father[v];
	int fa=father[v];
	father[v]=findset(father[v]);
	up[v]=max(max(up[v],up[fa]),maxw[fa]-minw[v]);
	down[v]=max(max(down[v],down[fa]),maxw[v]-minw[fa]);
	maxw[v]=max(maxw[v],maxw[fa]);
	minw[v]=min(minw[v],minw[fa]);
	return father[v];
}

void LCA(int u){
	mark[u]=true;
	father[u]=u;
	for(int i=head2[u];i != -1;i=edge2[i].next){//对LCA(u,v)进行分类 
		int v=edge2[i].v,id=edge2[i].id;
		if(!mark[v])continue;
		int f=findset(v);
		InsertEdge3(f,v,id);
	}
	for(int i=head[u];i != -1;i=edge[i].next){
		int v=edge[i].v;
		if(mark[v])continue;
		LCA(v);
		father[v]=u;
	}
	for(int i=head3[u];i != -1;i=edge3[i].next){
		int id=edge3[i].id;
		findset(uu[id]);
		findset(vv[id]);
		sum[id]=max(max(up[uu[id]],down[vv[id]]),maxw[vv[id]]-minw[uu[id]]);
	}
}

int main(){
	int u,v;
	while(~scanf("%d",&n)){
		Init(n);
		for(int i=1;i<=n;++i){
			scanf("%d",ww+i);
			up[i]=down[i]=0;
			maxw[i]=minw[i]=ww[i];
		}
		for(int i=1;i<n;++i){
			scanf("%d%d",&u,&v);
			InsertEdge(u,v,i);
			InsertEdge(v,u,i); 
		}
		size=0;
		scanf("%d",&m);
		for(int i=0;i<m;++i){
			scanf("%d%d",&uu[i],&vv[i]);
			InsertEdge2(uu[i],vv[i],i);
			InsertEdge2(vv[i],uu[i],i); 
		}
		size=0;
		LCA(1);
		for(int i=0;i<m;++i)printf("%d\n",sum[i]);
	}
	return 0;
}