#include <bits/stdc++.h>

constexpr int N = 2e5 + 10, LOG = 19;

struct SegmentTree {
	int lc[N * 55], rc[N * 55], val[N * 55], cnt = 0;
	void ins(int pre, int &x, int l, int r, int p, int v) {
		x = ++cnt, lc[x] = lc[pre], rc[x] = rc[pre], val[x] = v;
		if (l == r) return; int mid = (l + r) >> 1;
		if (p <= mid) ins(lc[pre], lc[x], l, mid, p, v);
		else ins(rc[pre], rc[x], mid + 1, r, p, v);
	}
	int qry(int x, int l, int r, int p) {
		if (p == 0 || x == 0) return 0;
		if (l == r) return val[x]; int mid = (l + r) >> 1;
		if (p <= mid) return qry(lc[x], l, mid, p);
		else return qry(rc[x], mid + 1, r, p);
	}
} st;

int n, m, col[N], P[N], cap;
std::vector<int> e[N];
int at[N];

int depth[N], anc[N][LOG], rt[N];
void dfs(int u, int p) {
	st.ins(rt[p], rt[u], 1, m, col[u], u);
	depth[u] = depth[p] + 1, anc[u][0] = p;
	for (int i = 1; i < LOG; ++i) anc[u][i] = anc[anc[u][i - 1]][i - 1];
	for (auto v : e[u]) if (v != p) dfs(v, u);
}

int up[N][LOG], down[N][LOG];
void dfs2(int u, int p) {
	if (at[col[u]] != 0) {
		up[u][0] = st.qry(rt[u], 1, m, P[at[col[u]] + 1]);
		down[u][0] = st.qry(rt[u], 1, m, P[at[col[u]] - 1]);
	}
	for (int i = 1; i < LOG; ++i)
		up[u][i] = up[up[u][i - 1]][i - 1], down[u][i] = down[down[u][i - 1]][i - 1];
	for (auto v : e[u]) if (v != p) dfs2(v, u);
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) std::swap(u, v);
	for (int i = LOG - 1; i >= 0; --i)
		if (depth[anc[u][i]] >= depth[v]) u = anc[u][i];
	if (u == v) return u;
	for (int i = LOG - 1; i >= 0; --i)
		if (anc[u][i] != anc[v][i]) u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int qry(int s, int t) { 
	int w = lca(s, t);
	// std::cerr << "s, t, w = " << s << ", " << t << ", " << w << '\n';
	s = st.qry(rt[s], 1, m, P[1]);
	int p = depth[s] >= depth[w];
	// std::cerr << "  s = " << s << '\n';
	for (int i = LOG - 1; i >= 0; --i)
		if (depth[up[s][i]] >= depth[w]) s = up[s][i], p += 1 << i;
	// std::cerr << "  p, s = " << p << ", " << s << '\n';
	int lo = p + 1, hi = cap, end = p;
	auto check = [&](int mid) {
		int v = st.qry(rt[t], 1, m, P[mid]), k = mid - p - 1;
		for (int i = LOG - 1; i >= 0; --i)
			if (k >> i & 1) v = down[v][i];
		return depth[v] > depth[w];
	};
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (check(mid)) end = mid, lo = mid + 1;
		else hi = mid - 1;
	}
	return end;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> cap;
	for (int i = 1; i <= cap; ++i) {
		std::cin >> P[i];
		at[P[i]] = i;
	}
	for (int i = 1; i <= n; ++i)
		std::cin >> col[i];
	for (int i = 1; i < n; ++i) {
		int u, v; std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(1, 0), dfs2(1, 0);

	// for (int i = 1; i <= n; ++i) {
	// 	std::cerr << i << ": [";
	// 	for (int j = 1; j <= m; ++j) {
	// 		if (j - 1) std::cerr << ", ";
	// 		std::cerr << st.qry(rt[i], 1, m, j);
	// 	}
	// 	std::cerr << "]\n";
	// }

	int Q, s, t; for (std::cin >> Q; Q--;) std::cin >> s >> t, std::cout << qry(s, t) << '\n';
	
	return 0;
}