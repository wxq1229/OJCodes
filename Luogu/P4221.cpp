#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
typedef pair<int,int> pii;
typedef long long ll;
const int N=22,MOD=998244353;
inline int mul(int a,int b) {return 1ll*a*b-1ll*a*b/MOD*MOD;}
int rinv[2222222];
int inv(int n) {
	if(n<=1433223) return rinv[n];
	else return n==1?1:mul((MOD-MOD/n),inv(MOD%n));
}
inline int qpow(int a,int b=MOD-2)
{
	if(!a) return 0;
	if(b==0) return 1;
	if(b==1) return a;
	if(b==2) return mul(a,a);
	int ans=1;
	while(b)
	{
		if(b&1) ans=mul(ans,a);
		a=mul(a,a),b>>=1;
	}
	return ans;
}
int fa[N],deg[N];
int find(int u) {return u==fa[u]?u:fa[u]=find(fa[u]);}
pii es[222];
int w[22],n,m,p;
int f[1<<22],g[22][1<<22],dp[22][1<<22];
bool chk(int S,int i) {return S&(1<<(i-1));}
int bcnt[1<<22];
void fwt(int *f,int n,int flg)
{
	for(int len=2,k=1;len<=n;len<<=1,k<<=1)
		for(int i=0;i<n;i+=len)
			for(int j=i;j<i+k;j++)
			{
				f[j+k]+=flg*f[j];
				if(f[j+k]<0) f[j+k]+=MOD;
				if(f[j+k]>=MOD) f[j+k]-=MOD;
			}
}
int main()
{
	rinv[1]=1;
	for(int i=2;i<=1433223;i++) rinv[i]=mul(MOD-MOD/i,rinv[MOD%i]);
	scanf("%d%d%d",&n,&m,&p); int lim=1<<n;
	for(int i=1;i<=m;i++) scanf("%d%d",&es[i].fi,&es[i].se);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int S=0;S<lim;++S)
	{
		int bs=0,os=0,bc=0;
		for(int i=1;i<=n;i++)
		{
			fa[i]=i,deg[i]=0;
			if(chk(S,i))
			{
				++bc,++bs,f[S]+=w[i];
				if(f[S]>=MOD) f[S]-=MOD;
			}
		}
		for(int i=1;i<=m;i++)
		{
			int u=es[i].fi,v=es[i].se;
			if(chk(S,u)&&chk(S,v))
			{
				++deg[u],++deg[v];
				int pu=find(u),pv=find(v);
				if(pu!=pv) fa[pv]=pu,--bs;
			}
		}
		for(int i=1;i<=n;i++) os+=deg[i]&1;
		if(bs!=1||os!=0) g[bc][S]=f[S]; else g[bc][S]=0;
		g[bc][S]=qpow(g[bc][S],p);
		if(f[S]) f[S]=qpow(inv(f[S]),p);
		bcnt[S]=bc;
	}
	for(int i=0;i<=n;i++) fwt(g[i],lim,1);
	dp[0][0]=1; fwt(dp[0],lim,1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		for(int j=0;j<lim;j++)
			for(int k=0;k<i;k++)
			{
				dp[i][j]+=mul(dp[k][j],g[i-k][j]);	
				if(dp[i][j]>=MOD) dp[i][j]-=MOD;
			}
		fwt(dp[i],lim,-1);
		for(int j=0;j<lim;j++)
			dp[i][j]=bcnt[j]==i?mul(dp[i][j],f[j]):0;
		if(i==n) ans=dp[n][lim-1];
		if(i!=n) fwt(dp[i],lim,1);
	}
	printf("%d\n",ans);
	return 0;
}