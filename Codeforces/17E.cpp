#include <bits/stdc++.h>
using i64 = long long;

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

std::string adjust(const std::string &s) {
	std::string res = "(";
	for (auto ch : s) {
		res += "!";
		res += ch;
	}
	res += "!)";
    return res;
}

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

constexpr int P = 51123987;
template <typename T>
struct Fenwick {
	std::vector<T> a;
	int n;

	Fenwick(int _n = 0) {
		n = _n, a = std::vector<T>(n + 2); 
		for (int i = 0; i <= n; ++i) a[i] = 0; 
	}
	void upd(int x, T v) { for (++x; x <= n; x += x & -x) (a[x] += v) %= P; }
	T qry(int x) { T ans = 0; for (++x; x; x -= x & -x) (ans += a[x]) %= P; return ans; }

	void add(int l, int r, T v) {
		++r;
		l = std::max(0, l);
		upd(l, v);
		if (r < n) upd(r, P - v);
	}
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::string s;
	std::cin >> n >> s;

	s = adjust(s);
	int m = int(s.size());
	auto R = manacher(s);

	// std::cerr << "s = " << s << '\n';
	// std::cerr << "R = " << R << '\n';
	
	Fenwick<int> pre(m), suf(m);
	for (int i = 0; i < m; ++i) {
		pre.add(i, i + R[i] - 1, 1);
		suf.add(i - R[i] + 1, i, 1);
	}

	std::vector<int> cntPre, cntSuf;
	cntPre.reserve(n);
	cntSuf.reserve(n);
	for (int i = 2; i < m - 2; ++i) if (std::isalpha(s[i])) {
		cntPre.push_back(pre.qry(i));
		cntSuf.push_back(suf.qry(i));
	}

	std::vector<int> sufCnt(n);
	for (int i = n - 1; i >= 0; --i) {
		if (i < n - 1) sufCnt[i] = sufCnt[i + 1];
		(sufCnt[i] += cntSuf[i]) %= P;
	}

	int ans = 0;
	for (int i = 0; i < n - 1; ++i) {
		ans += i64(cntPre[i]) * sufCnt[i + 1] % P;
		if (ans >= P) ans -= P;
	}

	int all = 0;
	for (int i = 0; i < n; ++i)
		(all += cntPre[i]) %= P;
	all = i64(all) * (all - 1) % P * ((P + 1) / 2) % P;
	std::cout << (all - ans + P) % P << '\n';
	return 0;
}