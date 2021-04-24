#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 310;
constexpr i64 INF = 1e18;
i64 a[N][N], b[N][N];

i64 dis[N * 2];
int cnt[N * 2];
bool inq[N * 2];
struct Edge {
	int v; i64 w;
	Edge(int v = -1, i64 w = 0) : v(v), w(w) { }
};
std::vector<Edge> g[N * 2];

void solve() {
	std::memset(a, 0, sizeof a);
	std::memset(b, 0, sizeof b);
	int n, m;
	std::cin >> n >> m;
	for (int i = 0; i < n - 1; ++i)
		for (int j = 0; j < m - 1; ++j)
			std::cin >> b[i][j];
	for (int i = n - 2; i >= 0; --i)
		for (int j = m - 2; j >= 0; --j)
			a[i][j] = b[i][j] - a[i + 1][j] - a[i][j + 1] - a[i + 1][j + 1];
	
	int V = n + m + 1;
	for (int i = 0; i < V; ++i) {
		g[i].clear();
	}
	int S = n + m;
	for (int i = 0; i < n + m; ++i) {
		g[i].emplace_back(S, i64(1e7));
		g[S].emplace_back(i, i64(1e7));
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (!((i + j) & 1)) {
				g[i].emplace_back(j + n, a[i][j]);
				g[j + n].emplace_back(i, 1e6 - a[i][j]);
			} else {
				g[j + n].emplace_back(i, a[i][j]);
				g[i].emplace_back(j + n, 1e6 - a[i][j]);
			}
		}
	}
	bool negativeCycle = false;
	for (int i = 0; i < V; ++i) {
		inq[i] = 0;
		dis[i] = INF;
		cnt[i] = 0;
	}
	inq[S] = 1, dis[S] = 0, cnt[S] = 0;
	std::queue<int> que;
	que.push(S);
	while (que.size()) {
		int u = que.front();
		que.pop();
		inq[u] = 0;
		for (auto e : g[u]) {
			int v = e.v; i64 w = e.w;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				cnt[v] = cnt[u] + 1;
				if (cnt[v] >= V) { negativeCycle = true; goto END; }
				if (!inq[v])
					inq[v] = 1, que.push(v);
			}
		}
	}
END:
	if (negativeCycle) std::cout << "NO\n";
	else {
		std::cout << "YES\n";
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (j > 0) std::cout << " ";
				if (!((i + j) & 1)) {
					std::cout << a[i][j] + dis[i] - dis[j + n];
				} else {
					std::cout << a[i][j] + dis[j + n] - dis[i];
				}
			}
			std::cout << '\n';
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int tt; std::cin >> tt; while (tt--) solve();
	return 0;
}