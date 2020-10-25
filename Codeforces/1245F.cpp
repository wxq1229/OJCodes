#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 31;
int bit[2][40];
bool vis[40][2][2];
ll f[40][2][2];

ll dp(int pos, int up0, int up1) {
	if (vis[pos][up0][up1]) {
		return f[pos][up0][up1];
	}
	ll &ans = f[pos][up0][up1];
	vis[pos][up0][up1] = 1;
	ans = 0;
	if (pos == 0) return ans = 1;
	int lim0 = up0 ? bit[0][pos] : 1;
	int lim1 = up1 ? bit[1][pos] : 1;
	for (int i = 0; i <= lim0; ++i)
		for (int j = 0; j <= lim1; ++j) {
			if (i & j) continue;
			ans += dp(pos - 1, up0 && i == bit[0][pos], up1 && j == bit[1][pos]);
		}
	return ans;
}

ll calc(ll n, ll m) {
	if (n < 0 || m < 0) return 0;
	memset(vis,0,sizeof(vis));
	for (int i = 0; i < N; ++i) {
		bit[0][i + 1] = n >> i & 1;
		bit[1][i + 1] = m >> i & 1;
	}
	// for (int i = N; i >= 1; --i)
	// 	cerr << bit[0][i] << " ";
	// cerr << '\n';
	// for (int i = N; i >= 1; --i)
	// 	cerr << bit[1][i] << " ";
	// cerr << '\n';
	return dp(N, 1, 1);
}

void solve() {
	ll l, r;
	cin >> l >> r;
	cout << calc(r, r) - 2ll * calc(l - 1, r) + calc(l - 1, l - 1) << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) solve();
	return 0;
}