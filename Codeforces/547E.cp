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
	int lc[N * 23], rc[N * 23], cnt, sum[N * 23];
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
	void merge(int &x, int y, int l, int r) {
		if (!x || !y) { x += y; return; }
		if (l == r) {
			sum[x] += sum[y];
			return;
		}
		int mid = (l + r) >> 1;
		merge(lc[x], lc[y], l, mid);
		merge(rc[x], rc[y], mid + 1, r);
		pushup(x);
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
		int len, link;
		int rt;
		std::array<int, SIGMA> go;
		Node() {
			link = -1;
			len = 0;
			rt = 0;
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
} sam;
 
struct Query {
	int l, r, id; 
	friend std::ostream &operator<<(std::ostream &os, const Query &q) {
		return os << "[" << q.l << ", " << q.r << ", " << q.id << "]";
	}
};
 
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
 
	int n, q;
	std::cin >> n >> q;
	std::vector<int> end(n);
	std::vector<std::vector<int>> add(1);
	for (int i = 0; i < n; ++i) {
		std::string s;
		std::cin >> s;
		int &cur = end[i];
		cur = 0;
		for (auto c : s) {
			cur = sam.extend(c - 'a', cur);
			add.resize(sam.t.size());
			add[cur].push_back(i);
		}
	}
 
	int cntNodes = sam.t.size();
	std::vector<std::vector<int>> e(cntNodes);
	for (int i = 1; i < cntNodes; ++i) {
		e[sam.t[i].link].push_back(i);
	}
 
	std::vector<std::vector<Query>> queries(cntNodes);
	for (int i = 0; i < q; ++i) {
		int l, r, k;
		std::cin >> l >> r >> k;
		--l, --r, --k;
		queries[end[k]].push_back({l, r, i});
	}
 
	// std::cerr << "add = " << add << '\n';
	// std::cerr << "e = " << e << '\n';
	// std::cerr << "queries = " << queries << '\n';
 
	std::vector<int> ans(q);
 
	auto debug = [&](int u, char c = '\n') {
		std::cerr << "T(" << u << ") = {";
		for (int i = 0; i < n; ++i) {
			if (i > 0) std::cerr << ", ";
			std::cerr << stm.query(sam.t[u].rt, 0, n - 1, i, i);
		}
		std::cerr << "}" << c;
	};
	
	std::function<void(int)> dfs = [&](int u) {
		for (auto p : add[u]) {
			stm.modify(sam.t[u].rt, 0, n - 1, p);
			// std::cerr << "after modify " << p << "\n    ";
			// debug(u);
		}
		for (auto v : e[u]) {
			dfs(v);
			stm.merge(sam.t[u].rt, sam.t[v].rt, 0, n - 1);
			// std::cerr << "after merge "; debug(u, 0);
			// std::cerr << ", "; debug(v, 0); std::cerr << "\n    ";
			// debug(u);
		}
		for (auto query : queries[u]) {
			int l = query.l, r = query.r, id = query.id;
			ans[id] = stm.query(sam.t[u].rt, 0, n - 1, l, r);
		}
	};
	dfs(0);
	for (auto v : ans) std::cout << v << '\n';
 
	return 0;
}