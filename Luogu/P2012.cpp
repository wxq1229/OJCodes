#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int P = 1e9;
const int phi = (int) 4e8;

inline ll mpow(ll a,ll b) {
	if (b > 1e9) return mpow(a, b % phi + phi);
	ll ans = 1;
	for (; b; b>>=1, a = a*a%P)
		if (b&1) ans = ans*a%P;
	return ans;
}
inline ll power(ll a, ll b) {
	ll ans = 1;
	for (; b; b>>=1, a*=a)
		if (b&1) ans*=a;
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	ll n;
	while (scanf("%lld",&n) && n!=0) {
		if (n <= 4) {
			ll ans = power(-4, n) + power(4, n) * 6 - power(8, n) * 4 + power(12, n);
			ans /= 256;
			cout << (ans % P + P) % P << '\n';
		} else {
			ll ans = mpow(P - 4, n - 4) + mpow(4, n - 4) * 6 % P - mpow(2, n) * mpow(4, n - 3) % P + mpow(3, n) * mpow(4, n - 4) % P;
			ans = (ans % P + P) % P;
			cout << ans << '\n';
		}
	}
	return 0;
}
