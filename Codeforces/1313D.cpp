#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
using pii = pair<int, int>;
using vi = vector<int>;

string btos(int x) {
	string s = "";
	while (x) {
		s = (char) ((x & 1) + 48) + s;
		x >>= 1;
	}
	return s;
}

const int N = 1e5 + 10;

int n, m, k;
struct event {
	int pos, id;
	int type;

	bool operator<(const event &o) const {
		return pos < o.pos || (pos == o.pos && type < o.type);
	}
};
vector<event> events;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m >> k;
	for (int i = 1; i <= n; ++i) {
		int l, r;
		cin >> l >> r;
		events.pb({l, i, 1});
		events.pb({r + 1, i, -1});
	}
	sort(events.begin(), events.end());
	const int MAXS = 1 << 8, MAXK = 8, INF = 0x3f3f3f3f;
	vector<int> dp(MAXS, -INF);
	vector<int> id(MAXK);
	dp[0] = 0;
	auto chk = [](int x) -> bool {
		return __builtin_popcount(x) & 1;
	};
	for (int i = 0; i < (int) events.size(); ++i) {
		vector<int> new_dp(MAXS, -INF);
		int seg_id = -1;
		int len = 0;
		if (i == (int) events.size() - 1) {
			len = 0;
		} else {
			len = events[i + 1].pos - events[i].pos;
		}
		// cerr << "len = " << len << '\n';
		if (events[i].type == 1) {
			for (int j = 0; j < MAXK; ++j)
				if (!id[j]) {
					seg_id = j;
					id[j] = events[i].id;
					break;
				}
			assert(seg_id != -1);
			for (int j = 0; j < MAXS; ++j) {
				new_dp[j] = max(new_dp[j], dp[j] + len * chk(j));
				new_dp[j | (1 << seg_id)] = max(new_dp[j | (1 << seg_id)], dp[j] + len * chk(j | (1 << seg_id)));
			}
		} else {
			for (int j = 0; j < MAXK; ++j) {
				if (id[j] == events[i].id) {
					seg_id = j;
					id[j] = 0;
					break;
				}
			}
			assert(seg_id != -1);
			for (int j = 0; j < MAXS; ++j) {
				if (j & (1 << seg_id)) {
					new_dp[j ^ (1 << seg_id)] = max(new_dp[j ^ (1 << seg_id)], dp[j] + len * chk(j^(1<<seg_id)));
				} else {
					new_dp[j] = max(new_dp[j], dp[j] + len * chk(j));
				}
			}
		}
		swap(dp, new_dp);
		// for (int j = 0; j < 8; ++j) {
			// cerr << dp[j] << '\n';
		// }
	}
	cout << dp[0] << '\n';
	return 0;
}