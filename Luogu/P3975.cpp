#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 5e5 + 10, SIGMA = 26;
struct Node {
	int go[SIGMA], link, maxlen;

	Node() {
		std::memset(go, -1, sizeof go);
		link = -1;
		maxlen = 0;
	}
} t[N * 2 + 1];
int last, cntNodes;
i64 siz[N * 2 + 1];

int newNode() { int u = cntNodes++; t[u] = Node(); return u; }
void init() { cntNodes = 0; last = newNode(); siz[last] = 0; }

void extend(int c) {
	int cur = newNode();
    siz[cur] = 1;
	t[cur].maxlen = t[last].maxlen + 1;
	int p = last;
	for (; p != -1 && t[p].go[c] == -1; p = t[p].link)
		t[p].go[c] = cur;
	if (p == -1) {
		t[cur].link = 0;
	} else {
		int q = t[p].go[c];
		if (t[q].maxlen == t[p].maxlen + 1) {
			t[cur].link = q;
		} else {
			int clone = newNode();
            siz[clone] = 0;
			t[clone].maxlen = t[p].maxlen + 1;
			for (int i = 0; i < SIGMA; ++i)
				t[clone].go[i] = t[q].go[i];
			t[clone].link = t[q].link;
			for (; p != -1 && t[p].go[c] == q; p = t[p].link)
				t[p].go[c] = clone;
			t[q].link = clone;
			t[cur].link = clone;
		}
	}
	last = cur;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init();
    std::string s;
    std::cin >> s;
    int n = (int) s.size();
    for (auto c : s) extend(c - 'a');

    int ty; i64 k;
    std::cin >> ty >> k;

    std::vector<std::vector<int>> e(cntNodes);
    for (int i = 0; i < cntNodes; ++i) {
        int u = t[i].link, v = i;
        if (u != -1) e[u].push_back(v);
    }
    std::function<void(int)> dfs = [&](int u) {
        for (auto v : e[u]) dfs(v), siz[u] += siz[v];
    };
    dfs(0);
    siz[0] = 0;
    if (ty == 0) {
        for (int i = 1; i < cntNodes; ++i)
            siz[i] = 1;
    }
    std::vector<i64> cnt(siz, siz + cntNodes);

    std::vector<bool> vis(cntNodes);
    std::function<void(int)> getSiz = [&](int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (int i = 0; i < SIGMA; ++i) {
            int v = t[u].go[i];
            if (v == -1)
                continue;
            getSiz(v), siz[u] += siz[v];
        }
    };
    getSiz(0);
    // for (int i = 0; i < cntNodes; ++i)
        // std::cerr << siz[i] << " ";
    // std::cerr << '\n';

    std::string ans = "";
    std::function<void(int)> solve = [&](int u) {
        if (k <= cnt[u]) return;
        k -= cnt[u];
        for (int i = 0; i < SIGMA; ++i) {
            int v = t[u].go[i];
            if (v == -1) continue;
            if (k > siz[v]) k -= siz[v];
            else {
                ans += char('a' + i);
                solve(v);
                return;
            }
        }
    };
    if (k <= siz[0]) solve(0), std::cout << ans << '\n';
    else std::cout << "-1\n";
    
    return 0;
}