#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 10;
int phi[N], ps[N], pn;
bool vis[N];

void sieve(int n) {
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ps[pn++] = i;
      phi[i] = i - 1;
    }
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      phi[i * ps[j]] = i % ps[j] == 0 ? phi[i] * ps[j] : phi[i] * (ps[j] - 1);
      if (i % ps[j] == 0) {
        break;
      }
    }
  }
}
                
int power(int a, int b, int md) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % md;
    a = 1ll * a * a % md, b >>= 1;
  }
  return ans;
}

int solve(int a, int p) {
  if (p == 1) return 0;
  else return power(a, solve(a, phi[p]) + phi[p], p);  
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  sieve((int) 1e7);
  int tt;
  cin >> tt;
  while (tt--) {
    int p;
    cin >> p;
    cout << solve(2, p) << '\n';
  }
  return 0;
}