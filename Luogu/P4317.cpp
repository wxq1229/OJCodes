#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 53, MOD = 10000007;

inline int qpow(ll a, ll b) {
  a %= MOD; int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD, b >>= 1;
  }
  return ans;
}

int bit[N];
ll f[N][2][N];

ll dp(int pos, bool up, int tot) {
  if (!pos) return tot == 0;
  ll &ans = f[pos][up][tot];
  if (~ans) return ans;
  ans = 0;
  int lim = up ? bit[pos] : 1;
  for (int i = 0; i <= lim; i++) {
    ans += dp(pos - 1, up && (i == bit[pos]), tot - i);
  }
  return ans;
}

int main() {
  ll n; cin >> n;
  int len = 0, ans = 1;
  while (n) bit[++len] = n % 2, n /= 2;
  memset(f, -1, sizeof(f));
  for (int i = 1; i <= len; i++) {
    ans = 1ll * ans * qpow(i, dp(len, 1, i)) % MOD;
  }
  cout << ans << '\n';
  return 0;
}