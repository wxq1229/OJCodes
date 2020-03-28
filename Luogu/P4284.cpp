#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;++i)
#define per(i,a,n) for (int i=n-1;i>=a;--i)
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

const int N=5e5+10;
vector<pair<int,db>> e[N];
db prob[N];
int n;

db dp[N],f[N];

void dfs(int u,int ff) {
	dp[u]=1-prob[u];
	for (auto ei:e[u]) {
		int v=ei.fi; db w=ei.se;
		if (v==ff) continue;
		dfs(v,u);
		dp[u]*=dp[v]+(1-dp[v])*(1-w);
	}
}
void getans(int u,int ff) {
	for (auto ei:e[u]) {
		int v=ei.fi; db w=ei.se;
		if (v==ff) continue;
		db fu=f[u]/(dp[v]+(1-w)*(1-dp[v]));
		f[v]=dp[v]*(fu+(1-fu)*(1-w));
		getans(v,u);
	}
}

int main() {
	scanf("%d",&n);
	rep(i,0,n-1) {
		int u,v; db w;
		scanf("%d%d%lf",&u,&v,&w),w*=0.01;
		e[u].pb(mp(v,w));
		e[v].pb(mp(u,w));
	}
	rep(i,1,n+1) scanf("%lf",&prob[i]),prob[i]*=0.01;
	dfs(1,0);
	f[1]=dp[1];
	getans(1,0);
	db ans=0; rep(i,1,n+1) ans+=1-f[i];
	printf("%.6lf\n",ans);
	return 0;
}