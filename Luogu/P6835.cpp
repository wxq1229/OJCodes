#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int P = 998244353;
inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = (ll) a * a % P)
		if (b & 1) ans = (ll) ans * a % P;
	return ans;
}

inline int add(int x, int y) {
	x += y;
	if (x >= P) x -= P;
	return x;
}
inline int sub(int x, int y) {
	x -= y;
	if (x < 0) x += P;
	return x;
}

struct line {
	int k, b;
	line operator+(const line &o) const {
		return {add(k, o.k), add(b, o.b)};
	}
	line operator-(const line &o) const {
		return {sub(k, o.k), sub(b, o.b)};
	}
	line operator*(const int &o) const {
		return {(ll) k * o % P, (ll) b * o % P};
	}
	line operator-(const int &o) const {
		return {k, sub(b, o)};
	}
	line operator+(const int &o) const {
		return {k, add(b, o)};
	}
};

const int N = 1e6 + 10;
vector<int> g[N];
int d[N];
line f[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int f__k, n, m;
	cin >> f__k >> n >> m;
	for (int i = 0; i < n; ++i)
		g[i].push_back(i + 1);
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		--u, --v;
		g[u].push_back(v);
		++d[u];
	}
	f[0] = {1, 0};
	for (int i = 0; i < n; ++i) {
		line tmp = f[i] * (d[i] + 1);
		for (auto j : g[i])
			tmp = tmp - f[j];
		tmp = tmp - d[i] - 1;
		f[i + 1] = tmp;
	}
	cout << (ll) (P - f[n].b) * mpow(f[n].k, P - 2) % P;
	return 0;
}