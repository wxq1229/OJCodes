#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
const int MOD=23333,N=1e5+10,B=222;
template<typename T> inline void upd(T &x) {while(x>=MOD) x-=MOD;}
vi g[N],f[B+10][B+10];
bool vis[N];
int phi[N],ps[N],pn,mu[N];
void init()
{
	int n=(int)5e4;
	phi[1]=mu[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!vis[i])
		{
			phi[i]=i-1,mu[i]=-1;
			ps[pn++]=i;
		}
		for(int j=0;j<pn&&i*ps[j]<=n;j++)
		{
			vis[i*ps[j]]=1;
			if(i%ps[j]) phi[i*ps[j]]=phi[i]*(ps[j]-1),mu[i*ps[j]]=-mu[i];
			else {phi[i*ps[j]]=phi[i]*ps[j];mu[i*ps[j]]=0;break;}
		}
	}
	for(int i=1;i<=n;i++) phi[i]%=MOD,mu[i]=(mu[i]+MOD)%MOD;
	for(int i=1;i<=n;i++)
	{
		int lim=n/i;
		g[i]=vi(lim+1,0);
		for(int j=1;j<=lim;j++) upd(g[i][j]=g[i][j-1]+phi[i*j]);
	}
	for(int a=1;a<=B;a++)
	for(int b=1;b<=B;b++)
	{
		int lim=n/max(a,b);
		f[a][b]=vi(lim+1,0);
		for(int i=1;i<=lim;i++)
		{
			int tmp=1ll*mu[i]*g[i][a]%MOD*g[i][b]%MOD;
			for(int j=i;j<=lim;j+=i) upd(f[a][b][j]+=tmp);
		}
		for(int i=1;i<=lim;i++) upd(f[a][b][i]+=f[a][b][i-1]);
	}
}
int main()
{
	init();
	int _; for(scanf("%d",&_);_;_--)
	{
		int n,m; scanf("%d%d",&n,&m);
		int ans=0,tn=min(n,m),lst=23333;
		for(int i=1;;i++) if(n/i<=B&&m/i<=B) {lst=i-1;break;}
		for(int i=1;i<=lst;i++)
			for(int j=i;j<=lst;j+=i) upd(ans+=1ll*mu[i]*g[i][n/j]%MOD*g[i][m/j]%MOD);
		for(int l=lst+1,r=0;l<=tn;l=r+1)
		{
			r=min(n/(n/l),m/(m/l));
			upd(ans+=(f[n/l][m/l][r]-f[n/l][m/l][l-1]+MOD)%MOD);
		}
		printf("%d\n",ans);
	}
	return 0;
}
