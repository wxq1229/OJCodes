#include <bits/stdc++.h>
using i64 = long long;

template <typename T>
struct LinearBasis {
	static constexpr int N = 61;
	T a[N];
	LinearBasis() { std::fill(a, a + N, 0); }
	void insert(T v) {
		for (int i = N - 1; i >= 0; --i) if (v >> i & 1) {
			if (a[i] == 0) { a[i] = v; break; }
			v ^= a[i];
		}
	}
	T query() {
		T ans = 0;
		for (int i = N - 1; i >= 0; --i)
			ans = std::max(ans, ans ^ a[i]);
		return ans;
	}
	T operator[](int i) const { assert(0 <= i && i < N); return a[i]; }
	T &operator[](int i) { assert(0 <= i && i < N); return a[i]; }
	friend LinearBasis operator+(LinearBasis lhs, const LinearBasis &rhs) {
		for (int i = 0; i < N; ++i)
			if (rhs[i] != 0) lhs.insert(rhs[i]);
		return lhs;
	}
};
using LB = LinearBasis<i64>;

constexpr int N = 20010, LOG = 15;
std::vector<int> e[N];
int n, q, anc[LOG][N], depth[N];
LB f[LOG][N];
i64 a[N];

void dfs(int u, int p) {
	f[0][u].insert(a[u]);
	anc[0][u] = p;
	depth[u] = depth[p] + 1;
	for (int i = 1; i < LOG; ++i) {
		f[i][u] = f[i - 1][u] + f[i - 1][anc[i - 1][u]];
		anc[i][u] = anc[i - 1][anc[i - 1][u]];
	}
	for (auto v : e[u]) if (v != p) dfs(v, u);
}
int lca(int u, int v) {
	if (depth[u] < depth[v]) std::swap(u, v);
	for (int i = LOG - 1; i >= 0; --i)
		if (depth[anc[i][u]] >= depth[v]) u = anc[i][u];
	if (u == v) return u;
	for (int i = LOG - 1; i >= 0; --i)
		if (anc[i][u] != anc[i][v]) u = anc[i][u], v = anc[i][v];
	return anc[0][u];
}
LB query(int u, int p) {
	LB ans;
	for (int i = LOG - 1; i >= 0; --i)
		if (depth[anc[i][u]] >= depth[p]) {
			ans = ans + f[i][u];
			u = anc[i][u];
		}
	return ans;
}
LB get(int u, int v) {
	int w = lca(u, v);
	LB ans;
	ans.insert(a[w]);
	return ans + query(u, w) + query(v, w);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		std::cin >> a[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0);
	while (q--) {
		int u, v;
		std::cin >> u >> v;
		std::cout << get(u, v).query() << '\n';
	}
	return 0;
}