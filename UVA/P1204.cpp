#include <bits/stdc++.h>

constexpr int N = 16;
int overlap[N][2][N][2];
int dp[1 << N][N][2];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	auto calc = [](const std::string &s, const std::string &t, bool flag = 0) {
		int n = int(s.size()), m = int(t.size());
		int pS = n - 1, pT = 0;
		std::string sufS = "", preT = "";
		int ans = 0;
		while (pS >= 0 && pT < m) {
			sufS = s[pS--] + sufS;
			preT = preT + t[pT++];
			if (sufS == preT && (!flag || (pS > 0 && pT < m - 1)))
				ans = std::max(ans, int(sufS.size()));
		}
		// std::cerr << "Overlap(" << s << ", " << t << ") = " << ans << '\n';
		return ans;
	};

	int n;
	while (std::cin >> n && n) {
		std::vector<std::array<std::string, 2>> foo(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> foo[i][0];
			foo[i][1] = foo[i][0];
			std::reverse(foo[i][1].begin(), foo[i][1].end());
		}
		std::sort(foo.begin(), foo.end(), [](const std::array<std::string, 2> &a, const std::array<std::string, 2> &b) {
			return a[0].size() > b[0].size();
		});
		std::vector<bool> flag(n);
		for (int i = 0; i < n; ++i) {
			flag[i] = false;
			for (int j = 0; j < i; ++j) {
				if (foo[j][0].find(foo[i][0]) != foo[j][0].npos || foo[j][0].find(foo[i][1]) != foo[j][0].npos) { 
					flag[i] = true;
					break; 
				}
			}
		}
		
		std::vector<std::array<std::string, 2>> str;
		str.reserve(n);
		for (int i = 0; i < n; ++i) if (!flag[i]) {
			str.push_back(foo[i]);
		}

		n = int(str.size());

		std::memset(overlap, -1, sizeof overlap);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) if (i != j) {
				for (int ki = 0; ki < 2; ++ki)
					for (int kj = 0; kj < 2; ++kj)
						overlap[i][ki][j][kj] = calc(str[i][ki], str[j][kj]);
			}
		}

		if (n == 1) {
			std::cout << int(str[0][0].size()) - calc(str[0][0], str[0][0], 1) << '\n';
			continue;
		}
		
		constexpr int INF = 0x3f3f3f3f;
		std::memset(dp, 0x3f, sizeof dp);
		dp[1][0][0] = int(str[0][0].size());

		for (int i = 0; i < (1 << n); ++i) {
			for (int j = 0; j < n; ++j) if (i >> j & 1) {
				for (int k = 0; k < 2; ++k) {
					const int v = dp[i][j][k];
					if (v >= INF) {
						continue;
					}
					for (int nj = 0; nj < n; ++nj) if (!(i >> nj & 1)) {
						int ni = i | (1 << nj);
						for (int nk = 0; nk < 2; ++nk) {
							int &ndp = dp[ni][nj][nk];
							ndp = std::min(ndp, v + int(str[nj][nk].size()) - overlap[j][k][nj][nk]);
						}
					}
				}
			}
		}

		const int ALL = (1 << n) - 1;
		int ans = INF;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < 2; ++j)
				ans = std::min(ans, dp[ALL][i][j] - overlap[i][j][0][0]);
		std::cout << ans << '\n';
	}
	
	return 0;
}