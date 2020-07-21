#include <bits/stdc++.h>

using namespace std;

const int N = 3010;
const int inf = 1e9;
int cost[N][N], s[N][N], x[N];

void solve(int *f, int *g, int l, int r, int pl, int pr) {
  if (l > r || pl > pr) {
    return;
  }   
  auto weight = [&](int i, int j) {
    return cost[i][j];
  };
  if (pl == pr) { 
    for (int i = l; i <= r; i++) {
      f[i] = g[pl - 1] + weight(pl, i);
    }
    return;
  }
  int mid = (l + r) >> 1;
  int pmid = -1;
  int mn = inf * 2;
  for (int i = pl; i <= min(mid, pr); i++) {
    if (g[i - 1] + weight(i, mid) < mn) {
      mn = g[i - 1] + weight(i, mid);
      pmid = i;
    }
  }
  f[mid] = mn;
  solve(f, g, l, mid - 1, pl, pmid);
  solve(f, g, mid + 1, r, pmid, pr);
}

int dp[N][N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> x[i];
  }   
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      s[i][j] = s[i][j - 1] + x[j];
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j++) {
      int mid = (i + j) >> 1;
      cost[i][j] = x[mid] * (mid - i + 1) - s[i][mid] + s[mid][j] - x[mid] * (j - mid + 1);
    }
  }             
  dp[1][0] = inf;
  for (int i = 1; i <= n; i++) {
    dp[1][i] = cost[1][i];
  }         
  for (int i = 2; i <= m; i++) {
    solve(dp[i], dp[i - 1], 1, n, 1, n);
    for (int j = 0; j < i; j++) {
      dp[i][j] = inf;
    } 
  }
  cout << dp[m][n] << '\n';
  return 0;
}