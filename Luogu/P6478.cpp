#include <bits/stdc++.h>
using namespace std;
#define maxn 5000
#define N 5555
#define MOD 998244353
inline int qpow(int a,int b=MOD-2,int m=MOD)
{
	int ans=1%m;
	for(;b;b>>=1,a=1ll*a*a%m)
		if(b&1) ans=1ll*ans*a%m;
	return ans;
}
inline char nc()
{
	char ch=getchar(); while(isspace(ch))ch=getchar();
	return ch;
}
int fac[N],ifac[N];
inline int comb(int n,int r)
{return 1ll*fac[n]*ifac[r]%MOD*ifac[n-r]%MOD;}
bool bl[N]; int n,m;
int fst[N<<1],nxt[N<<1],to[N<<1],ec;
void ade(int u,int v) {to[++ec]=v,nxt[ec]=fst[u],fst[u]=ec;}
void addedge(int u,int v) {ade(u,v),ade(v,u);}
#define fedge(i,u) for (int i=fst[u],v=to[i];i;i=nxt[i],v=to[i])
int siz[N],c[2][N],f[N][N],df[N];
void dfs(int u,int ff)
{
	f[u][0]=1,siz[u]=1,c[0][u]=bl[u]==0,c[1][u]=bl[u]==1;
	fedge(_,u) if(v!=ff)
	{
		dfs(v,u);
		for(int i=0;i<=siz[u];i++)
			for(int j=0;j<=siz[v];j++)
			{
				df[i+j]+=1ll*f[u][i]*f[v][j]%MOD;
				if(df[i+j]>=MOD) df[i+j]-=MOD;
			}
		siz[u]+=siz[v];
		c[0][u]+=c[0][v],c[1][u]+=c[1][v];
		for(int i=0;i<=siz[u];i++) f[u][i]=df[i];
		for(int i=0;i<=siz[u];i++) df[i]=0;
	}
	int cc=c[!bl[u]][u];
	for(int i=0;i<=cc;i++)
	{
		df[i+1]+=1ll*f[u][i]*(cc-i)%MOD;
		if(df[i+1]>=MOD) df[i+1]-=MOD;
	}
	for(int i=0;i<=siz[u];i++) {f[u][i]+=df[i]; if(f[u][i]>=MOD)f[u][i]-=MOD;}
	for(int i=0;i<=cc;i++) df[i]=df[i+1]=0; 
}
int ans[N];
int main()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<=maxn;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=qpow(fac[i]);
	scanf("%d",&n),m=n>>1;
	for(int i=1;i<=n;i++) bl[i]=nc()=='1';
	for(int u,v,i=1;i<n;i++)
		scanf("%d%d",&u,&v),addedge(u,v);
	dfs(1,0);
	for(int i=0;i<=m;i++)
	{
		ans[i]=0;
		for(int j=i;j<=m;j++)
		{
			ans[i]+=1ll*comb(j,i)*(((j-i)&1)?MOD-1:1)%MOD*f[1][j]%MOD*fac[m-j]%MOD;
			if(ans[i]>=MOD) ans[i]-=MOD;
		}
		printf("%d\n",ans[i]);
	}
	return 0;
}