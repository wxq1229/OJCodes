#include <bits/stdc++.h>
using i64 = long long;

template <typename T>
struct LinearBasis {
	static constexpr int N = 64;
	T a[N];
	void insert(T v) {
		for (int i = N - 1; i >= 0; --i) if (v >> i & 1) {
			if (a[i] == 0) { a[i] = v; break; }
			v ^= a[i];
		}
	}
	T query(T ans = 0) {
		for (int i = N - 1; i >= 0; --i) 
			ans = std::max(ans, ans ^ a[i]);
		return ans;
	}
};
LinearBasis<i64> lb;

constexpr int N = 50010;

int n, m, depth[N];
i64 d[N];
std::vector<std::pair<int, i64>> e[N];
void dfs(int u, int p) {
	depth[u] = depth[p] + 1;
	for (auto ei : e[u]) {
		int v = ei.first;
		i64 w = ei.second;
		if (v == p)	continue;
		if (!depth[v]) {
			d[v] = d[u] ^ w;
			dfs(v, u);
		} else {
			if (depth[v] < depth[u])
				lb.insert(d[u] ^ d[v] ^ w);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i <= m; ++i) {
		int u, v;
		i64 w;
		std::cin >> u >> v >> w;
		e[u].push_back(std::make_pair(v, w));
		e[v].push_back(std::make_pair(u, w));
	}
	dfs(1, 0);
	std::cout << lb.query(d[n]) << '\n';

	return 0;
}