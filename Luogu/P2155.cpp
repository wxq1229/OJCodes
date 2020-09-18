#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7 + 10;

int P;
inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = (ll) a * a % P)
		if (b & 1) ans = (ll) ans * a % P;
	return ans;
}

bool vis[N];
int ps[N], pn, pm[N], pm1[N];
int fac[N], ifac[N];
void sieve(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = (ll) fac[i - 1] * i % P;
	ifac[n] = mpow(fac[n], P - 2);
	for (int i = n - 1; i >= 0; --i)
		ifac[i] = (ll) ifac[i + 1] * (i + 1) % P;
	for (int i = 2; i <= n; ++i) {
		if (!vis[i]) ps[++pn] = i;
		for (int j = 1; j <= pn && i * ps[j] <= n; ++j) {
			vis[i * ps[j]] = 1;
			if (i % ps[j] == 0) break;
		}
	}
	pm[1] = pm1[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (vis[i]) pm[i] = pm[i - 1], pm1[i] = pm1[i - 1];
		else pm[i] = (ll) pm[i - 1] * i % P, pm1[i] = (ll) pm1[i - 1] * (i - 1) % P;
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	// n! * prod((p-1) / p)
	int ans = (ll) fac[n] * pm1[m] % P * mpow(pm[m], P - 2) % P;
	cout << ans << '\n';
}

int main() {
	int tt;
	cin >> tt >> P;
	sieve((int) 1e7); 
	while (tt--) solve();
	return 0;
}