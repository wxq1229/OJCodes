#include <bits/stdc++.h>
using namespace std;
#define fore(i,x) for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
const int N=5e4+10,P=10007;
inline int add(int x,int y){return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y){return (x-=y)<0?x+P:x;}
inline int fpow(int x,int y)
{
	int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
		if(y&1) ret=1ll*ret*x%P;
	return ret;
}
int n,K;
struct edge
{
	int to,nxt;
}e[N<<1];
int head[N],cnt=0;
inline void ade(int x,int y)
{e[++cnt]=(edge){y,head[x]};head[x]=cnt;}
inline void addedge(int x,int y){ade(x,y),ade(y,x);}
int dp[N][233],f[N][233];
void dfs(int x,int prev)
{
	dp[x][0]=1;
	fore(_,x) if(v!=prev)
	{
		dfs(v,x);
		dp[x][0]=add(dp[x][0],dp[v][0]);
		for(int i=1;i<=K;i++)
			dp[x][i]=add(dp[x][i],add(dp[v][i-1],dp[v][i]));
	}
}
void getans(int x,int prev)
{
	fore(_,x) if(v!=prev)
	{
		static int fx[233];
		fx[0]=sub(f[x][0],dp[v][0]);
		f[v][0]=add(dp[v][0],fx[0]);
		for(int i=1;i<=K;i++) fx[i]=sub(f[x][i],add(dp[v][i-1],dp[v][i]));
		for(int i=1;i<=K;i++)
			f[v][i]=add(dp[v][i],add(fx[i-1],fx[i]));
		getans(v,x);
	}
}
int S[233][233],fac[233];
int main()
{
	scanf("%d%d",&n,&K);
	fac[0]=1;for(int i=1;i<=K;i++) fac[i]=fac[i-1]*i%P;
	S[0][0]=1;
	for(int i=1;i<=K;i++)
		for(int j=1;j<=K;j++)
			S[i][j]=add(S[i-1][j]*j%P,S[i-1][j-1]);
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),addedge(x,y);
	dfs(1,0);
	for(int i=0;i<=K;i++) f[1][i]=dp[1][i];
	getans(1,0);
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=0;j<=K;j++)
			ans=add(ans,S[K][j]*fac[j]%P*f[i][j]%P);
		printf("%d\n",ans);
	}
	return 0;
}