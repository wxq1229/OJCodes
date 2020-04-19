#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6 + 10;

ll f[N], phi[N];
int ps[N], pn;
bool vis[N];

void sieve() {
  int n = 1000000; phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps[pn++] = i, phi[i] = i-1;
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { phi[i * ps[j]] = phi[i] * ps[j]; break; }
      else phi[i * ps[j]] = phi[i] * (ps[j]-1);
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j += i) f[j] += i == 1 ? 1 : phi[i] * i / 2;
}

int main() {
  sieve();
  int _; for (scanf("%d", &_); _; _--) {
    int n; scanf("%d", &n);
    printf("%lld\n", 1ll * n * f[n]);
  }
  return 0;
}
