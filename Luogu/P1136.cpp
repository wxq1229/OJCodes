#include <bits/stdc++.h>

constexpr int N = 555;
int mem[2][N][N][2];
#define dp mem[cur]
#define ndp mem[cur ^ 1]

int idx(char c) { return c == 'j' ? 0 : 1; }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, K;
	std::string s;
	std::cin >> n >> K >> s;
	
	int cur = 0;
	std::memset(dp, -1, sizeof dp);
	dp[0][0][idx(s[0])] = 0;
	dp[s[0] == 'j'][s[0] == 'z'][idx(s[0]) ^ 1] = 0;
	for (int i = 1; i < n; ++i) {
		std::memset(ndp, -1, sizeof ndp);
		// std::cerr << "i = " << i << '\n';
		for (int j = 0; j <= i && j <= K; ++j) {
			for (int k = 0; k + j <= i && k <= K; ++k) {
				for (int c = 0; c < 2; ++c) if (dp[j][k][c] != -1) {
					for (int nc = 0; nc < 2; ++nc) {
						int nj, nk;
						if (nc == idx(s[i])) nj = j, nk = k;
						else nj = j + (s[i] == 'j'), nk = k + (s[i] == 'z');
						// std::cerr << j << " " << k << " " << c << ": " << dp[j][k][c] << 
						// 			" + " << (c == 0 && nc == 1) << " -> " << nj << " " << nk << " " << nc << '\n';
						ndp[nj][nk][nc] = std::max(ndp[nj][nk][nc], dp[j][k][c] + (c == 0 && nc == 1));
					}					
				}
			}
		}
		cur ^= 1;
		// std::cerr << "---------------------------\n";
	}

	int ans = 0;
	for (int i = 0; i <= K; ++i)
		ans = std::max({ans, dp[i][i][0], dp[i][i][1]});
	std::cout << ans << '\n';

	return 0;
}