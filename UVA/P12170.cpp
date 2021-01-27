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

constexpr i64 INF = i64(1e18);

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int tt;
	std::cin >> tt;
	while (tt--) {
		int n, d;
		std::cin >> n >> d;
		std::vector<i64> a(n);
		for (int i = 0; i < n; ++i)
			std::cin >> a[i];
		
		std::vector<i64> vals;
		for (int i = 0; i < n; ++i) {
			for (int j = -(n - 1); j <= (n - 1); ++j)
				vals.push_back(a[i] + j * d);
		}
		std::sort(vals.begin(), vals.end());
		vals.erase(std::unique(vals.begin(), vals.end()), vals.end());
		int m = int(vals.size());

		// std::cerr << "vals = " << vals << '\n';

		std::vector<i64> dp(m, INF);
		dp[std::lower_bound(vals.begin(), vals.end(), a[0]) - vals.begin()] = 0;
		for (int i = 1; i < n - 1; ++i) {
			// std::cerr << "i = " << i << '\n';
			std::vector<i64> ndp(m, INF);
			int cur = 0;
			std::deque<std::pair<i64, int>> que;
			
			auto push = [&](std::pair<i64, int> p) {
				// std::cerr << "Push " << p << '\n';
				while (que.size() && que.back().first >= p.first)
					que.pop_back();
				que.push_back(p);
			};

			for (int j = 0; j < m; ++j) {
				while (cur < m && llabs(vals[cur] - vals[j]) <= d) {
					push(std::make_pair(dp[cur], vals[cur]));
					++cur;
				}
				while (que.size() && llabs(que.front().second - vals[j]) > d)
					que.pop_front();
				if (que.size()) {
					ndp[j] = que.front().first + llabs(vals[j] - a[i]);
				}
			}

			std::swap(dp, ndp);
		}
		i64 ans = INF;
		for (int i = 0; i < m; ++i) {
			if (llabs(a[n - 1] - vals[i]) <= d) {
				ans = std::min(ans, dp[i]);
			}
		}
		if (ans < INF) std::cout << ans << '\n';
		else std::cout << "impossible\n";
	}
	
	return 0;
}