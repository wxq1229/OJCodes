#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using ll = long long;
using pii = pair<int,int>;

const int N = 2010;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
vector<pii> g[N];
ll dp[N][N];
int n, k, siz[N], depth[N];

void dfs(int u,int f) {
	depth[u] = depth[f]+1;
	siz[u] = 1;
	for (auto e:g[u]) {
		int v = e.fi;
		ll w = e.se;
		if (v==f) continue;
		dfs(v,u);
		static ll tmp[N];
		for (int i=0; i<=siz[u]+siz[v]; ++i)
			tmp[i] = -INF;
		for (int i=0; i<=siz[u]; ++i)
			for (int j=0; j<=siz[v]; ++j)
				tmp[i+j] = max(tmp[i+j], dp[u][i] + dp[v][j] + w * j * (k - j) + w * (siz[v] - j) * (n - k - (siz[v]-j)));
		siz[u] += siz[v];
		for (int i=0; i<=siz[u]; ++i)
			dp[u][i] = tmp[i];
	}
}

int main() {
	cin >> n >> k;
	for (int i = 1; i < n; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v,w)), g[v].pb(mp(u,w));
	}
	dfs(1,0);
	cout << dp[1][k] << '\n';
	return 0;
}