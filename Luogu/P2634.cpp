#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
int gcd(int x,int y){return y==0?x:gcd(y,x%y);}
const int MAXN=20010;
struct edge{int to,w,nxt;}e[MAXN<<1];
int head[MAXN],cur=0;
void addedge(int x,int y,int w){
	e[++cur]=(edge){y,w,head[x]};head[x]=cur;
	e[++cur]=(edge){x,w,head[y]};head[y]=cur;
}
int dp[MAXN],size[MAXN],vis[MAXN],cnt[3],dis[MAXN],root,sum;
int ans=0,n;
void getRoot(int x,int fa){
	size[x]=1,dp[x]=0;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v]||v==fa)continue;
		getRoot(v,x);
		size[x]+=size[v];
		dp[x]=max(dp[x],size[v]);
	}
	dp[x]=max(dp[x],sum-size[x]);
	if (dp[x]<dp[root])root=x;
}
void getDis(int x,int fa){
	cnt[dis[x]%3]++;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa||vis[v])continue;
		dis[v]=(dis[x]+e[i].w)%3;
		getDis(v,x);
	}
}
int calc(int x,int w){
	cnt[0]=cnt[1]=cnt[2]=0,dis[x]=w;
	getDis(x,0);
	return cnt[0]*cnt[0]+cnt[1]*cnt[2]*2;
}
void solve(int x){
	vis[x]=1;ans+=calc(x,0);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v])continue;
		ans-=calc(v,e[i].w);
		sum=size[v],dp[root=0]=n,getRoot(v,0);
		solve(root);
	}
}
int main(){
	scanf("%d",&n);
	rep (i,1,n-1){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		addedge(x,y,w);
	}
	sum=dp[root=0]=n,getRoot(1,0);
	solve(root);
	int tmp=gcd(ans,n*n);
	printf("%d/%d\n",ans/tmp,n*n/tmp);
	return 0;
}
/*
5
1 2 1
1 3 2
1 4 1
2 5 3
*/







