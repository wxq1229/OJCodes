#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define MAXN 2010
typedef unsigned long long ull;
struct edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt=0;
inline void adde(int x,int y){
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
inline void addedge(int x,int y){adde(x,y);adde(y,x);}
int low[MAXN],dfn[MAXN],cut[MAXN],idx=0;
void tarjan(int x,int fa){
	dfn[x]=low[x]=++idx;
	int size=0;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (!dfn[v]){
			size++;
			tarjan(v,x);
			low[x]=min(low[x],low[v]);
			if (x!=fa&&low[v]>=dfn[x])
				cut[x]=1;
		}
		low[x]=min(low[x],dfn[v]);
	}
	if (x==fa&&size>=2)cut[x]=1;
}
int num,tot,now;
int vis[MAXN];
void dfs(int x){
	vis[x]=now;num++;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (cut[v]&&vis[v]!=now){
			vis[v]=now;
			tot++;
		}
		if (!vis[v])
			dfs(v);
	}
}
void init(){
	idx=cnt=now=0;
	memset(cut,0,sizeof(cut));
	memset(vis,0,sizeof(vis));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(head,0,sizeof(head));
}
int main(){
	int n,m,kase=0;
	while (scanf("%d",&m)==1&&m){
		n=0;init();
		rep (i,0,m-1){
			int x,y;scanf("%d%d",&x,&y);
			n=max(n,max(x,y));
			addedge(x,y);
		}
		rep (i,1,n)if (!dfn[i])
			tarjan(i,i);
		int ans1=0;ull ans2=1;
		rep (i,1,n)if (!vis[i]&&!cut[i]){
			tot=num=0;
			now++;dfs(i);
			if (tot==0){
				ans1+=2;
				ans2*=1ull*num*(num-1)/2;
			}
			else if (tot==1){
				ans1++;
				ans2*=1ull*num;
			}
		}
		printf("Case %d: %d %llu\n",++kase,ans1,ans2);
	}
	return 0;
}
/*
9
1  3
4  1
3  5
1  2
2  6
1  5
6  3
1  6
3  2
6
1  2
1  3
2  4
2  5
3  6
3  7
0





*/

