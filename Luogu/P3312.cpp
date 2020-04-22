#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e5 + 10, maxn = 100000;

ll sigma[N], low[N], mu[N];
int ps[N], pn;
bool vis[N];

void sieve(int n) {
  sigma[1] = low[1] = mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps[pn++] = i, mu[i] = -1, low[i] = sigma[i] = i + 1;
    for (int j = 0; j < pn && i*ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) {
        mu[i * ps[j]] = 0;
        low[i * ps[j]] = low[i] * ps[j] + 1;
        sigma[i * ps[j]] = sigma[i] / low[i] * low[i * ps[j]];
        break;
      }
      else {
        low[i*ps[j]] = ps[j] + 1, sigma[i*ps[j]] = sigma[i] * (ps[j] + 1);
        mu[i *ps[j]] = -mu[i];
      }
    }
  }
}

struct BIT {
  ll c[N]; int n;
  inline void init(int sz) {
    n = sz;
    for (int i = 0; i <= n; i++) c[i] = 0;
  }
  inline void upd(int x, ll v = 1) {
    for (; x <= n; x += x & -x) c[x] += v;
  }
  inline ll qwq(int x) {
    ll ans = 0;
    for (; x; x -= x & -x) ans += c[x];
    return ans;
  }
  inline ll qry(int l, int r) { return qwq(r) - qwq(l-1); }
} bt;

void upd(int x) {
  for (int i = x; i <= maxn; i += x)
    bt.upd(i, sigma[x] * mu[i/x]);
}
ll qry(int l, int r) { return bt.qry(l,r); }

struct Query {
  int n, m, k, id;
  bool operator < (Query o) const { return k < o.k; }
} q[N];

int p[N];
bool cmp(int i, int j) { return sigma[i] < sigma[j]; }

ll solve(int n, int m) {
  int tn = min(n,m); ll ans = 0;
  for (int l = 1, r = 0; l <= tn; l = r+1) {
    r = min(n / (n/l), m / (m/l));
    ans += qry(l,r) * (n/l) * (m/l);
  }
  return ans;
}

ll ans[N];

int main() {
  sieve(maxn), bt.init(maxn);
  int T; scanf("%d", &T);
  for (int i = 1; i <= T; i++) scanf("%d%d%d", &q[i].n, &q[i].m, &q[i].k), q[i].id = i;
  sort(q + 1, q + T + 1);
  for (int i = 1; i <= maxn; i++) p[i] = i;
  sort(p + 1, p + maxn + 1, cmp);
  for (int i = 1, j = 1; i <= T; i++) {
    while (j <= maxn && sigma[p[j]] <= q[i].k) {
      upd(p[j]); j++;
    }
    ans[q[i].id] = solve(q[i].n, q[i].m);
  }
  for (int i = 1; i <= T; i++) printf("%lld\n", ans[i] & ((1<<31) - 1));
  return 0;
}
