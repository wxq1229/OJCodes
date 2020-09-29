#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int P = 998244353, N = 5010;
inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = (ll) a * a % P)
		if (b & 1) ans = (ll) ans * a % P;
	return ans;
}

int fact[N], inv_fact[N];
void fact_init(int n) {
	fact[0] = 1;
	for (int i = 1; i <= n; ++i)
		fact[i] = (ll) fact[i - 1] * i % P;
	inv_fact[n] = mpow(fact[n], P - 2);
	for (int i = n - 1; i >= 0; --i)
		inv_fact[i] = (ll) inv_fact[i + 1] * (i + 1) % P;
}
int A(int n, int k) {
	return (ll) fact[n] * inv_fact[n - k] % P;
}

int main() {
	int n;
	cin >> n;
	fact_init(n);
	vector<vector<int>> p(n + 1, vector<int>(n + 1));
	p[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		p[i][0] = 1;
		for (int j = 1; j < i; ++j)
			p[i][j] = ((ll) (j + 1) * p[i-1][j] % P + (ll) (i - j) * p[i - 1][j - 1] % P) % P;
	}
	// for (int i = 0; i <= n; ++i, cerr << '\n')
		// for (int j = 0; j <= i; ++j)
			// cerr << p[i][j] << " ";
	vector<int> ans(n + 1);
	for (int i = 0; i < n; ++i) {
		for (int j = i == 0 ? 1 : i; j <= n; ++j)
			(ans[i] += (ll) A(n, n - j) * p[j][i] % P) %= P;
	}
	for (int i = 0; i < n; ++i)
		cout << ans[i] << " ";
	cout << '\n';
	return 0;
}