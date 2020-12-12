#include <bits/stdc++.h>

constexpr int N = 1e6 + 10, LOG = 21;

int depth[N];
int nxt[N], anc[LOG][N];

int lca(int u, int v) {
	if (depth[u] < depth[v]) std::swap(u, v);
	for (int i = LOG - 1; i >= 0; --i)
		if (depth[anc[i][u]] >= depth[v]) u = anc[i][u];
	if (u == v) return u;
	for (int i = LOG - 1; i >= 0; --i)
		if (anc[i][u] != anc[i][v]) u = anc[i][u], v = anc[i][v];
	return anc[0][u];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::string s;
	std::cin >> s;
	int n = (int) s.size();
	s = "!" + s;

	nxt[1] = 0;
	for (int i = 2; i <= n; ++i) {
		int j = nxt[i - 1];
		while (j != 0 && s[j + 1] != s[i])
			j = nxt[j];
		nxt[i] = j + (s[j + 1] == s[i]);
	}

	for (int i = 1; i <= n; ++i) {
		anc[0][i] = nxt[i];
		depth[i] = depth[nxt[i]] + 1;
	}
	for (int j = 1; j < LOG; ++j) {
		for (int i = 1; i <= n; ++i)
			anc[j][i] = anc[j - 1][anc[j - 1][i]];
	}

	int m;
	std::cin >> m;
	while (m--) {
		int u, v;
		std::cin >> u >> v;
		int w = lca(u, v);
		if (w == u || w == v)
			std::cout << anc[0][w] << '\n';
		else std::cout << w << '\n';
	}
	return 0;
}