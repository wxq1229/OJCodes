#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e7 + 10, mod = 998244353;

inline int fpow(int x, int y) {
  int ans = 1; for (; y; y>>=1, x = 1ll * x * x % mod)
    if (y & 1) ans = 1ll * ans * x % mod;
  return ans;
}

int ps[777777], pn, Sk[N], S[N], K, f[N];
bool vis[N];

void init() {
  int n = 10000000; Sk[1] = 1, f[1] = 1, S[1] = fpow(2, K);
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ps[pn++] = i, Sk[i] = fpow(i, K);
      f[i] = i - 1;
    }
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      Sk[i * ps[j]] = 1ll * Sk[i] * Sk[ps[j]] % mod;
      if (i % ps[j] == 0) {
        int tmp = i * ps[j];
        if (i / ps[j] % ps[j] != 0) f[tmp] = 1ll * f[i/ps[j]] * (mod - ps[j]) % mod;
        else f[tmp] = 0;
        break;
      }
      else f[i * ps[j]] = 1ll * f[i] * (ps[j] - 1) % mod;
    }
  }
  for (int i = 1; i <= n/2; i++) f[i] = 1ll * f[i] * Sk[i] % mod;
  for (int i = 1; i <= n/2; i++) {
    f[i] += f[i-1];
    if (f[i] >= mod) f[i] -= mod;
  }
  for (int i = 1; i <= n; i++) {
    Sk[i] += Sk[i-1];
    if (Sk[i] >= mod) Sk[i] -= mod;
  }
//  cout << "Sk: "; for (int i = 1; i <= 10; i++) cout << Sk[i] << " "; cout << endl;
  for (int i = 1; i < n/2; i++) {
    S[i+1] = (0ll + S[i] + Sk[2*i+2] + Sk[2*i+1] - 2ll * Sk[i+1] % mod + mod) % mod;
  }
//  cout << "S: "; for (int i = 1; i <= 10; i++) cout << S[i] << " "; cout << endl;
}

int main() {
  int n, ans = 0; ll tK; scanf("%d%lld", &n, &tK); 
  K = tK % (mod-1); init();
  for (int l = 1, r = 0; l <= n; l = r+1) {
    r = n / (n/l);
    ans += 1ll * S[n/l] * (f[r] - f[l-1] + mod) % mod;
    if (ans >= mod) ans -= mod;
  }
  printf("%d\n", ans);
  return 0;
}
