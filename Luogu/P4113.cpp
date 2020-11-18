#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;

struct BIT {
	int n, a[N];

	void init(int _n = 0) {
		n = _n;
		for (int i = 0; i <= n; ++i)
			a[i] = 0;
	}
	
	void upd(int x, int v = 1) { for (; x <= n; x += x & -x) a[x] += v;	}
	int qry(int x) {
		int ans = 0;
		for (; x; x -= x & -x) ans += a[x];
		return ans;
	}
} bt;

int n, c, m, a[N];
int pre1[N], pre2[N], ans[N], cnt[N];
vector<pair<int, int>> qs[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> c >> m;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; ++i) {
		int l, r;
		cin >> l >> r;
		qs[r].push_back(make_pair(l, i));
	}
	bt.init(n);
	for (int i = 1; i <= n; ++i) {
		int col = a[i];
		++cnt[col];
		if (cnt[col] >= 2) {
			if (cnt[col] > 2) bt.upd(pre2[col], -1);
			bt.upd(pre1[col], 1);
		}
		pre2[col] = pre1[col];
		pre1[col] = i;
		for (auto q : qs[i]) {
			int l = q.first, r = i, id = q.second;
			ans[id] = bt.qry(r) - bt.qry(l - 1);
		}
	}
	for (int i = 1; i <= m; ++i) 
		cout << ans[i] << '\n';
	return 0;
}