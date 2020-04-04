#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
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

const int N=2e5+10;
ll a[N],ans[N],tmp[N];
int n,m;
VI d[N];

int gcd(int x,int y) {return y?gcd(y,x%y):x;}

int main() {
	for (int i=2;i<=200000;i++) for (int j=i;j<=200000;j+=i)
		d[j].pb(i);
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) scanf("%lld",&a[i]);
	sort(a+1,a+n+1),reverse(a+1,a+n+1);
	rep(i,1,n+1) ans[0]+=a[i]*a[i];
	for (auto k:d[n]) {
		ans[k]=0;
		for (int i=1;i<n;i+=k) {
			rep(j,1,k+1) tmp[j]=a[i+j-1];
			for (int j=1;j+2<=k;j++) ans[k]+=tmp[j]*tmp[j+2];
			ans[k]+=tmp[1]*tmp[2]+tmp[k]*tmp[k-1];
		}
	}
	while (m--) {
		int k; scanf("%d",&k);
		if (k==0) printf("%lld\n",ans[0]);
		else printf("%lld\n",ans[n/gcd(n,k)]);
	}
	return 0;
}
