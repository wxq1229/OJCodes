#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int P = 998244353, N = 1010;
int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = (ll) a * a % P)
		if (b & 1) ans = (ll) ans * a % P;
	return ans;
}
void upd(int &x,int y) {
	x += y;
	if (x >= P) x -= P;
}

int fac[N << 1], ifac[N << 1];
void fac_init(int n = 2000) {
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = (ll) fac[i - 1] * i % P;
	ifac[n] = mpow(fac[n], P - 2);
	for (int i = n - 1; i >= 0; --i)
		ifac[i] = (ll) ifac[i + 1] * (i + 1) % P;
}

int a[N], b[N];
int f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	fac_init();
	{
		const int n = 1000;
		for (int i = 0; i <= n; ++i) {
			a[i] = (ll) mpow(2,i) * ifac[i] % P;
			if (i & 1) a[i] = P - a[i];
		}
		for (int i = 0; i <= n; ++i) {
			b[i] = (ll) fac[i << 1] * ifac[i] % P * ifac[i] % P;
		}
		for (int i = 0; i <= n; ++i) {
			for (int j = 0; j <= i; ++j)
				upd(f[i], (ll) a[j] * b[i - j] % P);
		}
	}
	int tt;
	cin >> tt;
	while (tt--) {
		int n;
		cin >> n;
		int facn = (ll) fac[n] * fac[n] % P;
		for (int i = 0; i <= n; ++i) {
			int ans = (ll) f[n - i] * mpow(2,i) % P * facn % P * ifac[i] % P;
			cout << ans << '\n';
		}
	}
	return 0;
}