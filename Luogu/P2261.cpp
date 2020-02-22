#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<(b);++i)
#define per(i,a,b) for (int i=(a)-1;i>=(b);--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

#define s1(l,r) (1ll*(l+r)*(r-l+1)/2)

int main() {
	int n,k; scanf("%d%d",&n,&k);
	ll ans=1ll*n*k;
	for(int l=1,r=0;l<=n;l=r+1) {
		if(l<=k) r=min(n,k/(k/l));
		else r=n;
		// cout<<l<<" "<<r<<endl;
		ans-=k/l*s1(l,r);
	}
	printf("%lld\n",ans);
	return 0;
}