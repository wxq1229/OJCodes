#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6 + 10, maxn = 1e6;

ll md;

inline ll add(ll a, ll b) {
  a += b;
  if (a >= md) {
    a -= md;
  }
  return a;
}
inline ll sub(ll a, ll b) { return add(a, md - b); }
inline ll mul(ll a, ll b) {
  ll ans = 0;
  while (b) {
    if (b & 1) ans = add(ans, a);
    a = add(a, a), b >>= 1;
  }
  return ans;
}
inline ll qpow(ll a, ll b) {
  ll ans = 1 % md;
  while (b) {
    if (b & 1) ans = mul(ans, a);
    a = mul(a, a), b >>= 1;
  }
  return ans;
}

bool vis[N];
int ps[N], pn, pn_saved;
void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ps[++pn] = i;
    }
    for (int j = 1; j <= pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) {
        break;
      }
    }
  }
  pn_saved = pn;
}

ll n, val[N], g[N];
int rid[2][N], tot, sqn;

inline int id(ll v) {
//  cerr << "ID of " << v << '\n'; 
  if (v <= sqn) {
    assert(rid[0][v]);
    return rid[0][v];
  } else {
    assert(rid[1][n / v]);
    return rid[1][n / v];
  }
}

void init() {
  sqn = (int) sqrt(n);
  tot = 0;
  for (ll l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    ll v = n / l;
//    cerr << "V: " << v << '\n';
    val[++tot] = v;
    if (v <= sqn) rid[0][v] = tot;
    else rid[1][n / v] = tot;
    g[tot] = v - 1;
  }
//  cerr << "sqrt(" << n << ") = " << sqn << '\n';
  pn = upper_bound(ps + 1, ps + pn_saved + 1, sqn) - 1 - ps;
  for (int k = 1; k <= pn; k++) {
    for (int i = 1; i <= tot && (ll) ps[k] * ps[k] <= val[i]; i++) {
      int j = id(val[i] / ps[k]);      
      g[i] -= g[j] - k + 1;
    }
  }
}

void solve() {
  cin >> n >> md;
  init();
  ll ans = 1 % md;
  for (int i = 1; i <= pn; i++) {
    ll p = ps[i], tmp = 1;
    while (p <= n) tmp = add(tmp, n / p), p *= ps[i];
    ans = mul(ans, tmp);
  }
//  cerr << ans << '\n';        	         
  for (ll l = sqn + 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
//    cerr << l << " " << r << '\n';
    ans = mul(ans, qpow((n / l + 1) % md, g[id(r)] - (l - 1 == sqn ? pn : g[id(l - 1)])));
  }
  cout << ans << '\n';
}

int main() {
#ifdef LOCAL
  double STIME = clock();
#endif
  sieve(maxn);
  int tt;
  cin >> tt;
  while (tt--) solve();
#ifdef LOCAL
  cerr << "Time used: " << clock() - STIME << '\n';
#endif
  return 0;
}