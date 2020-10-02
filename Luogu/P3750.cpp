#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int P = 100003;

inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = (ll) a * a % P)
		if (b & 1) ans = (ll) ans * a % P;
	return ans;
}

const int N = 1e5+10;
int a[N], n, k;
vector<int> d[N];
int dp[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	for (int i = 1; i <= n; ++i)
		for (int j = i; j <= n; j += i)
			d[j].push_back(i);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	int ans = 0;	
	for (int i = n; i >= 1; --i) if (a[i]) {
		++ans;
		for (auto j : d[i])
			a[j] ^= 1;
	}
	if (ans <= k) {
		for (int i = 1; i <= n; ++i)
			ans = (ll) ans * i % P;
		cout << ans << '\n';
	} else {
		dp[n] = 1;
		for (int i = n - 1; i >= 0; --i)
			dp[i] = ((ll) n * mpow(i, P - 2) % P + (ll) (n - i) * mpow(i, P - 2) % P * dp[i + 1] % P) % P;
		int tmp = ans;
		ans = 0;
		for (int i = tmp; i > k; --i)
			(ans += dp[i]) %= P;
		(ans += k) %= P;
		for (int i = 1; i <= n; ++i)
			ans = (ll) ans * i % P;
		cout << ans << '\n';
	}
	return 0;
}