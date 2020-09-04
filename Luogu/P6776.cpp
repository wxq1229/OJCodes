#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;

int lc[N], rc[N], n, m;
bool isleaf[N], isroot[N];

bool check(vector<int> rts) {
	if (!rts.size()) return false;
	for (auto u : rts)
		if (isleaf[u]) return true;
	vector<int> nrt1, nrt2, nrt3, nrt4;
	for (auto u : rts) {
		if (!lc[u]) {
			nrt1.push_back(rc[u]);
		} else if (!rc[u]) {
			nrt2.push_back(lc[u]);
		} else {
			if (isleaf[rc[u]]) nrt3.push_back(lc[u]);
			if (isleaf[lc[u]]) nrt4.push_back(rc[u]);
		}
	}
	return check(nrt1) && check(nrt2) && check(nrt3) && check(nrt4);
}

bool dfs(int u) {
	if (u == 0) return 1;
	return (!lc[u] || !rc[u] || isleaf[lc[u]] || isleaf[rc[u]]) && dfs(lc[u]) && dfs(rc[u]);
}

void solve() {
	isleaf[0] = isroot[0] = 0;
	cin >> m;
	n = 0;
	for (int it = 0; it < m; ++it) {
		int nn;
		cin >> nn;
		for (int i = n + 1; i <= n + nn; ++i)
			isroot[i] = 1;
		for (int i = n + 1; i <= n + nn; ++i) {
			cin >> lc[i] >> rc[i];
			isleaf[i] = !lc[i] && !rc[i];
			if (lc[i]) lc[i] += n;
			if (rc[i]) rc[i] += n;
			isroot[lc[i]] = 0;
			isroot[rc[i]] = 0;
		}
		n += nn;
	}
	vector<int> rts;
	for (int i = 1; i <= n; ++i)
		if (isroot[i] && dfs(i)) rts.push_back(i);
	if (check(rts)) cout << "Almost Complete\n";
	else cout << "No\n";
}

int main() {
	int tt;
	cin >> tt;
	while (tt--) solve();
	return 0;
}