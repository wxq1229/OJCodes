#include <bits/stdc++.h>

using namespace std;

const int N = 5000010, mod = 1000000007;

inline int fpow(int x, int y) {
  int ans = 1; for (; y; y >>= 1, x = 1ll * x * x % mod)
    if (y & 1) ans = 1ll * ans * x % mod;
  return ans;
}

int K, ps[N], pn, f[N];
bool vis[N];

void sieve() {
  int n = 5000000; f[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ps[pn++] = i, f[i] = fpow(i, K) - 1;
      if (f[i] < 0) f[i] += mod;
    }
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      int ip = i * ps[j]; vis[ip] = 1;
      if (i % ps[j] == 0) {
        f[ip] = 1ll * f[i] * fpow(ps[j], K) % mod;
        break;
      }
      else f[ip] = 1ll * f[i] * f[ps[j]] % mod;
    }
  }
  for (int i = 1; i <= n; i++) {
    f[i] += f[i-1];
    if (f[i] >= mod) f[i] -= mod;
  }
}

int solve(int n, int m) {
  int tn = min(n,m), ans = 0;
  for (int l = 1, r = 0; l <= tn; l = r+1) {
    r = min(n / (n / l), m / (m / l));
    ans += 1ll * (n/l) * (m/l) % mod * (f[r] - f[l-1] + mod) % mod;
    if (ans >= mod) ans -= mod;
  }
  return ans;
}

int main() {
  int _; scanf("%d%d", &_, &K); sieve();
  while (_--) {
    int n, m; scanf("%d%d", &n, &m);
    printf("%d\n", solve(n, m));
  }
  return 0;
}
