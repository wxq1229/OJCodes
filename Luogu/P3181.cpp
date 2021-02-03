#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 4e5 + 10, SIGMA = 27;

struct Node {
	int go[SIGMA], link, maxlen;

	Node() {
		std::memset(go, -1, sizeof go);
		link = -1;
		maxlen = 0;
	}
} t[N * 2];
int last, cntNodes, cnt[N * 2][2];

int newNode() { int u = cntNodes++; t[u] = Node(); return u; }
void init() { cntNodes = 0; last = newNode(); }

void extend(int c) {
	int cur = newNode();
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

	std::string S, T;
	std::cin >> S >> T;
	int n = int(S.size()), m = int(T.size());
	std::string foo = S + "!" + T;
	// std::cerr << foo << '\n';
	for (int i = 0; i < int(foo.size()); ++i) {
		if (i == n) extend(26);
		else if (i < n) extend(foo[i] - 'a'), cnt[last][0] = 1;
		else extend(foo[i] - 'a'), cnt[last][1] = 1;
	}

	std::vector<std::vector<int>> e(cntNodes);
	for (int i = 0; i < cntNodes; ++i){
		if (i > 0) e[t[i].link].push_back(i);
	}
	std::function<void(int)> dfs = [&](int u) {
		for (auto v : e[u]) {
			dfs(v);
			cnt[u][0] += cnt[v][0];
			cnt[u][1] += cnt[v][1];
		}
	};
	dfs(0);
	
	// for (int i = 0; i < cntNodes; ++i)
	// 	std::cerr << cnt[i][0] << "," << cnt[i][1] << " ";
	// std::cerr << '\n';

	i64 ans = 0;
	for (int i = 1; i < cntNodes; ++i)
		ans += i64(t[i].maxlen - t[t[i].link].maxlen) * cnt[i][0] * cnt[i][1];
	std::cout << ans << '\n';

	return 0;	
}