#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

const int N = 1e6 + 10;
int n, m, c, k;
ull a[N];
vector<int> g[111];
bitset<100000000> vis;
bool flg[111];

int main() {
	scanf("%d%d%d%d", &n, &m, &c, &k);
	for (int i = 1; i <= n; ++i)
		scanf("%llu", &a[i]);
	for (int i = 1; i <= m; ++i) {
		int p, q;
		cin >> p >> q;
		g[p].push_back(q);
	}
	// ull st = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < k; ++j)
			if (a[i] & (1ull << j)) flg[j] = 1;
	}
	for (int i = 0; i < k; ++i) if (flg[i]) {
		for (int j = 0; j < (int) g[i].size(); ++j) {
			int x = g[i][j];
			vis[x - 1] = 1;
		}
	}
	int cnt = 0;
	for (int i = 0; i < k; ++i) {
		bool ok = true;
		for (int j = 0; j < (int) g[i].size(); ++j) {
			int x = g[i][j];
			if (!vis[x - 1]) {
				ok = false;
				break;
			}
		}
		cnt += ok;
	}
	ull ans = 0;
	if (cnt == 64) {
		if (n == 0) {
			puts("18446744073709551616");
			return 0;
		}
		ans = (1ull<<63) - n + (1ull<<63);
	} else ans = (1ull<<cnt) - n;
	printf("%llu\n", ans);
	return 0;
}