#include <bits/stdc++.h>
using namespace std;
using ll = long long;

inline char nc() {
    const int SZ = 1 << 20;
    static char buf[SZ], *p1 = buf, *p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SZ, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T> inline T rd() {
    T x = 0; char ch = nc(); bool f = 1;
    while (!isdigit(ch)) { f ^= ch == '-'; ch = nc(); }
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = nc(); }
    return f ? x : -x;
}
#define gi rd<int>
#define gl rd<ll>

const int N = 1e7 + 10;
ll a[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n = gi(), m = gi();
	for (int it = 0; it < m; ++it) {
		int l = gi(), r = gi();
		ll s = gl(), e = gl();
		ll k = (e - s) / (r - l);
		a[l] += s, a[l + 1] += k - s;
		a[r + 1] += -e-k, a[r + 2] += e;
	}
	for (int i = 1; i <= n; ++i) {
		a[i] += a[i - 1];
	}
	for (int i = 1; i <= n; ++i) {
		a[i] += a[i - 1];
	}
	ll xr = 0, mx = 0;
	for (int i = 1; i <= n; ++i) {
		mx = max(mx, a[i]);
		xr ^= a[i];
	}
	cout << xr << " " << mx << '\n';
	return 0;
}