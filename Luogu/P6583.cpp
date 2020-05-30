#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll pw2[1111],pw5[1111];
ll calc(ll n)
{
	ll ans=0;
	for(int i=0;pw2[i]<=n;i++)
		for(int j=0;pw5[j]*pw2[i]<=n;j++)
		{
			if(i&&j) ans+=n-n/2-n/5+n/10;
			else if(i) ans+=n-n/2;
			else if(j) ans+=n-n/5;
			else ans+=n;
		}
	return ans;
}
int main()
{
	pw2[0]=1; for(int i=1;;i++)
	{
		pw2[i]=pw2[i-1]*2ll;
		if(pw2[i]>(ll)1e12) break;
	}
	pw5[0]=1; for(int i=1;;i++)
	{
		pw5[i]=pw5[i-1]*5ll;
		if(pw5[i]>(ll)1e12) break;
	}
	ll n,ans=0; scanf("%lld",&n);
	for(ll l=1,r=0;l<=n;l=r+1)
	{
		r=n/(n/l);
		ans+=calc(n/l)*(r-l+1);
	}
	printf("%lld\n",ans);
	return 0;
}