#include <bits/stdc++.h>
using namespace std;

const int all = (1<<8) - 1, N = 60010;
int n, a[N], s[N], k;
int dp[10][N], f[1<<9][1<<9];

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        s[i] = s[i - 1] ^ a[i];
    }    
    memset(dp, 0x3f, sizeof(dp));
    auto upd = [&](int x, int v) {
        int h = x >> 8;
        for (int i = 0; i <= all; ++i)
            f[h][i] = min(f[h][i], v + ((x & all) ^ i));
    };
    auto qry = [&](int x) {
        int ans = 0x3f3f3f3f;
        for (int i = 0; i <= all; ++i) {
            ans = min(ans, f[i][x & all] + (((x>>8) ^ i) << 8));
        }
        return ans;
    };
    for (int i = 1; i <= n; ++i) dp[1][i] = s[i];
    for (int j = 2; j <= k; ++j) {
        for (int h = 0; h <= all; ++h)
            for (int l = 0; l <= all; ++l) f[h][l] = 0x3f3f3f3f;
        for (int i = 1; i <= n; ++i) {
            if (i >= j) dp[j][i] = qry(s[i]);
            upd(s[i], dp[j - 1][i]);
        }
    }
    for (int i = k; i <= n; ++i) cout << dp[k][i] << (i == n ? "\n" : " ");
    return 0;
}