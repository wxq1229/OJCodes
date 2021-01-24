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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;
	int n = int(s.size());

	i64 ans = 0;
	for (int i = 1; i <= n; ++i)
		ans += i64(i) * (i - 1) / 2 + i64(i) * (i - 1);
	
	SuffixArray SA(s);
	std::vector<int> a(SA.height.begin() + 1, SA.height.end());
	// std::cerr << a << '\n';
	--n;

	std::vector<int> l(n), r(n);
	std::stack<int> stk;
	for (int i = 0; i < n; ++i) {
		while (stk.size() && a[stk.top()] > a[i])
			stk.pop();
		l[i] = stk.size() ? stk.top() : -1;
		stk.push(i);
	}
	while (stk.size()) stk.pop();
	for (int i = n - 1; i >= 0; --i) {
		while (stk.size() && a[stk.top()] >= a[i])
			stk.pop();
		r[i] = stk.size() ? stk.top() : n;
		stk.push(i);
	}
	// for (int i = 0; i < n; ++i) std::cerr << l[i] << " " << r[i] << '\n';
	for (int i = 0; i < n; ++i) {
		++l[i];
		--r[i];
	}
	for (int i = 0; i < n; ++i) ans -= 2ll * a[i] * (i - l[i] + 1) * (r[i] - i + 1);
	std::cout << ans << '\n';
	return 0;
}