#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef double db;

const int N = 3e5 + 10;
const db inf = 1e9;
ll c[N], t[N], sc[N], st[N], s;
int n;

ll dp[N];
inline db X(int i) { return sc[i]; }
inline db Y(int i) { return dp[i] + s * (sc[n] - sc[i]); }
inline db slope(int i, int j) {
    if (X(i) == X(j)) return Y(i) <= Y(j) ? inf : -inf;
    assert(X(i) < X(j));
    return (Y(j) - Y(i)) / (X(j) - X(i));
}

int q[N], ql, qr;
int getpos(int i) {
    db k = st[i];
    int l = ql, r = qr - 1, p = q[qr];
    while (l <= r) {
        int mid = (l+r) >> 1;
        if (slope(q[mid], q[mid+1]) >= k) r = mid - 1, p = q[mid];
        else l = mid + 1;
    }
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i] >> c[i];
        st[i] = st[i - 1] + t[i];
        sc[i] = sc[i - 1] + c[i];
    }
    for (int i = 1; i <= n; ++i) {
        int j = getpos(i);
        dp[i] = dp[j] + s * (sc[n]-sc[j]) + (sc[i]-sc[j])*st[i];
        while (ql < qr && slope(q[qr-1], q[qr]) >= slope(q[qr-1], i)) --qr;
        q[++qr] = i;
    }
    cout << dp[n] << '\n';
	return 0;
}