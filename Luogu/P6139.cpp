#include <bits/stdc++.h>

struct SuffixAutomaton {
	static constexpr int SIGMA = 26;
	struct Node {
		int len, link;
		std::array<int, SIGMA> go;
		Node() {
			link = -1;
			len = 0;
			std::fill(go.begin(), go.end(), -1);
		}
	};
	std::vector<Node> t;
	int newNode() { t.emplace_back(); return t.size() - 1; }
	SuffixAutomaton() { t.clear(); newNode(); }
	int extend(int c, int last) {
		if (t[last].go[c] != -1) {
			int p = last;
			int q = t[p].go[c];
			if (t[q].len == t[p].len + 1) return q;
			else {
				int clone = newNode();
				t[clone].go = t[q].go;
				t[clone].link = t[q].link;
				t[clone].len = t[p].len + 1;
				for (; p != -1 && t[p].go[c] == q; p = t[p].link)
					t[p].go[c] = clone;
				t[q].link = clone;
				return clone;
			}
		}
		int cur = newNode();
		t[cur].len = t[last].len + 1;
		int p = last;
		for (; p != -1 && t[p].go[c] == -1; p = t[p].link)
			t[p].go[c] = cur;
		if (p == -1) t[cur].link = 0;
		else {
			int q = t[p].go[c];
			if (t[q].len == t[p].len + 1) t[cur].link = q;
			else {
				int clone = newNode();
				t[clone].link = t[q].link;
				t[clone].go = t[q].go;
				t[clone].len = t[p].len + 1;
				for (; p != -1 && t[p].go[c] == q; p = t[p].link)
					t[p].go[c] = clone;
				t[q].link = t[cur].link = clone;
			}
		}
		return cur;
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	SuffixAutomaton sam;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		std::string s;
		std::cin >> s;
		int last = 0;
		for (auto c : s) last = sam.extend(c - 'a', last);
	}
	int cntNodes = sam.t.size();
	int64_t ans = 0;
	for (int i = 1; i < cntNodes; ++i)
		ans += sam.t[i].len - sam.t[sam.t[i].link].len;
	std::cout << ans << '\n';
	return 0;
}