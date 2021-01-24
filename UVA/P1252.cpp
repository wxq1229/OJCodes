#include <bits/stdc++.h>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	while (std::cin >> m >> n && n && m) {
		std::vector<int> a(n);
		for (int i = 0; i < n; ++i) {
			std::string foo;
			std::cin >> foo;
			for (int j = 0; j < m; ++j)
				if (foo[j] == '1') a[i] |= 1 << j;
		}
		
		constexpr int INF = 0x3f3f3f3f;
		std::vector<std::vector<int>> dp(1 << m, std::vector<int>(1 << m, INF));
		for (int S = 0; S < (1 << m); ++S) {
			for (int T = S; ; T = (T - 1) & S) {
				int cnt = 0;
				for (int i = 0; i < n; ++i)
					if ((a[i] | T) == a[i] && (a[i] & (S ^ T)) == 0) { ++cnt; }
				if (cnt == 1) dp[S][T] = 0;
				if (cnt == 0) dp[S][T] = INF >> 1;
				if (T == 0) break;
			}
		}

		std::function<int(int, int)> DP = [&](int S, int T) {
			int &ans = dp[S][T];
			if (ans < INF) return ans;
			for (int i = 0; i < m; ++i) if (!(S >> i & 1)) {
				int ndp1 = DP(S | (1 << i), T | (1 << i)) + 1;
				int ndp2 = DP(S | (1 << i), T) + 1;
				ans = std::min(ans, std::max(ndp1, ndp2));
			}
			return ans;
		};

		std::cout << DP(0, 0) << '\n';
	}
	
	return 0;
}