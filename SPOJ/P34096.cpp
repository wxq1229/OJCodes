#include <bits/stdc++.h>

using namespace std;

const int N = 4e5 + 10;
typedef unsigned long long ull;

int pn, saved_pn, ps[N];
bool nprim[N];

void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!nprim[i]) {
      ++pn;
      ps[pn] = i;
    }
    for (int j = 1; j <= pn && i * ps[j] <= n; j++) {
      nprim[i * ps[j]] = 1;
      if (i % ps[j] == 0) break;
    }
  }
  saved_pn = pn;
}

long long n;
ull K;
int sqn;

int tot, rid[2][N];
ull val[N], g0[N];

inline int id(long long v) {
  if (v <= sqn) return rid[0][v];
  else return rid[1][n / v];
}

void init() {
  sqn = (int) sqrt(n);
  pn = upper_bound(ps + 1, ps + saved_pn + 1, sqn) - 1 - ps;
  tot = 0;
  for (long long l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    val[++tot] = n / l;
    ull v = val[tot];
    g0[tot] = v - 1;
    if (v <= sqn) rid[0][v] = tot;
    else rid[1][n / v] = tot;
  }
  for (int k = 1; k <= pn; k++) {
    for (int i = 1; i <= tot && val[i] >= 1ll * ps[k] * ps[k]; i++) {
      int j = id(val[i] / ps[k]);
      g0[i] = g0[i] - g0[j] + k - 1;
    }
  }
}

inline ull get_g(long long n) {
  int i = id(n);
  return K * g0[i] + g0[i]; 
}
inline ull get_sp(int k) {
  return K * k + k;
}

ull S(long long n, int k) {
  if (ps[k] >= n) return 0;
  ull ans = get_g(n) - get_sp(k);
  for (int i = k + 1; i <= pn && 1ll * ps[i] * ps[i] <= n; i++) {
    long long pw = ps[i];
    for (int e = 1; pw <= n; e++, pw *= ps[i]) {
      ans += (S(n / pw, i) + (e > 1)) * (K * e + 1);
    }
  }
  return ans;
}

void solve() {
  cin >> n >> K;
  init();
  cout << S(n, 0) + 1ull << '\n';
}            

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  sieve((int) 1e5);  
  int tt;
  cin >> tt;
  while (tt--) solve();
  return 0;
}
