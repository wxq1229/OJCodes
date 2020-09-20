#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using db = double;

const int N = 1e5 + 10;
vector<pair<int,int>> g[N];
bool vis[N];
db dp[N];

db solve(int u) {
	if (vis[u]) return dp[u];
	db &ans = dp[u];
	ans = 0;
	vis[u] = 1;
	int deg = (int) g[u].size();
	for (auto e:g[u])
		ans += (e.se + solve(e.fi)) / deg;
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin >> n >> m;
	for (int i=1; i<=m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v,w));
	}
	memset(vis,0,sizeof(vis));
	vis[n] = 0;
	dp[n] = 0;
	cout << setprecision(2) << fixed << solve(1) << '\n';
	return 0;
}
