#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 6e5 + 10;

int n, m, q;
ll id[N * 13];
int lc[N * 13], rc[N * 13], siz[N * 13];
int rt[300010], cnt;

int calc(int rid, int l, int r) {
	int sz = 0, tot = rid <= n ? m - 1 : n;
	if (r <= tot) {
		sz = r - l + 1;
	} else if (l <= tot) {
		sz = tot - l + 1;
	} else {
		sz = 0;
	}
	return sz;
}

int newnode(int rid, int l, int r) {
	int x = ++cnt;
	lc[x] = rc[x] = 0;
	if (rid <= n) id[x] = (ll) (rid - 1) * m + l;
	else id[x] = (ll) l * m;
	int tot = rid <= n ? m - 1 : n;
	if (r <= tot) {
		siz[x] = r - l + 1;
	} else if (l <= tot) {
		siz[x] = tot - l + 1;
	} else {
		siz[x] = 0;
		id[x] = 0;
	}
	return x;
}

void mdf(int rid, int &x, int l, int r, int p, int v = -1, ll new_id = 0) {
	if (!x) x = newnode(rid, l, r);
	siz[x] += v;
	if (l == r) {
		id[x] = new_id;
		return;
	}
	int mid = (l + r) >> 1;
	if (p <= mid) mdf(rid, lc[x], l, mid, p, v, new_id);
	else mdf(rid, rc[x], mid + 1, r, p, v, new_id);
}

pair<int, ll> qry(int rid, int &x, int l, int r, int k) {
	if (!x) x = newnode(rid, l, r);
	if (l == r) return make_pair(l, id[x]);
	int mid = (l + r) >> 1;
	int ls = lc[x] ? siz[lc[x]] : calc(rid, l, mid);
	if (k <= ls) return qry(rid, lc[x], l, mid, k);
	else return qry(rid, rc[x], mid + 1, r, k - ls);
}

int lst[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> q;
	int lim = max(n, m) + q;
	for (int i = 1; i <= n; ++i)
		lst[i] = m - 1;
	lst[n + 1] = n;
	for (int i = 1; i <= n + 1; ++i)
		rt[i] = newnode(i, 1, lim);
	while (q--) {
		int x, y;
		cin >> x >> y;
		if (y < m) {
			auto ans = qry(x, rt[x], 1, lim, y);
			cout << ans.second << '\n';
			mdf(x, rt[x], 1, lim, ans.first);
			auto tmp = qry(n + 1, rt[n + 1], 1, lim, x);
			mdf(x, rt[x], 1, lim, ++lst[x], 1, tmp.second);
			mdf(n + 1, rt[n + 1], 1, lim, tmp.first);
			mdf(n + 1, rt[n + 1], 1, lim, ++lst[n + 1], 1, ans.second);
		} else {
			auto ans = qry(n + 1, rt[n + 1], 1, lim, x);
			cout << ans.second << '\n';
			mdf(n + 1, rt[n + 1], 1, lim, ans.first);
			mdf(n + 1, rt[n + 1], 1, lim, lst[n + 1] + 1, 1, ans.second);
			++lst[n + 1];
		}
	}
	return 0;
}