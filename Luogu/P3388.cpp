#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int MAXN=100010;
struct edge{int to,nxt;}e[MAXN<<1];
int head[MAXN],cnt=0;
inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
inline void addedge(int x,int y){add(x,y);add(y,x);}
int dfn[MAXN],low[MAXN],cut[MAXN],idx=0;
void tarjan(int x,int fa){
	int size=0;
	dfn[x]=low[x]=++idx;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (!dfn[v]){
			size++;
			tarjan(v,x);
			if (x!=fa&&low[v]>=dfn[x])
				cut[x]=1;
			low[x]=min(low[x],low[v]);
		}
		low[x]=min(low[x],dfn[v]);
	}
	if (x==fa&&size>=2)
		cut[x]=1;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	rep (i,1,m){
		int x,y;
		scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	rep (i,1,n)
		if (!dfn[i]) tarjan(i,i);
	vector<int>ans;
	rep (i,1,n)
		if (cut[i])ans.push_back(i);
	printf("%d\n",ans.size());
	rep (i,0,ans.size()-1)
		printf("%d ",ans[i]);
	return 0;
}
/*
6 7
1 2
1 3
1 4
2 5
3 5
4 5
5 6





*/

