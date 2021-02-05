#include <bits/stdc++.h>

template <typename A, typename B> 
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p) {
	os << "{" << p.first << ", " << p.second << "}";
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
	bool fst = true;
	os << "{";
	for (auto t : v) {
		if (fst) fst = false;
		else os << ", ";
		os << t;
	}
	os << "}";
	return os;
}

struct SegmentTreeMerger {
	static constexpr int N = 2e5 + 10;
	int lc[N * 33], rc[N * 33], cnt, sum[N * 33];
	SegmentTreeMerger() { cnt = 1; sum[0] = 0; }
	void pushup(int x) {
		assert(x != 0);
		sum[x] = sum[lc[x]] + sum[rc[x]];
	}
	int newNode() { int u = cnt++; lc[u] = rc[u] = sum[u] = 0; return u; }
	void modify(int &x, int l, int r, int p, int v = 1) {
		if (!x) x = newNode();
		if (l == r) {
			++sum[x];
			return;
		}
		int mid = (l + r) / 2;
		if (p <= mid) modify(lc[x], l, mid, p, v);
		else modify(rc[x], mid + 1, r, p, v);
		pushup(x);
	}
	int merge(int x, int y, int l, int r) {
		if (!x || !y) return x + y;
		int o = ++cnt;
		if (l == r) {
			sum[o] = sum[x] + sum[y];
			return o;
		}
		int mid = (l + r) >> 1;
		lc[o] = merge(lc[x], lc[y], l, mid);
		rc[o] = merge(rc[x], rc[y], mid + 1, r);
		pushup(o);
		return o;
	}
	int query(int x, int l, int r, int ql, int qr) {
		if (!x || ql > qr) return 0;
		if (ql <= l && r <= qr) return sum[x];
		int mid = (l + r) / 2;
		if (qr <= mid) return query(lc[x], l, mid, ql, qr);
		else if (mid < ql) return query(rc[x], mid + 1, r, ql, qr);
		else return query(lc[x], l, mid, ql, qr) + query(rc[x], mid + 1, r, ql, qr);
	}
} stm;

struct SuffixAutomaton {
	static constexpr int SIGMA = 26;
	struct Node {
		int link, len;
		int rt;
		std::array<int, SIGMA> go;
		Node() {
			std::fill(go.begin(), go.end(), -1);
			link = -1;
			len = 0;
			rt = 0;
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

	int n, q;
	std::string s;
	std::cin >> n >> q >> s;
	for (int i = 0; i < n; ++i) {
		sam.extend(s[i] - 'a');
		stm.modify(sam.t[sam.last].rt, 0, n - 1, i);
	}

	int cntNodes = sam.t.size();
	std::vector<int> at(n);
	for (int cur = 0, i = 0; i < n; ++i) {
		if (cur != -1) cur = sam.t[cur].go[s[i] - 'a'];
		at[i] = cur;
	}

	// std::cerr << "at = " << at << '\n';
	
	constexpr int LOG = 18;
	std::vector<std::vector<int>> anc(LOG, std::vector<int>(cntNodes, -1));
	std::vector<std::vector<int>> e(cntNodes);
	for (int i = 1; i < cntNodes; ++i) {
		e[sam.t[i].link].push_back(i);
		anc[0][i] = sam.t[i].link;
	}
	for (int i = 1; i < LOG; ++i) {
		for (int u = 0; u < cntNodes; ++u) {
			int v = anc[i - 1][u];
			if (v != -1) anc[i][u] = anc[i - 1][v];
		}
	}
	auto get = [&](int u, int len) {
		for (int i = LOG - 1; i >= 0; --i) {
			int v = anc[i][u];
			if (v != -1 && sam.t[v].len >= len)
				u = v;
		}
		return u;
	};
	std::function<void(int)> dfs = [&](int u) {
		for (auto v : e[u])
			dfs(v), sam.t[u].rt = stm.merge(sam.t[u].rt, sam.t[v].rt, 0, n - 1);
	};
	dfs(0);

	/*
	std::vector<std::vector<int>> endpos(cntNodes);
	for (int i = 0; i < cntNodes; ++i) {
		for (int j = 0; j < n; ++j) {
			if (stm.query(sam.t[i].rt, 0, n - 1, j, j) != 0) {
				endpos[i].push_back(j);
			}
		}
	}
	for (int i = 0; i < cntNodes; ++i)
		std::cerr << "endpos(" << i << ") = " << endpos[i] << '\n';
	*/

	while (q--) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		--a, --b, --c, --d;
	
		auto check = [&](int len) {
			int p = c + len - 1;
			int u = get(at[p], len);
			if (u < 1) return false;
			// std::cerr << "u = " << u << '\n';
			// std::cerr << "Q " << stm.query(sam.t[u].rt, 0, n - 1, a, b) << '\n';
			return stm.query(sam.t[u].rt, 0, n - 1, a + len - 1, b) != 0;
		};
		
		int lo = 1, hi = std::min(b - a + 1, d - c + 1), ans = 0;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) {
				ans = mid;
				lo = mid + 1;
			} else {
				hi = mid - 1;
			}
		}
		std::cout << ans << '\n';
	}
	
	return 0;
}