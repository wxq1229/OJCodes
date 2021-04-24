#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 13, M = 510;
int n, m, a[N];
i64 dp[1 << N][N][M];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];
	int first = std::max_element(a, a + n) - a;	
	
	for (int i = 0; i < n; ++i) {
		int more = 0;
		if (a[i] > a[first]) more = 0;
		else more = a[first] - a[i] + (i > first);
		if (more * n <= m) dp[1 << i][i][more * n] = 1;
	}
	for (int S = 0; S < (1 << n) - 1; ++S) {
		int left = n - __builtin_popcount(S);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j <= m; ++j) if (dp[S][i][j] != 0) {
				for (int ni = 0; ni < n; ++ni) if (!(S >> ni & 1)) {
					int more = 0;
					if (a[ni] > a[i]) more = 0;
					else more = a[i] - a[ni] + (ni > i);
					int nj = left * more + j;
					if (nj <= m) dp[S | (1 << ni)][ni][nj] += dp[S][i][j];
				}
			}
		}
	}

	i64 ans = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= m; ++j)
			ans += dp[(1 << n) - 1][i][j];
	std::cout << ans << '\n';
	
	return 0;
}