#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 1e6 + 10, P = 998244353;
int n, k, a[N];
int tot, val[N];

struct BIT {
	int bt[N];
	void upd(int x,int v) {
		while (x <= tot) {
			(bt[x] += v) %= P;
			x += x & -x;
		}
	}
	int qry(int x) {
		int ans = 0;
		while (x) {
			(ans += bt[x]) %= P;
			x -= x & -x;
		}
		return ans;
	}
} b0, b1;

int inv[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	inv[1] = 1;
	for (int i = 2; i <= n; ++i)
		inv[i] = (ll) inv[P % i] * (P - P / i) % P;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		val[++tot] = a[i];
	}
	sort(val+1, val+tot+1);
	tot = unique(val+1,val+tot+1) - val - 1;
	for (int i = 1; i <= n; ++i)
		a[i] = lower_bound(val + 1, val + tot + 1, a[i]) - val;
	queue<int> q;
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		while (q.size() && q.front() < i - k) {
			b0.upd(a[q.front()], P - 1);
			b1.upd(a[q.front()], P - val[a[q.front()]]);
			q.pop();
		}
		int cnt = b0.qry(a[i]), sum = b1.qry(a[i]);
		ans += (ll) ((ll) cnt * val[a[i]] % P - sum + P) * inv[(int) q.size()] % P;
		if (ans >= P) ans -= P;
		q.push(i);
		b0.upd(a[i], 1);
		b1.upd(a[i], val[a[i]]);
	}
	cout << (ans + val[a[1]]) % P << '\n';
	return 0;
}