#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e6+10;
int n, a[N];

namespace Gen {
	int a, b, c, d, mod;
	inline int sqr(int x) { return (ll)x*x%mod; }
	inline int F(int x) {return ((ll) a*sqr(x)%mod*x%mod + (ll) b*sqr(x)%mod + (ll) c*x%mod + (ll) d) % mod; }

	void init() {
		cin >> n >> a >> b >> c >> d >> ::a[1] >> mod;
		::a[0] = 0;
		for (int i = 2; i <= n; ++i)
			::a[i] = (F(::a[i - 1]) + F(::a[i - 2])) % mod;
	}
}

bool check(int mid) {
	static int l[N], r[N];
	for (int i = 1; i <= n; ++i) {
		r[i] = a[i] + mid;
		l[i] = max(1, a[i] - mid);
	}
	int lst = 0;
	for (int i = 1; i <= n; ++i) {
		if (r[i] < lst) return false;
		if (lst <= l[i]) lst = l[i];
	}
	return true;
}

int main() {
	Gen::init();
	// for (int i = 1; i <= n; ++i) {
		// cout << a[i] << " ";
	// }
	// cout << '\n';
	int lo = 0, hi = Gen::mod, ans = -1;
	while (lo <= hi) {
		int mid = (lo+hi) >> 1;
		if (check(mid)) {
			ans = mid;
			hi = mid-1;
		}
		else lo = mid + 1;
	}
	cout << ans << '\n';
	return 0;
}