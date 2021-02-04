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
	static constexpr int N = 4e5 + 10;
	int lc[N * 66], rc[N * 66], cnt, sum[N * 66];
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

	std::string s;
	std::cin >> s;
	int n = int(s.size());
	for (int i = 0; i < n; ++i) {
		sam.extend(s[i] - 'a');
		// std::cerr << "i = " << i << '\n';
		// std::cerr << "    last = " << sam.last << '\n';
		stm.modify(sam.t[sam.last].rt, 0, n - 1, i);
	}

	int cntNodes = sam.t.size();

	std::vector<std::vector<int>> e(cntNodes);
	for (int i = 1; i < cntNodes; ++i) {
		e[sam.t[i].link].push_back(i);
	}
	std::function<void(int)> dfs = [&](int u) {
		for (auto v : e[u])
			dfs(v), sam.t[u].rt = stm.merge(sam.t[u].rt, sam.t[v].rt, 0, n - 1);
	};
	dfs(0);

	int q;
	std::cin >> q;
	while (q--) {
		int l, r;
		std::string t;
		std::cin >> l >> r >> t;
		--l, --r;
		int cur = 0, m = int(t.size());
		std::vector<int> at(m + 1);
		int end = m;
		for (int i = 0; i < m; ++i) {
			at[i] = cur;
			cur = sam.t[cur].go[t[i] - 'a'];
			if (cur == -1 || stm.query(sam.t[cur].rt, 0, n - 1, l + i, r) == 0) {
				end = i;
				break;
			}
		}
		if (end == m) at[m] = cur;
		
		// std::cerr << "AT = " << at << '\n';
		// std::cerr << "end = " << end << '\n';

		bool found = false;
		std::string ans = "-1";
		auto check = [&](int p) {
			if (found) return;
			for (int c = (p == m ? 0 : t[p] - 'a' + 1); c < SuffixAutomaton::SIGMA; ++c) {
				int next = sam.t[at[p]].go[c];
				// std::cerr << "at = " << at[p] << '\n';
				// std::cerr << "c = " << c << '\n';
				// std::cerr << "next = " << next << '\n';
				if (next != -1 && stm.query(sam.t[next].rt, 0, n - 1, l + p, r) != 0) {
					found = true;
					ans = "";
					for (int i = 0; i < p; ++i)
						ans += t[i];
					ans += char('a' + c);
					return;
				}
			}
		};
		for (int i = end; i >= 0; --i)
			check(i);
		std::cout << ans << '\n';
	}
	
	return 0;
}