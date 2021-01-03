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

	std::string s, t;
	std::cin >> s >> t;

	std::string str = s + "|" + t;

	std::vector<bool> inS((int) str.size()), inT((int) str.size());
	for (int i = 0; i < (int) s.size(); ++i)
		inS[i] = 1;
	for (int i = (int) s.size() + 1; i < (int) str.size(); ++i)
		inT[i] = 1;

	SuffixArray SA(str);

	// std::cerr << SA.height << '\n';

	auto chk = [&](int len) {
		bool foundS = 0, foundT = 0;
		for (int i = 0; i < SA.n; ++i) {
			if (SA.height[i] < len) {
				foundS = inS[SA.sa[i]], foundT = inT[SA.sa[i]];
				continue;
			}
			foundS |= inS[SA.sa[i]];
			foundT |= inT[SA.sa[i]];
			if (foundS && foundT) return true;
		}
		return false;
	};

	int lo = 0, hi = std::min((int) s.size(), (int) t.size()), ans = 0;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (chk(mid))
			ans = mid, lo = mid + 1;
		else hi = mid - 1;
	}

	std::cout << ans << '\n';

	return 0;
}