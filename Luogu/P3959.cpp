#include <bits/stdc++.h>

using namespace std;

string bin_string(int x) {
	string ans = "";
	while (x) ans = (char)((x & 1) + 48) + ans, x >>= 1;
	return ans;
}

typedef long long ll;
const int inf = (int) 1e9, SZ = (1 << 12) + 5;

ll dp[14][SZ], cost[SZ][SZ], g[15][15];
int n, m;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  memset(g, 0x3f, sizeof(g));     
  for (int i = 1; i <= m; i++) {
    int u, v; ll w;
    cin >> u >> v >> w;
    g[u][v] = min(g[u][v], w);
    g[v][u] = min(g[v][u], w);
  }
  const int ALL = (1 << n) - 1;
  for (int S = 1; S <= ALL; S++) {
    int U = ALL - S;
    for (int T = U; T; T = (T - 1) & U) {
      cost[S][T] = 0;
      vector<int> v_s, v_t;
      for (int i = 1; i <= n; i++) {
        if (S & (1 << (i - 1))) v_s.push_back(i);
        if (T & (1 << (i - 1))) v_t.push_back(i);
      }
      for (auto v : v_t) {
        ll tmp = inf;
        for (auto u : v_s) tmp = min(tmp, g[u][v]);
        cost[S][T] += tmp;
      }
      // cerr << "cost[" << bin_string(S) << "][" << bin_string(T) << "] = " << cost[S][T] << endl;
    }
  }
  memset(dp, 0x3f, sizeof(dp));
  for (int i = 1; i <= n; i++) dp[0][1 << (i - 1)] = 0;
  ll ans = dp[0][ALL];
  for (int i = 1; i < n; i++) {
    for (int S = 0; S <= ALL; S++) {
      for (int T = (S - 1) & S; T; T = (T - 1) & S) {
        int U = S - T;
        dp[i][S] = min(dp[i][S], dp[i - 1][T] + i * cost[T][U]);
      }
      // cerr << "dp[" << i << "][" << bin_string(S) << "] = " << dp[i][S] << endl;
    }
    ans = min(ans, dp[i][ALL]);
  }    
  cout << ans << '\n';
  return 0;
}
