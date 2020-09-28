#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;

const int P = 1e9 + 7, N = 1e6 + 10;
inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b>>=1, a = (ll)a*a%P)
		if (b & 1) ans = (ll)ans*a%P;
	return ans;
}

int fact[N], inv_fact[N];
db lg_fact[N];
void init(int n) {
	fact[0] = 1, lg_fact[0] = 0;
	for (int i = 1; i <= n; ++i) {
		fact[i] = (ll) fact[i - 1] * i % P;
		lg_fact[i] = lg_fact[i - 1] + log(i);
	}
	inv_fact[n] = mpow(fact[n], P - 2);
	for (int i = n - 1; i >= 0; --i) {
		inv_fact[i] = (ll) inv_fact[i + 1] * (i + 1) % P;
	}
}

db lg_C(int n, int k) {
	return lg_fact[n] - lg_fact[k] - lg_fact[n - k];
}
int C(int n, int k) {
	if (n < 0 || k > n) return 0;
	return (ll) fact[n] * inv_fact[k] % P * inv_fact[n - k] % P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, k;
	cin >> n >> k;
	init(n);
	struct node {
		int x, y;
		db lg;
		bool operator<(const node &o) const {
			return lg < o.lg;
		}
	};
	priority_queue<node> pq;
	for (int i = 0; i <= n; ++i)
		pq.push({n, i, lg_C(n, i)});
	int ans = 0;
	while (k--) {
		node u = pq.top();
		pq.pop();
		(ans += C(u.x, u.y)) %= P;
		pq.push({u.x - 1, u.y, lg_C(u.x-1, u.y)});
	}
	cout << ans << '\n';
	return 0;
}