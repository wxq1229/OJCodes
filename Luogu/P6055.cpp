#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod = 998244353;

ll mu[20000010];
int ps[20000010], pn = 0;
bool vis[20000010];

void sieve() {
  int n = 20000000; mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps[pn++] = i, mu[i] = -1;
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { mu[i * ps[j]] = 0; break; }
      else mu[i * ps[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= n; i++) mu[i] += mu[i-1];
  for (int i = 1; i <= n; i++) if (mu[i] < 0) mu[i] += mod;
}

map<int,int> musum;

int Smu(int n) {
  if (n <= 20000000) return mu[n];
  if (musum.count(n)) return musum[n];
  int ans = n >= 1;
  for (int l = 2, r = 0; l <= n; l = r+1) {
    r = n / (n / l);
    ans -= 1ll * Smu(n / l) * (r - l + 1) % mod;
    if (ans < 0) ans += mod;
  }
  return musum[n] = ans;
}

int ans, n;

int main() {
  sieve();
  scanf("%d", &n);
  for (int l = 1, r = 0; l <= n; l = r+1) {
    r = n / (n / l);
    ans += 1ll * (n/l) * (n/l) % mod * (n/l) % mod * (Smu(r) - Smu(l - 1) + mod) % mod;
    if (ans > mod) ans -= mod;
  }
  printf("%d\n", ans);
  return 0;
}
