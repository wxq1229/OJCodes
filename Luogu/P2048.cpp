#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5e5 + 10;

int rt[N], lc[N * 32], rc[N * 32], sum[N * 32], cnt = 0;

void ins(int pre, int &x, int l, int r, int p, int v = 1) {
	x = ++cnt;
	lc[x] = lc[pre], rc[x] = rc[pre];
	sum[x] = sum[pre] + v;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (p <= mid) ins(lc[pre], lc[x], l, mid, p, v);
	else ins(rc[pre], rc[x], mid + 1, r, p, v);
}
int qry(int x, int y, int l, int r, int k) {
	if (l == r) return l;
	int mid = (l + r) >> 1, s = sum[lc[y]] - sum[lc[x]];
	if (k <= s) return qry(lc[x], lc[y], l, mid, k);
	else return qry(rc[x], rc[y], mid + 1, r, k - s);
}

int n, k, L, R;
int a[N], tot;
ll val[N], s[N];

struct node {
	int p, l, r, k;
	ll v;
	bool operator<(const node &o) const {
		return v < o.v;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k >> L >> R;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
		val[++tot] = s[i];
	}
	val[++tot] = 0;
	sort(val + 1, val + tot + 1);
	tot = unique(val + 1, val + tot + 1) - val - 1;
	for (int i = 0; i <= n; ++i)
		s[i] = lower_bound(val + 1, val + tot + 1, s[i]) - val;
	for (int i = 0; i <= n; ++i)
		ins(rt[i], rt[i + 1], 1, tot, s[i]);
	priority_queue<node> pq;
	for (int i = L; i <= n; ++i) {
		int l = i + 1 - R, r = i + 1 - L;
		l = max(1, l);
		ll ans = val[s[i]] - val[qry(rt[l - 1], rt[r], 1, tot, 1)];
		pq.push({i, l, r, 1, ans});
		// cerr << "push " << i << " " << l << " " << r << " " << 1 << " " << ans << '\n';
	}
	ll ans = 0;
	for (int it = 0; it < k; ++it) {
		node u = pq.top();
		pq.pop();
		// cerr << u.p << " " << u.l << " " << u.r << " " << u.k << " " << u.v << '\n';
		ans += u.v;
		if (u.k + 1 <= u.r - u.l + 1) {
			ll tmp = val[s[u.p]] - val[qry(rt[u.l - 1], rt[u.r], 1, tot, u.k + 1)];
			// cerr << "-> " << tmp << '\n';
			pq.push({u.p, u.l, u.r, u.k + 1, tmp});
		}
	}
	cout << ans << '\n';
	return 0;
}