#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6 + 10;

bool vis[N];
int ps[N], pn;

void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ps[++pn] = i;
    }
    for (int j = 1; j <= pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) break;
    }
  }
}

ll n, val[N];
int rid[2][N], sqn, tot;

inline int id(ll v) {
  if (v <= sqn) return rid[0][v];
  else return rid[1][n / v];
}

ll g[N];

int main() {
#ifdef LOCAL
  double STIME = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  sqn = (int) sqrt(n);
  sieve(sqn);
  tot = 0;
  // cerr << pn << endl;
  for (ll l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    ll v = n / l;
    val[++tot] = v;
    if (v <= sqn) rid[0][v] = tot;
    else rid[1][n / v] = tot;
    g[tot] = v - 1;
  }
  for (int k = 1; k <= pn; k++) {
    for (int i = 1; i <= tot && 1ll * ps[k] * ps[k] <= val[i]; i++) {
      int j = id(val[i] / ps[k]);
      g[i] -= g[j] - k + 1;
    }
  }
  cout << g[id(n)] << endl;
#ifdef LOCAL
  cerr << "Time used: " << clock() - STIME << '\n';
#endif
  return 0;
}