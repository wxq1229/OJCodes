#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e8+10;
bool vis[N];
ll pcnt[N],pn,ps[N/10];
void shai(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!vis[i]) ps[pn++]=i,pcnt[i]++;
		for(int j=0;j<pn&&i*ps[j]<=n;j++)
		{
			vis[i*ps[j]]=1;
			if(i%ps[j]==0) break;
		}
	}
	for(int i=1;i<=n;i++) pcnt[i]+=pcnt[i-1];
}
inline ll qpow(ll a,ll b,ll m)
{
	ll ans=1%m;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%m;
		a=1ll*a*a%m,b>>=1;
	}
	return ans;
}
int main()
{
	shai((int)1e8);
	int _; scanf("%d",&_); while(_--)
	{
		ll n,m; scanf("%lld%lld",&n,&m);
		ll ans=1,sqn=(ll)sqrt(n);
		for(int i=0;ps[i]<=sqn;i++)
		{
			ll tmp=0,p=ps[i];
			while (p<=n) tmp=(tmp+n/p)%m,p*=ps[i];
			ans=1ll*ans*(tmp+1)%m;
		}
		for(ll l=sqn+1,r=0;l<=n;l=r+1)
		{
			r=n/(n/l);
			ans=1ll*ans*qpow(n/l+1,pcnt[r]-pcnt[l-1],m)%m;
		}
		printf("%lld\n",ans);
	}
	return 0;
}