#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int P = 1e9 + 7;

int dp[20][2][2][20];
bool vis[20][2][2][20];
int qd, dig[20], len;

int dfs(int pos, bool up, bool zero, int tot) {
	if (!pos) return tot;
	if (vis[pos][up][zero][tot])
		return dp[pos][up][zero][tot];
	vis[pos][up][zero][tot] = 1;
	int &ans = dp[pos][up][zero][tot];
	ans = 0;
	int lim = up ? dig[pos] : 9;
	for (int i = 0; i <= lim; ++i)
		(ans += dfs(pos - 1, up && i == dig[pos], zero && i == 0, tot + (i == qd && (i || !zero)))) %= P;
	return ans;
}

vector<int> qry(ll n) {
	len = 0;
	while (n) dig[++len] = n % 10, n /= 10;
	vector<int> ans(10);
	for (int i = 0; i < 10; ++i) {
		memset(vis,0,sizeof(vis));
		qd = i;
		ans[i] = dfs(len, 1, 1, 0);
	}
	return ans;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		ll l, r;
		cin >> l >> r;
		vector<int> x = qry(l - 1), y = qry(r);
		int ans = 0;
		for (int i = 0; i < 10; ++i) {
			(ans += (ll) i * (y[i]-x[i]+P) % P) %= P;
		}
		cout << ans << '\n';
	}
	return 0;
}