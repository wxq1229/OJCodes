#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100010;
int n,K;
struct edge{
	int to,nxt;
}e[MAXN*2];
int head[MAXN],cnt=0;
void adde(int x,int y){
	e[++cnt]=(edge){y,head[x]},head[x]=cnt;
}
void addedge(int x,int y){
	adde(x,y);
	adde(y,x);
}
int size[MAXN],dp[MAXN],vis[MAXN],root,sum;
void getRoot(int x,int prev){
	size[x]=1,dp[x]=0;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev||vis[v]) continue;
		getRoot(v,x);
		size[x]+=size[v];
		dp[x]=max(dp[x],size[v]);
	}
	if ((dp[x]=max(dp[x],sum-size[x]))<dp[root])
		root=x;
}
int tot=0,dis[MAXN],D[MAXN];
void getDis(int x,int prev){
	D[++tot]=dis[x];
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev||vis[v]) continue;
		dis[v]=dis[x]+1,getDis(v,x);
	}
}
ll calc(int x,int w){
	dis[x]=w,tot=0,getDis(x,0);
	sort(D+1,D+tot+1);
	int l=1,r=tot;
	ll tmp1=0,tmp2=0;
	while (l<r){
		if (D[l]+D[r]<=K) tmp1+=r-l,l++;
		else r--;
	}
	l=1,r=tot;
	while (l<r){
		if (D[l]+D[r]<K) tmp2+=r-l,l++;
		else r--;
	}
	return tmp1-tmp2;
}
ll ans=0;
void solve(int x){
	vis[x]=1,ans+=calc(x,0);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v]) continue;
		ans-=calc(v,1);
		sum=size[v],dp[root=0]=0x3f3f3f3f;
		getRoot(v,x),solve(root);
	}
}
int main(){
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	dp[root=0]=0x3f3f3f3f,sum=n;
	getRoot(1,0),solve(root);
	printf("%I64d\n",ans);
	return 0;
}










