#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10, LIM = 1e9;

int lc[N*80], rc[N*80], sum[N*80], cnt = 0, rt[N];

void ins(int pre,int &x,int l,int r,int p,int v) {
	x = ++cnt;
	lc[x] = lc[pre], rc[x] = rc[pre];
	sum[x] = sum[pre] + v;
	if (l == r) return;
	int mid = (l+r) >> 1;
	if (p<=mid) ins(lc[pre],lc[x],l,mid,p,v);
	else ins(rc[pre],rc[x],mid+1,r,p,v);
}
int qry(int x,int y,int l,int r,int ql,int qr) {
	if (r<ql || qr<l) return 0;
	if (ql<=l && r<=qr) return sum[y]-sum[x];
	int mid = (l+r) >> 1, ans = 0;
	if (ql<=mid) ans += qry(lc[x],lc[y],l,mid,ql,qr);
	if (mid<qr) ans += qry(rc[x],rc[y],mid+1,r,ql,qr);
	return ans;
}
void build(int &x,int l,int r) {
	x = ++cnt;
	sum[x] = lc[x] = rc[x] = 0;
	if (l == r) return;
	int mid = (l+r) >> 1;
	build(lc[x],l,mid);
	build(rc[x],mid+1,r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		int v;
		cin >> v;
		ins(rt[i-1], rt[i], 0, LIM, v, v);
	}
	int q;
	cin >> q;
	while (q--) {
		int l,r;
		cin >> l >> r;
		int cur_sum = 0, ans = 0;
		while (233) {
			int tmp = qry(rt[l-1], rt[r], 0, LIM, 0, ans+1);
			// cerr << ans << '\n';
			if (tmp > cur_sum) {
				ans += tmp - cur_sum;
				cur_sum = tmp;
			} else {
				break;
			}
		}
		cout << ans + 1 << '\n';
	}
	return 0;
}