#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline ll read() {
	char ch; ll x = 0; int f = 1; while (!isdigit(ch = getchar())) f = ch=='-' ? -f : f;
	while (isdigit(ch)){ x = x*10 + ch - '0'; ch = getchar(); } return x * f;
}

const int P = 998244353, i2 = 499122177, i6 = 166374059;
void update(ll &x, ll y) {
	x += y; if (x >= P) x -= P;
}
inline ll s1(ll n) {
	n %= P; return n % P * (n+1) % P * i2 % P;
}
inline ll s2(ll n) {
	n %= P; return n % P * (n+1) % P * (2ll*n%P + 1) % P * i6 % P;
}
inline ll sqr(ll x) {
	return 1ll * x * x % P;
}

void euclid(ll a, ll b, ll c, ll n, ll &f, ll &g, ll &h) {
	ll ac = a/c, bc = b/c, m = 1ll * (1ll*a*n + b) / c;
	if (!a) {
		f = 1ll * bc * (n + 1) % P, g = 1ll * bc * s1(n) % P;
		h = 1ll * sqr(bc) * (n + 1) % P;
		return;
	}
	ll f1, g1, h1;
	if (a >= c || b >= c) {
		euclid(a % c, b % c, c, n, f1, g1, h1);
		f = g = h = 0;
		update(f, 1ll * s1(n) * ac % P), update(f, 1ll * bc * (n+1) % P), update(f, f1);
		update(g, 1ll * s2(n) * ac % P), update(g, 1ll * s1(n) * bc % P), update(g, g1);
		update(h, 1ll * s2(n) * sqr(ac) % P), update(h, 1ll * (n+1) * sqr(bc) % P);
		update(h, h1), update(h, 2ll * ac * g1 % P);
		update(h, 1ll * n * (n+1) % P * ac % P * bc % P);
		update(h, 2ll * bc * f1 % P);
		return;
	}
	euclid(c, c-b-1, a, m-1, f1, g1, h1);
	f = g = h = 0;
	update(f, 1ll * n * m % P), update(f, P - 1ll * f1 % P);
	update(g, 1ll * n % P * (n+1) % P * m % P);
	update(g, P - 1ll * f1 % P), update(g, P - 1ll * h1 % P), g = g * i2 % P;
	update(h, 1ll * m * (m+1) % P * n % P), update(h, P - 2ll * g1 % P);
	update(h, P - 2ll * f1 % P), update(h, P - f);
}

int main(){
	for (int T = read(); T; T--) {
		ll n = read(), a = read(), b = read(), c = read(), f, g, h;
		euclid(a, b, c, n, f, g, h);
		printf("%lld %lld %lld\n", f, h, g);
	}
	return 0;
}










