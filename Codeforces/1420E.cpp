#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	vector<int> pos;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		if (a[i] == 1) {
			pos.push_back(i);
		}
	}
	int c1 = (int) pos.size(), c0 = n - c1, all = c0 * (c0 - 1) / 2;
	const int INF = 0x3f3f3f3f;
	vector<vector<vector<int>>> dp(1, vector<vector<int>>(1, vector<int>(1, 0)));
	for (int i = 0; i < n; ++i) {
		int lim = min((i + 1) * (n - 1) + 1, n * (n - 1) / 2 + 1);
		vector<vector<vector<int>>> new_dp(lim, vector<vector<int>>(i + 2, vector<int>(i + 2, INF)));
		for (int t = 0; t <= i * (n - 1) && t <= n * (n - 1) / 2; ++t) {
			int limc = min(c1, i);
			int liml = min(c0, i);
			for (int c = 0; c <= limc; ++c) {
				for (int l = 0; l <= liml; ++l) {
					if (dp[t][c][l] >= INF) {
						continue;
					}
					if (c + 1 <= c1 && t + abs(i - pos[c]) < lim) {
						new_dp[t + abs(i - pos[c])][c + 1][0] = min(new_dp[t + abs(i - pos[c])][c + 1][0], dp[t][c][l]);
					}
					if (l + 1 <= c0) {
						new_dp[t][c][l + 1] = min(new_dp[t][c][l + 1], dp[t][c][l] + l);
					}
				}
			}
		}
		swap(dp, new_dp);
	}
	vector<int> delta(n * (n - 1) / 2 + 1);
	for (int i = 0; i <= n * (n - 1) / 2; ++i) {
		int ans = INF;
		for (int l = 0; l <= c0; ++l) {
			ans = min(ans, dp[i][c1][l]);
		}
		delta[i] = ans;
	}
	for (int i = 1; i <= n * (n - 1) / 2; ++i)
		delta[i] = min(delta[i], delta[i - 1]);
	for (int i = 0; i <= n * (n - 1) / 2; ++i) {
		cout << all - delta[i] << " ";
	}
	return 0;
}