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

using i64 = int64_t;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	const i64 INF = 2e18;	

	int n; std::string s;
	std::cin >> n >> s;
	std::vector<i64> a(n);
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	
	std::vector<i64> max = a, min = a, siz(n, 1);
	std::vector<int> fa(n); std::iota(fa.begin(), fa.end(), 0);
	std::function<int(int)> find = [&](int u) { return fa[u] == u ? u : fa[u] = find(fa[u]); };
	auto merge = [&](int u, int v) -> std::pair<i64, i64> {
		u = find(u), v = find(v);
		if (u == v) return std::make_pair(-INF, -1);
		i64 resMax = std::max(max[u] * max[v], min[u] * min[v]), resCnt = siz[u] * siz[v];
		max[u] = std::max(max[u], max[v]);
		min[u] = std::min(min[u], min[v]);
		fa[v] = u;
		siz[u] += siz[v];
		return std::make_pair(resMax, resCnt);
	};
	
	SuffixArray SA(s);
//	std::cerr << SA.height << '\n';
	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);
	std::sort(order.begin(), order.end(), [&](int i, int j) { return SA.height[i] > SA.height[j]; });
	
	std::vector<i64> resMax(n), resCnt(n);
	int ptr = 0;
	bool flg = 0;
	i64 curMax = -INF, curCnt = 0;
	for (int i = n - 1; i >= 0; --i) {
		while (ptr < n && SA.height[order[ptr]] >= i) {
			if (order[ptr] != 0) {
				auto p = merge(SA.sa[order[ptr]], SA.sa[order[ptr] - 1]);
				assert(p.second != -1);
				flg = 1;
				if (p.first > curMax) curMax = p.first;
				curCnt += p.second;
			}
			++ptr;
		}
		if (!flg) resMax[i] = resCnt[i] = 0;
		else resMax[i] = curMax, resCnt[i] = curCnt;
	}
	
	for (int i = 0; i < n; ++i)
		std::cout << resCnt[i] << " " << resMax[i] << '\n';
	
	return 0;
}