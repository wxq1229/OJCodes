#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int MAXN=100010;
int dp[MAXN],size[MAXN],vis[MAXN],head[MAXN],cnt=0;
struct edge{int to,w,nxt;}e[MAXN<<1];
void add(int x,int y,int w){e[++cnt]=(edge){y,w,head[x]};head[x]=cnt;}
void addedge(int x,int y,int w){add(x,y,w);add(y,x,w);}
int root,n,Q,sum,q[MAXN],ans[10000010];
void getRoot(int x,int fa){
	size[x]=1;dp[x]=0;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v]||v==fa)continue;
		getRoot(v,x);
		size[x]+=size[v];
		dp[x]=max(dp[x],size[v]);
	}
	dp[x]=max(dp[x],sum-size[x]);
	if (dp[x]<dp[root]) root=x;
}
int dis[MAXN],d[MAXN],tot=0;
void getDis(int x,int fa){
	d[++tot]=dis[x];
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa||vis[v])continue;
		dis[v]=dis[x]+e[i].w;
		getDis(v,x);
	}
}
void calc(int x,int w,int k1){
	tot=0;dis[x]=w;getDis(x,w);
	rep (i,1,tot) rep (j,1,tot)
		ans[d[i]+d[j]]+=k1;
}
void solve(int x){
	calc(x,0,1);
	vis[x]=1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v])continue;
		calc(v,e[i].w,-1);
		sum=size[v],dp[root=0]=n;
		getRoot(v,0);solve(root);
	}
}
int main(){
	scanf("%d%d",&n,&Q);
	rep (i,1,n-1){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		addedge(x,y,w);
	}
	dp[root=0]=n,sum=n;
	getRoot(1,0);solve(root);
	while (Q--){
		int k1;scanf("%d",&k1);
		puts(ans[k1]?"AYE":"NAY");
	}
	return 0;
}
/*
2 1
1 2 2
2
*/

