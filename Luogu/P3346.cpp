#include <bits/stdc++.h>

constexpr int N = 4e6 + 10, SIGMA = 10;
int next[N][SIGMA], cntNodes, len[N], link[N];
int newNode() {
	int u = cntNodes++;
	len[u] = 0;
	link[u] = -1;
	std::fill(next[u], next[u] + SIGMA, -1);
	return u;
}
void init() {
	cntNodes = 0;
	newNode();
}
int extend(int c, int last) {
	int p = last;
	if (next[p][c] != -1) {
		int q = next[p][c];
		if (len[q] == len[p] + 1) return q;
		else {
			int clone = newNode();
			len[clone] = len[p] + 1;
			link[clone] = link[q];
			for (int i = 0; i < SIGMA; ++i)
				next[clone][i] = next[q][i];
			for (; p != -1 && next[p][c] == q; p = link[p])
				next[p][c] = clone;
			link[q] = clone;
			return clone;
		}
	}
	int cur = newNode();
	len[cur] = len[last] + 1;
	for (; p != -1 && next[p][c] == -1; p = link[p])
		next[p][c] = cur;
	if (p == -1) link[cur] = 0;
	else {
		int q = next[p][c];
		if (len[q] == len[p] + 1) link[cur] = q;
		else {
			int clone = newNode();
			len[clone] = len[p] + 1;
			link[clone] = link[q];
			for (int i = 0; i < SIGMA; ++i)
				next[clone][i] = next[q][i];
			for (; p != -1 && next[p][c] == q; p = link[p])
				next[p][c] = clone;
			link[q] = link[cur] = clone;
		}
	}
	return cur;
}

std::vector<int> e[N];
int n, m, c[N], at[N], deg[N];

void dfs(int u, int p) {
	at[u] = extend(c[u], at[p]);
	for (auto v : e[u]) if (v != p) {
		dfs(v, u);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		std::cin >> c[i];
	for (int i = 1; i < n; ++i) {
		int u, v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
		++deg[u], ++deg[v];
	}

	init(), at[0] = 0;
	for (int i = 1; i <= n; ++i)
		if (deg[i] == 1) dfs(i, 0);
	
	int64_t ans = 0;
	for (int i = 1; i < cntNodes; ++i) {
		ans += len[i] - len[link[i]];
	}
	std::cout << ans << '\n';
	
	return 0;
}