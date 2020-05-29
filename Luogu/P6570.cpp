#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,MOD=1e9+7;
inline int qpow(int a,int b=MOD-2,int m=MOD)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%MOD;
		a=1ll*a*a%MOD,b>>=1;
	}
	return ans;
}
template<typename T> inline void updmod(T &x){while(x>=MOD?x-=MOD,1:0);}
int phi[N],ps[N],pn;
bool np[N];
void sieve(int n)
{
	phi[1]=1;
	for(int i=2;i<=n;i++)
	{
		if(!np[i]) ps[pn++]=i,phi[i]=i-1;
		for(int j=0;j<pn&&i*ps[j]<=n;j++)
		{
			np[i*ps[j]]=1;
			if(i%ps[j]==0) {phi[i*ps[j]]=phi[i]*ps[j];break;}
			phi[i*ps[j]]=phi[i]*(ps[j]-1);
		}
	}
}
int cnt[N],f[N];
int main()
{
	sieve(1e6);
	int n,mx=0,c0=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		int v;scanf("%d",&v);
		c0+=v==0,cnt[v]+=v!=0;
		mx=max(mx,v);
	}
	int all=1;
	while(all<=mx) all<<=1; --all;
	f[0]=1;
	for(int i=1;i<=mx;i++) if(cnt[i])
	{
		int s=all^i;
		for(int j=s;;j=(j-1)&s)
		{
			updmod(f[i|j]+=1ll*cnt[i]*f[j]%MOD);
			if(!j) break;
		}
	}
	int ans=0;
	for(int i=0;i<=all;i++) updmod(ans+=1ll*f[i]*phi[i+1]%MOD);
	printf("%d\n",1ll*ans*qpow(2,c0)%MOD);
	return 0;
}
