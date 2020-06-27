#include <bits/stdc++.h>

using namespace std;

const int N = 23;
typedef long long ll;

ll f[N][2][2][N];
bool vis[N][2][2][N];

int qd, dg[N];

ll dp(int pos, bool up, bool zero, int tot) {
  if (!pos) return tot;
  if (vis[pos][up][zero][tot]) return f[pos][up][zero][tot];
  vis[pos][up][zero][tot] = 1;
  int lim = !up ? 9 : dg[pos];
  ll &ans = f[pos][up][zero][tot];
  for (int i = 0; i <= lim; i++) {
    ans += dp(pos - 1, up && i == dg[pos], zero && i == 0, tot + ((!zero || i != 0) && i == qd));
  }
  return ans;
}

ll qry(ll n, int d) {
  qd = d;
  int len = 0;
  while (n) dg[++len] = n % 10, n /= 10;
  memset(f, 0, sizeof(f));
  memset(vis, 0, sizeof(vis));
  qd = d;
  return dp(len, 1, 1, 0);
}

int main() {
  ll l, r;
  cin >> l >> r;
  for (int i = 0; i <= 9; i++) {
    cout << qry(r, i) - qry(l - 1, i) << " ";
  }
  return 0;
}