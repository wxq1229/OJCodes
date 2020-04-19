#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 5e4 + 10;

bool vis[N];
int ps[N], pn, mu[N];
ll f[N];

inline ll sqr(ll x) { return 1ll * x * x; }

void sieve() {
  int n = 50000; mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps[pn++] = i, mu[i] = -1;
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { mu[i * ps[j]] = 0; break; }
      else mu[i * ps[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j+= i) f[j] += 1ll * i * mu[i];
}

int c[N], n;

int main() {
  sieve();
  scanf("%d", &n);
  for (int i = 1, x; i <= n; i++) scanf("%d", &x), c[x]++;
  n = 50000; ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll tmp = 0;
    for (int j = i; j <= n; j += i) tmp += 1ll * (j/i) * c[j];
    ans += sqr(tmp) * i * f[i];
//    cerr << i << ": " << f[i] << " " << sqr(tmp) << endl;
  }
  printf("%lld\n", ans);
  return 0;
}
