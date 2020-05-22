#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn=1e7,N=maxn+10;
int ps[N/10],pn;
bool np[N]; ull phi[N];
void shai(int n)
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
	for(int i=1;i<=n;i++) phi[i]+=phi[i-1];
}
inline ull s1(ll n) {
	if(n&1) return (n+1)/2*n;
	else return n/2*(n+1);
}
map<ll,ull> sphi;
ull Sphi(ll n)
{
	if(n<=maxn) return phi[n];
	if(sphi.count(n)) return sphi[n];
	ull ans=s1(n);
	for(ll l=2,r=0;l<=n;l=r+1)
	{
		r=n/(n/l);
		ans-=(ull)(r-l+1)*Sphi(n/l);
	}
	return sphi[n]=ans;
}
void sol()
{
	ll n; scanf("%lld",&n);
	ull ans=0;
	for(ll l=1,r=0;l<=n;l=r+1)
	{
		r=n/(n/l);
		ans+=(s1(r)-s1(l-1))*(Sphi(n/l)-1);
	}
	printf("%llu\n",ans);
}
int main()
{
	shai(maxn);
	int _; scanf("%d",&_); while(_--) sol();
	return 0;
}
