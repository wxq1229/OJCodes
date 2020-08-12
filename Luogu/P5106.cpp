#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int P = 1e9 + 7, N = 1e6 + 10;

inline int mpow(int a, int b, int md = P) {
    int ans = 1;
    for (; b; b >>= 1, a = (ll) a * a % md)
        if (b & 1) ans = (ll) ans * a % md;
    return ans;
}

int ps[N], pn;
bool vis[N];
void sieve(int n) {
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) ps[++pn] = i;
        for (int j = 1; j <= pn && i * ps[j] <= n; ++j) {
            vis[i * ps[j]] = 1;
            if (i % ps[j] == 0) break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    sieve(n);
    int ans = 1, all = mpow(n, k, P - 1);
    for (int i = 1; i <= pn; ++i) {
        int p = ps[i];
        ans = (ll) ans * mpow(p - 1, (all - mpow(n - n / p, k, P - 1) + P - 1) % (P - 1)) % P;
    }
    for (int i = 1; i <= pn; ++i) {
        ll pw = ps[i];
        while (pw <= n) {
            int e = (all - mpow(n - n / pw, k, P - 1) + P - 1) % (P - 1);
            e -= (all - mpow(n - n / pw / ps[i], k, P - 1) + P - 1) % (P - 1);
            if (e < 0) e += P - 1;
            ans = (ll) ans * mpow(pw / ps[i], e) % P;
            pw *= ps[i];
        }
    }
    cout << ans << '\n';
    return 0;
}