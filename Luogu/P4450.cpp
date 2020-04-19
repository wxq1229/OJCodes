#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e6 + 10;

int mu[N], ps[N], pn;
bool vis[N];

void sieve() {
  int n = 1000000; mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps[pn++] = i, mu[i] = -1;
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { mu[i * ps[j]] = 0; break; }
      else mu[i * ps[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= n; i++) mu[i] += mu[i-1];
}

ll S(int n, int m) {
  int tn = min(n, m); ll ans = 0;
  for (int l = 1, r = 0; l <= tn; l = r+1) {
    r = min(n/(n/l), m/(m/l));
    ans += 1ll * (mu[r] - mu[l-1]) * (n/l) * (m/l);
  }
  return ans;
}

int main() {
  sieve();
  int n, m, d; scanf("%d%d%d", &n, &m, &d);
  printf("%lld\n", S(n / d, m / d));
  return 0;
}
