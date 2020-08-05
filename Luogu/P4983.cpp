#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;

const int N = 1e5 + 10;
ll a[N], s[N], dp[N];
int n, m;

inline db X(int i) { return s[i] - 1; }
inline db Y(int i) { return dp[i] + (s[i] - 1) * (s[i] - 1); }
inline db slope(int i, int j) {
	return (Y(j) - Y(i)) / (X(j) - X(i));
}

int calc(ll mid) {
	static int cnt[N], q[N];
	dp[0] = cnt[0] = 0;
	int *ql = q + 1, *qr = q;
	*++qr = 0;
	for (int i = 1; i <= n; ++i) {
		while (ql < qr && 2.0 * s[i] > slope(*ql, *(ql + 1))) ++ql;
		int j = *ql;
		dp[i] = dp[j] + (s[i] - s[j] + 1) * (s[i] - s[j] + 1) - mid;
		cnt[i] = cnt[j] + 1;
		while (ql < qr && slope(*(qr - 1), *qr) > slope(*(qr - 1), i)) --qr;
		*++qr = i;
	}
	return cnt[n];
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		s[i] = s[i - 1] + a[i];
	}
	ll l = -1e16, r = 0, p = 1;
	while (l <= r) {
		ll mid = (l + r) >> 1;
		if (calc(mid) <= m) l = mid + 1, p = mid;
		else r = mid - 1;
	}
	calc(p);
	printf("%lld\n", dp[n] + p * m);
	return  0;
}