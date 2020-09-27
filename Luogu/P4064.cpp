#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using db = double;

const int N = 1e6 + 10;
int n, m, k, delta;
int a[N];

struct segment {
	int l, r;
} seg[N];
vector<int> seg_id[N];

bool check(int mid) {
	static int less[N], d[N];
	for (int i = 1; i <= n; ++i) {
		less[i] = 0;
		d[i] = 0;
		if (a[i] < mid)
			less[i] = ceil((db) mid - a[i]) / delta;
	}
	struct cmp {
		bool operator()(const segment &a, const segment &b) const {
			return a.r < b.r;
		}
	};
	priority_queue<segment, vector<segment>, cmp> pq;
	int cur = 0, cnt = 0;
	for (int i = 1; i <= n; ++i) {
		for (auto id : seg_id[i])
			pq.push(seg[id]);
		cur += d[i];
		int new_a = a[i] + cur;
		if (new_a >= mid) continue;
		while (new_a < mid && pq.size()) {
			segment sg = pq.top();
			pq.pop();
			if (sg.r >= i) {
				++cnt;
				cur += delta;
				new_a += delta;
				d[sg.l] += delta;
				d[sg.r+1] -= delta;
			}
		}
		if (new_a < mid) return false;
	}
	return cnt <= k;
}

void solve() {
	cin >> n >> m >> k >> delta;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		seg_id[i].clear();
	}
	for (int i = 1; i <= m; ++i) {
		cin >> seg[i].l >> seg[i].r;
		seg_id[seg[i].l].push_back(i);
	}
	int lo = *min_element(a+1, a+n+1), hi = lo + m * delta;
	int ans = -114514;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (check(mid)) {
			ans = mid;
			lo = mid + 1;
		}
		else hi = mid - 1;
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) solve();
	return 0;
}