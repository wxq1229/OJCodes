#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;

struct node {
	int l, r;
	int sum, tag;
} t[N<<2];

void pushup(int x) {
	t[x].sum = t[x<<1].sum + t[x<<1|1].sum;
}
void ptag(int x, int v) {
	t[x].tag = v;
	t[x].sum = v * (t[x].r - t[x].l + 1);
}
void pushdown(int x) {
	if (t[x].tag == -1) {
		return;
	}
	ptag(x<<1, t[x].tag);
	ptag(x<<1|1, t[x].tag);
	t[x].tag = -1;
}

int arr[N];
void build(int x,int l,int r) {
	t[x].l = l, t[x].r = r;
	t[x].sum = 0, t[x].tag = -1;
	if (l == r) {
		t[x].sum = arr[l];
		return;
	}
	int mid = (l+r) >> 1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void upd(int x,int ql,int qr,int v) {
	if (ql > qr) return;
	int l = t[x].l, r = t[x].r;
	if (ql<=l && r<=qr) {
		ptag(x, v);
		return;
	}
	pushdown(x);
	int mid = (l+r) >> 1;
	if (ql<=mid) upd(x<<1,ql,qr,v);
	if (mid<qr) upd(x<<1|1,ql,qr,v);
	pushup(x);
}
int qry(int x,int ql,int qr) {
	int l = t[x].l, r = t[x].r;
	if (ql<=l && r<=qr) return t[x].sum;
	pushdown(x);
	int mid = (l+r) >> 1, ans = 0;
	if (ql<=mid) ans += qry(x<<1,ql,qr);
	if (mid<qr) ans += qry(x<<1|1,ql,qr);
	return ans;
}

struct event {
	int op, l, r;
} events[N];
int a[N], n, m, pos;

bool check(int mid) {
	for (int i = 1; i <= n; ++i)
		arr[i] = a[i] >= mid;
	build(1,1,n);
	for (int i = 1; i <= m; ++i) {
		int op = events[i].op, l = events[i].l, r = events[i].r;
		int c1 = qry(1, l, r), c0 = r - l + 1 - c1;
		if (op == 0) {
			// cerr << l << ',' << l+c0-1 << " " << l+c0 << ',' << r << '\n';
			upd(1, l, l + c0 - 1, 0);
			upd(1, l + c0, r, 1);
		} else {
			// cerr << l << ',' << l+c1-1 << " " << l+c1 << ',' << r << '\n';
			upd(1, l, l + c1 - 1, 1);
			upd(1, l + c1, r, 0);
		}
	}
	return qry(1, pos, pos) == 1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 1; i <= m; ++i) {
		cin >> events[i].op >> events[i].l >> events[i].r;
	}
	cin >> pos;
	int lo = 1, hi = n, ans = -114514;
	while (lo <= hi) {
		// cerr << lo << " " << hi << '\n';
		int mid = (lo+hi) >> 1;
		if (check(mid)) {
			ans = mid;
			lo = mid + 1;
		}
		else hi = mid - 1;
	}
	cout << ans << '\n';
	return 0;
}