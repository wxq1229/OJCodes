#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5e3 + 10, P = 998244353;
void upd(int &x, int y) {
    x += y - P;
    x += x >> 31 & P;
}

int n, m;
int a[N][N], s[N];

int solve(int k) {
    vector<int> dp((n << 1) + 1);
    dp[n] = 1;
    for (int i = 1; i <= n; ++i) {
        vector<int> new_dp((n << 1) + 1);
        for (int j = 0; j <= n * 2; ++j) {
            upd(new_dp[j], dp[j]);
            upd(new_dp[j + 1], (ll) dp[j] * a[i][k] % P);
            if (j - 1 >= 0) upd(new_dp[j - 1], (ll) dp[j] * (s[i] - a[i][k] + P) % P);
        }
        swap(dp, new_dp);
    }
    int ans = 0;
    for (int i = n + 1; i <= n * 2; ++i)
        upd(ans, dp[i]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int all = 1;
    for (int i = 1; i <= n; ++i) {
        s[i] = 0;
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
            upd(s[i], a[i][j]);
        }
        all = (ll) all * (s[i] + 1) % P;
    }
    upd(all, P - 1);
    for (int i = 1; i <= m; ++i) upd(all, P - solve(i));
    cout << all << '\n';
    return 0;
}