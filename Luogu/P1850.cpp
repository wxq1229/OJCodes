#include <bits/stdc++.h>
using namespace std;
using db = double;

const int N = 2010;

int n, m, V, E;
db dp[N][N][2], p[N];
int c[N], d[N];
int g[N][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.precision(2);
	cout << fixed;
	cin >> n >> m >> V >> E;
	for (int i = 1; i <= n; ++i)
		cin >> c[i];
	for (int i = 1; i <= n; ++i)
		cin >> d[i];
	for (int i = 1; i <= n; ++i)
		cin >> p[i];
	memset(g, 0x3f, sizeof(g));
	for (int i = 1; i <= V; ++i)
		g[i][i] = 0;
	for (int i = 1; i <= E; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u][v] = min(g[u][v], w);
		g[v][u] = min(g[v][u], w);
	}
	for (int k = 1; k <= V; ++k)
		for (int i = 1; i <= V; ++i)
			for (int j = 1; j <= V; ++j)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for (int i = 1; i <= V; ++i)
		g[i][0] = g[0][i] = 0;
	for (int i = 0; i <= n; ++i)
		for (int j = 0; j <= m; ++j)
			for (int k = 0; k < 2; ++k)
				dp[i][j][k] = 1e9;
	dp[0][0][0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= min(i, m); ++j) {
			vector<vector<int>> tmp = {{g[c[i-1]][c[i]], g[c[i-1]][d[i]]}, {g[d[i-1]][c[i]], g[d[i-1]][d[i]]}};
			dp[i][j][0] = min(dp[i-1][j][0] + tmp[0][0],
							p[i - 1] * (dp[i - 1][j][1] + tmp[1][0])
								+ (1 - p[i - 1]) * (dp[i - 1][j][1] + tmp[0][0]));
			if (j >= 1) {
				dp[i][j][1] = min(
					p[i] * (dp[i - 1][j - 1][0] + tmp[0][1]) + (1 - p[i]) * (dp[i - 1][j - 1][0] + tmp[0][0]),
					p[i] * (p[i - 1] * (dp[i - 1][j - 1][1] + tmp[1][1]) + (1 - p[i - 1]) * (dp[i - 1][j - 1][1] + tmp[0][1]))
						+ (1 - p[i]) * (p[i - 1] * (dp[i - 1][j - 1][1] + tmp[1][0]) + (1 - p[i - 1]) * (dp[i - 1][j - 1][1] + tmp[0][0]))
				);
			}
		}
	}
	db ans = 1e9;
	for (int i = 0; i <= m; ++i)
		ans = min(ans, min(dp[n][i][0], dp[n][i][1]));
	cout << ans << '\n';
	return 0;
}