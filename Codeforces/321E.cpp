#include <bits/stdc++.h>
using namespace std;

inline char nc() {
  const int SZ = 1 << 20;
  static char buf[SZ], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SZ, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T> inline T rd() {
  T x = 0; char ch = nc(); bool f = 1;
  while (!isdigit(ch)) { f ^= ch == '-'; ch = nc(); }
  while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = nc(); }
  return f ? x : -x;
}
#define gi rd<int>

const int N = 4010, inf = 0x3f3f3f3f;
int a[N][N], s[N][N], n, k;

int weight(int l, int r) {
    assert((s[r][r] - s[l - 1][r] - s[r][l - 1] + s[l - 1][l - 1]) % 2 == 0);
    return (s[r][r] - s[l - 1][r] - s[r][l - 1] + s[l - 1][l - 1]) >> 1;
}

void solve(vector<int> &new_dp, const vector<int> &dp, int l, int r, int pl, int pr) {
    // cerr << l << " " << r << ", " << pl << " " << pr << '\n';
    if (l > r || pl > pr) return;
    if (pl == pr) {
        for (int i = l; i <= r; ++i)
            new_dp[i] = dp[pl - 1] + weight(pl, i);
        return;
    }
    int mid = (l + r) >> 1;
    int pmid = -1, ans = inf * 2;
    for (int i = pl; i <= min(mid, pr); ++i)
        if (dp[i - 1] + weight(i, mid) < ans) {
            ans = dp[i - 1] + weight(i, mid);
            pmid = i;
        }
    new_dp[mid] = ans;
    solve(new_dp, dp, l, mid - 1, pl, pmid);
    solve(new_dp, dp, mid + 1, r, pmid, pr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    n = gi(), k = gi();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            a[i][j] = gi();
        }
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            s[i][j] = s[i - 1][j] + s[i][j - 1] + a[i][j] - s[i - 1][j - 1];
    vector<int> dp(n + 1, inf);
    dp[0] = 0;
    for (int i = 1; i <= k; ++i) {
        vector<int> new_dp(n + 1, inf);
        solve(new_dp, dp, 1, n, 1, n);
        for (int j = 0; j < i; ++j)
            new_dp[j] = inf;
        swap(dp, new_dp);
    }
    cout << dp[n] << '\n';
    return 0;
}