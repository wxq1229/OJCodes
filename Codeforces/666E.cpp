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

struct Info {
	int cnt, id;
	friend Info operator+(const Info &a, const Info &b) {
		if (a.cnt == b.cnt) return a.id < b.id ? a : b;
		else return a.cnt > b.cnt ? a : b;
	}
};

struct SegmentTreeMerger {
	static constexpr int N = 5e5 + 10;
	int lc[N * 33], rc[N * 33], cnt;
	Info mx[N * 33];
	SegmentTreeMerger() { cnt = 0; newNode(); }
	void pushup(int x) {
		assert(x != 0);
		mx[x] = mx[lc[x]] + mx[rc[x]];
	}
	int newNode() {
		int u = cnt++;
		lc[u] = rc[u] = 0;
		mx[u] = {0, 0};
		return u;
	}
	void modify(int &x, int l, int r, int p, int v = 1) {
		if (!x) x = newNode();
		if (l == r) {
			mx[x].id = l;
			++mx[x].cnt;
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
			mx[x].cnt += mx[y].cnt;
			mx[x].id = l;
			return;
		}
		int mid = (l + r) >> 1;
		merge(lc[x], lc[y], l, mid);
		merge(rc[x], rc[y], mid + 1, r);
		pushup(x);
	}
	Info query(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return mx[x];
		int mid = (l + r) / 2;
		if (qr <= mid) return query(lc[x], l, mid, ql, qr);
		else if (mid < ql) return query(rc[x], mid + 1, r, ql, qr);
		else return query(lc[x], l, mid, ql, qr) + query(rc[x], mid + 1, r, ql, qr);
	}
} stm;

struct Query { 
	int l, r, id; 
	friend std::ostream &operator<<(std::ostream &os, const Query &q) {
		return os << "[" << q.l << ", " << q.r << " " << q.id << "]";
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::string s;
	int n;
	std::cin >> s >> n;
	SuffixAutomaton sam;
	std::vector<std::vector<int>> add;
	for (int i = 0; i < n; ++i) {
		std::string t;
		std::cin >> t;
		int cur = 0;
		for (auto c : t) {
			cur = sam.extend(c - 'a', cur);
			add.resize(sam.t.size());
			add[cur].push_back(i);
		}
	}
	int m = int(s.size());
	int cntNodes = sam.t.size();
	std::vector<int> at(m), mxLen(m);
	int cur = 0;
	for (int i = 0; i < m; ++i) {
		int c = s[i] - 'a';
		if (sam.t[cur].go[c] != -1) {
			mxLen[i] = i > 0 ? mxLen[i - 1] + 1 : 1;
			at[i] = cur = sam.t[cur].go[c];
			continue;
		}
		while (cur != 0 && sam.t[cur].go[c] == -1)
			cur = sam.t[cur].link;
		if (sam.t[cur].go[c] != -1) {
			int pLen = sam.t[cur].len;
			cur = sam.t[cur].go[c];
			at[i] = cur;
			mxLen[i] = pLen + 1;
		}
		else at[i] = -1, mxLen[i] = 0;
	}

	// std::cerr << at << '\n

	constexpr int LOG = 18;
	std::vector<std::vector<int>> anc(LOG, std::vector<int>(cntNodes));
	for (int i = 0; i < cntNodes; ++i)
		anc[0][i] = sam.t[i].link;
	for (int i = 1; i < LOG; ++i) {
		for (int u = 0; u < cntNodes; ++u) {
			int v = anc[i - 1][u];
			if (v != -1) anc[i][u] = anc[i - 1][v];
		}
	}
	auto get = [&](int p, int len) {
		if (mxLen[p] < len) return -1;
		int u = at[p];
		if (u == -1) return -1;
		for (int i = LOG - 1; i >= 0; --i) {
			int v = anc[i][u];
			if (v != -1 && sam.t[v].len >= len)
				u = v;
		}
		return u;
	};

	std::vector<std::vector<Query>> queries(cntNodes);
	int q;
	std::cin >> q;
	std::vector<Info> ans(q);
	for (int i = 0; i < q; ++i) {
		int l, r, pl, pr;
		std::cin >> l >> r >> pl >> pr;
		--l, --r, --pl, --pr;
		int u = get(pr, pr - pl + 1);
		if (u != -1) queries[u].push_back({l, r, i});
		else ans[i] = {0, l};
	}

	std::vector<std::vector<int>> e(cntNodes);
	std::vector<int> rt(cntNodes);
	for (int i = 1; i < cntNodes; ++i)
		e[sam.t[i].link].push_back(i);

	std::function<void(int)> dfs = [&](int u) {
		for (auto p : add[u]) stm.modify(rt[u], 0, n - 1, p);
		for (auto v : e[u]) {
			dfs(v);
			stm.merge(rt[u], rt[v], 0, n - 1);
		}
		for (auto query : queries[u]) {
			int l = query.l, r = query.r, id = query.id;
			ans[id] = stm.query(rt[u], 0, n - 1, l, r);
			if (ans[id].cnt == 0) ans[id].id = l;
		}
	};
	dfs(0);

	for (auto v : ans) std::cout << v.id + 1 << " " << v.cnt << '\n';
	return 0;
}