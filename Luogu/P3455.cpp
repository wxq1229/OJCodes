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

const int N=5e4+10;
int mu[N],sum[N],vis[N];
int p[N],pn;

void init(int n) {
	mu[1]=1;
	rep(i,2,n+1) {
		if(!vis[i]) {
			mu[i]=-1;
			p[pn++]=i;
		}
		for(int j=0;j<pn&&i*p[j]<=n;j++) {
			vis[i*p[j]]=1;
			if (i%p[j]) mu[i*p[j]]=mu[i]*mu[p[j]];
			else {mu[i*p[j]]=0;break;}
		}
	}
	rep(i,1,n+1) sum[i]=sum[i-1]+mu[i];
}
#define S(l,r) (sum[r]-sum[l-1])

int solve(int n,int m,int d) {
	n/=d,m/=d; int tn=min(n,m);
	ll ans=0;
	for(int l=1,r=0;l<=tn;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		ans+=1ll*S(l,r)*(n/l)*(m/l);
	}
	return ans;
}

int main() {
	init(50000);
	int _,n,m,d; for(scanf("%d",&_);_;_--) {
		scanf("%d%d%d",&n,&m,&d);
		printf("%d\n",solve(n,m,d));
	}
	return 0;
}