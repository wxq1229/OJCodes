#include <bits/stdc++.h>

using namespace std;

const int mod = 104857601, N = 1000001;

bool vis[N];
int ps[78499], pn, phi[N];

void sieve() {
  int n = 1000000; phi[1] = 1;
  for (int i = 2; i <= n; i++)  {
    if (!vis[i]) ps[pn++] = i, phi[i] = i-1;
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { phi[i * ps[j]] = 1ll * phi[i] * ps[j] % (mod-1); break; }
      else phi[i * ps[j]] = 1ll * phi[i] * (ps[j]-1) % (mod-1);
    }
  }
  for (int i = 1; i <= n; i++) {
    phi[i] += phi[i-1];
    if (phi[i] >= mod-1) phi[i] -= mod-1;
  }
}

inline int sqr(int x) { return 1ll * x * x % mod; }

inline int fpow(int x, int y) {
  int ans = 1;
  for (; y; y>>=1, x = 1ll * x * x % mod)
    if (y & 1) ans = 1ll * ans * x % mod;
  return ans;
}

int solve(int n) {
  int ans = 1;
  for (int i = 1; i <= n; i++)
    ans = 1ll * ans * fpow(i, (2ll * phi[n/i] - 1) % (mod-1)) % mod;
  return ans;
}

int main() {
  sieve();
//  cout << pn << endl;
  int n, ans = 1;
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) ans = 1ll * ans * i % mod;
  ans = 1ll * fpow(ans, n<<1) * fpow(solve(n), mod - 3) % mod;
  printf("%d\n", ans);
  return 0;
}
