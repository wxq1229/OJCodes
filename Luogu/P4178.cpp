#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define MAXN 100010
int head[MAXN],cnt=0;
struct edge{
	int to,w,nxt;
}e[MAXN<<1];
void add(int x,int y,int w){e[++cnt]=(edge){y,w,head[x]};head[x]=cnt;}
void addedge(int x,int y,int w){add(x,y,w);add(y,x,w);}
int root,sum,n,K,dp[MAXN],size[MAXN],vis[MAXN],dis[MAXN];
void getRoot(int x,int fa){
	size[x]=1;dp[x]=0;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa||vis[v])continue;
		getRoot(v,x);
		size[x]+=size[v];
		dp[x]=max(dp[x],size[v]);
	}
	dp[x]=max(dp[x],sum-size[x]);
	if (dp[x]<dp[root]) root=x;
}
int d[MAXN],tot;
void getDis(int x,int fa){
	d[++tot]=dis[x];
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa||vis[v])continue;
		dis[v]=dis[x]+e[i].w;
		getDis(v,x);
	}
}
int calc(int x,int w){
	tot=0;dis[x]=w;getDis(x,0);
	sort(d+1,d+tot+1);
	int l=1,r=tot,res=0;
	while (l<=r){
		if (d[l]+d[r]<=K)res+=r-l,l++;
		else r--;
	}
	return res;
}
int ans=0;
void solve(int x){
	vis[x]=1;ans+=calc(x,0);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v])continue;
		ans-=calc(v,e[i].w);
		dp[root=0]=n,sum=size[v];getRoot(v,x);
		solve(root);
	}
}
int main(){
	scanf("%d",&n);
	rep (i,1,n-1){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		addedge(x,y,w);
	}
	dp[root=0]=sum=n;
	scanf("%d",&K);
	getRoot(1,0);solve(root);
	printf("%d\n",ans);
	return 0;
}
/*
7
1 6 13 
6 3 9 
3 5 7 
4 1 3 
2 4 20 
4 7 2 
10
*/





