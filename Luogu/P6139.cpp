#include <bits/stdc++.h>
using i64 = long long;

struct SuffixAutomaton {
	static constexpr int SIGMA = 26;
	struct Node {
		int link, len;
		std::array<int, SIGMA> go;
		Node() {
			std::fill(go.begin(), go.end(), -1);
			link = -1;
			len = 0;
		}
	};
	std::vector<Node> t;
	int last;
	int newNode() { t.emplace_back(); return t.size() - 1; }
	SuffixAutomaton() { t.clear(); last = newNode(); }
	void extend(int c) {
		int cur = newNode();
		t[cur].len = t[last].len + 1;
		int p = last;
		for (; p != -1 && t[p].go[c] == -1; p = t[p].link)
			t[p].go[c] = cur;
		if (p == -1) {
			t[cur].link = 0;
		} else {
			int q = t[p].go[c];
			if (t[q].len == t[p].len + 1) {
				t[cur].link = q;
			} else {
				int clone = newNode();
				t[clone].len = t[p].len + 1;
				t[clone].go = t[q].go;
				t[clone].link = t[q].link;
				for (; p != -1 && t[p].go[c] == q; p = t[p].link)
					t[p].go[c] = clone;
				t[q].link = clone;
				t[cur].link = clone;
			}
		}
		last = cur;
	}
} sam;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::string s;
		std::cin >> s;
		sam.last = 0;
		for (auto c : s) sam.extend(c - 'a');
	}

	i64 ans = 0;
	int cntNodes = int(sam.t.size());
	for (int i = 1; i < cntNodes; ++i)
		ans += sam.t[i].len - sam.t[sam.t[i].link].len;
	std::cout << ans << '\n';

	return 0;
}