#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define mp make_pair
#define pb push_back
#define fi first
#define se second

const int N = 1e5 + 10;

int n;
int depth[N];
vi g[N];
void dfs(int u,int f) {
	depth[u] = depth[f]+1;
	for (auto v:g[u])
		if (v != f) dfs(v,u);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.precision(20);
	cout << fixed;
	cin >> n;
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	dfs(1,0);
	double ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += 1.0 / depth[i];
	cout << ans << '\n';
	return 0;
}