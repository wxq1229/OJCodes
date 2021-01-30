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

struct SuffixArray {
	static constexpr int SIGMA = 555;
	
	int n;
	std::vector<int> sa, rk, height;

	/*
	 * height[i] = LCP(suffix(sa[i]), suffix(sa[i - 1]))
	 * height[0] = 0
	 */

	SuffixArray(const std::string &s) {
		n = (int) s.size();
		sa = std::vector<int>(n);
		rk = std::vector<int>(n);
		{
			std::vector<int> cnt(SIGMA);
			for (int i = 0; i < n; ++i)
				++cnt[s[i]];
			for (int i = 1; i < SIGMA; ++i)
				cnt[i] += cnt[i - 1];
			for (int i = 0; i < n; ++i) sa[--cnt[s[i]]] = i;
			rk[sa[0]] = 0;
			for (int i = 1; i < n; ++i) rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);				
		}

		for (int k = 1; k < n && rk[sa[n - 1]] != n - 1; k <<= 1) {
			std::vector<int> x(n), y(n);
			for (int i = 0; i < n; ++i) {
				x[i] = rk[i] + 1;
				if (i + k < n) y[i] = rk[i + k] + 1;
				else y[i] = 0;
			}

			std::vector<int> sb(n);
			{
				std::vector<int> cnt(n + 1);
				for (int i = 0; i < n; ++i) ++cnt[y[i]];
				for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
				for (int i = 0; i < n; ++i) sb[--cnt[y[i]]] = i;
			}
			{
				std::vector<int> cnt(n + 1);
				for (int i = 0; i < n; ++i) ++cnt[x[i]];
				for (int i = 1; i <= n; ++i) cnt[i] += cnt[i - 1];
				for (int i = n - 1; i >= 0; --i) sa[--cnt[x[sb[i]]]] = sb[i];
			}

			rk[sa[0]] = 0;
			for (int i = 1; i < n; ++i)
				rk[sa[i]] = rk[sa[i - 1]] + (x[sa[i]] != x[sa[i - 1]] || y[sa[i]] != y[sa[i - 1]]);
		}

		height = std::vector<int>(n);
		height[0] = 0;
		for (int i = 0, k = 0; i < n; ++i) {
			if (rk[i] == 0) continue;
			if (k > 0) --k;
			int j = sa[rk[i] - 1];
			while (i + k < n && j + k < n && s[i + k] == s[j + k])
				++k;
			height[rk[i]] = k;
		}
	}
};

template <typename T, typename Compare>
struct RangeQuery {
	Compare cmp;

	std::vector<std::vector<T>> mn;
	std::vector<int> lg;
	int n, lgn;

	RangeQuery(const std::vector<T> &a) {
		n = int(a.size());
		lgn = 0;
		while ((1 << lgn) <= n) ++lgn;

		lg = std::vector<int>(n + 1);
		lg[0] = -1;
		for (int i = 1; i <= n; ++i) lg[i] = lg[i >> 1] + 1;

		constexpr T v1 = std::numeric_limits<T>::max();
		constexpr T v2 = std::numeric_limits<T>::min();
		T v = cmp(v1, v2) ? v2 : v1;
				
		mn = std::vector<std::vector<T>>(lgn, std::vector<T>(n, v));
		for (int i = 0; i < n; ++i)
			mn[0][i] = a[i];
		
		for (int i = 1; i < lgn; ++i)
			for (int j = 0; j + (1 << i) - 1 < n; ++j) {
				T x = mn[i - 1][j];
				T y = mn[i - 1][j + (1 << (i - 1))];
				if (cmp(x, y)) mn[i][j] = x;
				else mn[i][j] = y;
			}
	}
	
	T query(int l, int r) {
		int k = lg[r - l + 1];
		T x = mn[k][l], y = mn[k][r - (1 << k) + 1];
		return cmp(x, y) ? x : y;
	}
};
template <typename T>
	using RangeMaxQuery = RangeQuery<T, std::greater<T>>;
template <typename T>
	using RangeMinQuery = RangeQuery<T, std::less<T>>;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	constexpr int MAXL = 200010;

	// std::cerr << "HI\n";
	int m, k;
	std::cin >> m >> k;
	std::vector<int> bel(MAXL, -1), at(MAXL, -1);
	std::vector<int> beg(m), sz(m);
	std::string s = "";
	for (int i = 0; i < m; ++i) {
		std::string foo;
		std::cin >> foo;
		sz[i] = int(foo.size());
		beg[i] = int(s.size());
		s += foo + "|";
		for (int j = beg[i]; j < (int) s.size() - 1; ++j)
			bel[j] = i, at[j] = j - beg[i];
	}
	int n = int(s.size());
	bel.resize(n);
	at.resize(n);

	SuffixArray SA(s);
	const auto &sa = SA.sa;
	const auto &height = SA.height;
	RangeMinQuery<int> rmqh(height);

	/*
	std::cerr << "s = " << s << '\n';
	std::cerr << "sa = " << sa << '\n';
	for (int i = 0; i < n; ++i) {
		for (int j = sa[i]; j < n; ++j)
			std::cerr << s[j];
		std::cerr << '\n';
	}
	*/

	std::vector<int> p(n, n + 1);
	std::vector<int> cnt(m);
	for (int i = 0, j = 0, cur = 0; i < n; ++i) {
		while (cur < k && j < n) {
			if (bel[sa[j]] != -1) {
				cur += cnt[bel[sa[j]]] == 0;
				++cnt[bel[sa[j]]];
			}
			++j;
		}
		if (cur == k)
			p[i] = j - 1;
		if (bel[sa[i]] != -1) {
			cur -= cnt[bel[sa[i]]] == 1;
			--cnt[bel[sa[i]]];
		}
	}
	// std::cerr << p << '\n';
	RangeMinQuery<int> rmqp(p);

	std::vector<i64> ans(m);

	for (int i = 0; i < n; ++i) if (bel[sa[i]] != -1) {
		auto check = [&](int len) {
			int pL = i, pR = i;
			{
				int lo = 0, hi = i - 1;
				while (lo <= hi) {
					int mid = (lo + hi) >> 1;
					if (rmqh.query(mid + 1, i) >= len)
						hi = mid - 1, pL = mid;
					else lo = mid + 1;
				}
			}
			{
				int lo = i + 1, hi = n - 1;
				while (lo <= hi) {
					int mid = (lo + hi) >> 1;
					if (rmqh.query(i + 1, mid) >= len)
						lo = mid + 1, pR = mid;
					else hi = mid - 1;
				}
			}
			return rmqp.query(pL, pR)  <= pR;
		};

		int lo = 0, hi = sz[bel[sa[i]]] - at[sa[i]], len = 0;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) len = mid, lo = mid + 1;
			else hi = mid - 1;
		}

		ans[bel[sa[i]]] += len;
		// std::cerr << "    ans[" << bel[sa[i]] << "] += " << len << '\n';
	}
	for (int i = 0; i < m; ++i)
		std::cout << ans[i] << " ";
	return 0;
}