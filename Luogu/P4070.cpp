#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 1e6 + 10;
struct Node {
    std::map<int, int> go;
	int link, maxlen;

	Node() {
        go.clear();
		link = -1;
		maxlen = 0;
	}
} t[N * 2 + 1];
int last, cntNodes;
i64 ans;

int newNode() { int u = cntNodes++; t[u] = Node(); return u; }
void init() { cntNodes = 0; last = newNode(); }

i64 calc(int u) {
    if (u == 0) return 0;
    return t[u].maxlen - t[t[u].link].maxlen;
}

void extend(int c) {
	int cur = newNode();
	t[cur].maxlen = t[last].maxlen + 1;
	int p = last;
	for (; p != -1 && !t[p].go.count(c); p = t[p].link)
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
            t[clone].go = t[q].go;
			t[clone].link = t[q].link;
            ans += calc(clone);
			for (; p != -1 && t[p].go.count(c) && t[p].go[c] == q; p = t[p].link)
				t[p].go[c] = clone;
            ans -= calc(q);
			t[q].link = clone;
            ans += calc(q);
			t[cur].link = clone;
		}
	}
    ans += calc(cur);
	last = cur;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    init();

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int c; std::cin >> c;
        extend(c);
        std::cout << ans << '\n';
    }
    
    return 0;
}