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

constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f;

struct SegmentTree {
	struct Node {
		int l, r;
		int mn;
	} t[N * 4];

	void pushup(int x) {
		t[x].mn = std::min(t[x * 2].mn, t[x * 2 + 1].mn);
	}

	void modify(int x, int p, int v) {
		int l = t[x].l, r = t[x].r;
		if (l == r) { t[x].mn = std::min(t[x].mn, v); return; }
		int mid = (l + r) >> 1;
		if (p <= mid) modify(x * 2, p, v);
		else modify(x * 2 + 1, p, v);
		pushup(x);
	}

	int query(int x, int ql, int qr) {
		if (ql > qr) return t[x].mn;
		int l = t[x].l, r = t[x].r;
		if (ql <= l && r <= qr) {
			return t[x].mn;
		}
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(x * 2, ql, qr);
		else if (mid < ql) return query(x * 2 + 1, ql, qr);
		else return std::min(query(x * 2, ql, qr), query(x * 2 + 1, ql, qr));
	}

	void build(int x, int l, int r) {
		t[x].l = l, t[x].r = r;
		if (l == r) {
			t[x].mn = INF;
			return;
		}
		int mid = (l + r) >> 1;
		build(x * 2, l, mid);
		build(x * 2 + 1, mid + 1, r);
		pushup(x);
	}
} ST;

// abcba -> (!a!b!c!c!a!)
std::string adjust(const std::string &s) {
	std::string res = "(";
	for (auto ch : s) {
		res += "!";
		res += ch;
	}
	res += "!)";
	return res;
}

// LongestPalindromicSubstr.size() = max{R[i] - 1}
std::vector<int> manacher(const std::string &s) {
	int n = (int) s.size();

	std::vector<int> R(n);
	int p = -1, mx = -1;
	for (int i = 0; i < n; ++i) {
		if (i <= mx) R[i] = std::min(mx - i + 1, R[2 * p - i]);
		else R[i] = 1;
		while (i - R[i] >= 0 && i + R[i] < n && s[i - R[i]] == s[i + R[i]])
			++R[i];
		if (i + R[i] - 1 > mx)
			p = i, mx = i + R[i] - 1;
	}

	return R;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;
	s = adjust(s);
	auto R = manacher(s);

	// std::cerr << s << '\n' << R << '\n';

	int n = int(s.size());
	ST.build(1, 0, n - 1);
	int ans = 0;
	for (int i = 2; i < n - 2; ++i) {
		int j = ST.query(1, i - R[i], n - 1);
		if (isalpha(s[i]) || R[i] > 1) {
			// std::cerr << i << " " << j << '\n';
			ans = std::max(ans, i - j);
		}
		ST.modify(1, i + R[i] - 1, i);
	}
	std::cout << ans << '\n';
	
	return 0;
}