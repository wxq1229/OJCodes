#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int maxn = 100000, N = maxn + 10;

ll f[N]; bool vis[N];
int ps[N], pn, mu[N];

void sieve(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps[pn++] = i, mu[i] = -1;
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { mu[i*ps[j]] = 0; break; }
      else mu[i*ps[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j += i) f[j] += 1ll * mu[j/i] * i;
  for (int i = 1; i <= n; i++) f[i] += f[i-1];
}

int main() {
  sieve(maxn);
  int n, m; scanf("%d%d", &n, &m);
  int tn = min(n,m); ll ans = 0;
  for (int l = 1, r = 0; l <= tn; l = r+1) {
    r = min(n / (n/l), m / (m/l));
    ans += 1ll * (n/l) * (m/l) * (f[r]-f[l-1]);
  }
  printf("%lld\n", 2ll * ans - 1ll * n * m);
  return 0;
}
