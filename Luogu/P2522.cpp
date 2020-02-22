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

const int maxn=5e4,N=5e4+10;
int vis[N],sum[N],mu[N],p[N],pn;

void init(int n) {
	mu[1]=1;
	rep(i,2,n+1) {
		if(!vis[i]) {p[pn++]=i;mu[i]=-1;}
		for(int j=0;j<pn&&i*p[j]<=n;j++) {
			vis[i*p[j]]=1;
			if(i%p[j]==0) {mu[i*p[j]]=0;break;}
			else mu[i*p[j]]=mu[i]*mu[p[j]];
		}
	}
	rep(i,1,n+1) sum[i]=sum[i-1]+mu[i];
}

int solve(int n,int m) {
	int tn=min(n,m); ll ans=0;
	for(int l=1,r=0;l<=tn;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		ans+=1ll*(sum[r]-sum[l-1])*(n/l)*(m/l);
	}
	return ans;
}

int main() {
	init(maxn);
	int _,lx,ly,rx,ry,k; for(scanf("%d",&_);_;--_) {
		scanf("%d%d%d%d%d",&lx,&rx,&ly,&ry,&k);
		printf("%d\n",solve(rx/k,ry/k)-solve((lx-1)/k,ry/k)
						-solve(rx/k,(ly-1)/k)+solve((lx-1)/k,(ly-1)/k));
	}
	return 0;
}