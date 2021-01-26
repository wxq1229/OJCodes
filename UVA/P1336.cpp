#include <bits/stdc++.h>
using db = double;

constexpr int N = 1111;

struct Wall {
	db x, c, k;

	bool operator<(const Wall &o) const { return x < o.x; }
} walls[N];
int n;
db v, x;
db dp[N][N][2], sum[N];

db calc(int i, int j) {
	return fabs(walls[i].x - walls[j].x) / v;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	while (std::cin >> n >> v >> x && n && x != 0 && v != 0) {
		db sumC = 0;
		for (int i = 1; i <= n; ++i) {
			std::cin >> walls[i].x >> walls[i].c >> walls[i].k;
			sumC += walls[i].c;
		}
		walls[++n] = {x, 0, 0};
		std::sort(walls + 1, walls + n + 1);
		for (int i = 1; i <= n; ++i) {
			sum[i] = sum[i - 1] + walls[i].k;
		}
		db allK = sum[n];
		int p = 0;
		for (int i = 1; i <= n; ++i){
			if (walls[i].x == x) {
				p = i;
				break;
			}
		}
		for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= n; ++j)
				dp[i][j][0] = dp[i][j][1] = 1e10;
		dp[p][p][0] = dp[p][p][1] = sumC;
		for (int len = 2; len <= n; ++len) {
			for (int i = 1; i + len - 1 <= n; ++i) {
				int j = i + len - 1;
				dp[i][j][0] = std::min(dp[i + 1][j][1] + (allK - (sum[j] - sum[i])) * calc(i, j),
										dp[i + 1][j][0] + (allK - (sum[j] - sum[i])) * calc(i, i + 1));
				dp[i][j][1] = std::min(dp[i][j - 1][0] + (allK - (sum[j - 1] - sum[i - 1])) * calc(i, j),
										dp[i][j - 1][1] + (allK - (sum[j - 1] - sum[i - 1])) * calc(j, j - 1));
			}
		}
		std::cout << int(std::min(dp[1][n][0], dp[1][n][1])) << '\n';
	}
	return 0;
}
