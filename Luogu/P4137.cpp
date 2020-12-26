#include <bits/stdc++.h>

constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f, MX = 2e5 + 1;

struct SegmentTree {
	struct Node {
		int l, r;
		int mn;
	} t[N << 2];

	void pushup(int x) {
		t[x].mn = std::min(t[x << 1].mn, t[x << 1 | 1].mn);
	}

	void modify(int x, int p, int v) {
		int l = t[x].l, r = t[x].r;
		if (l == r) {
			t[x].mn = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) modify(x << 1, p, v);
		else modify(x << 1 | 1, p, v);
		pushup(x);
	}

	int query(int x, int ql, int qr) {
		int l = t[x].l, r = t[x].r;
		if (ql <= l && r <= qr) return t[x].mn;
		int mid = (l + r) >> 1, ans = INF;
		if (ql <= mid) ans = std::min(ans, query(x << 1, ql, qr));
		if (mid < qr) ans = std::min(ans, query(x << 1 | 1, ql, qr));
		return ans;
	}

	void build(int x, int l, int r) {
		t[x].l = l, t[x].r = r, t[x].mn = INF;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(x << 1, l, mid);
		build(x << 1 | 1, mid + 1, r);
	}
} ST;

int n, m;
int a[N], pos[N];

std::multiset<int> set[N];

struct Query { int l, r, id; };
std::vector<Query> queries[N];
int ans[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	std::cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		std::cin >> a[i];

	ST.build(1, 0, MX);
	for (int i = 0; i <= MX; ++i) {
		pos[i] = 0;
		set[0].insert(i);
	}
	ST.modify(1, 0, 0);

	for (int i = 1; i <= m; ++i) {
		int l, r;
		std::cin >> l >> r;
		queries[r].push_back({l, r, i});
	}

	for (int i = 1; i <= n; ++i) {
		int last = pos[a[i]];
		set[last].erase(set[last].find(a[i]));
		pos[a[i]] = i;
		int next = i;
		set[next].insert(a[i]);
		ST.modify(1, last, set[last].size() ? *set[last].begin() : INF);
		ST.modify(1, next, set[next].size() ? *set[next].begin() : INF);

		/*
		std::cerr << "i = " << i << "\n  ";
		for (int j = 0; j <= 5; ++j)
			std::cerr << ST.query(1, j, j) << " ";
		std::cerr << '\n';
		*/

		for (auto q : queries[i]) {
			int l = q.l, r = q.r, id = q.id;
			ans[id] = ST.query(1, 0, l - 1);
		}
	}
	for (int i = 1; i <= m; ++i)
		std::cout << ans[i] << '\n';
	return 0;
}