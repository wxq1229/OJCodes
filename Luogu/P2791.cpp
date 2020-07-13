#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

inline int qpow(int a, int b = MOD - 2, int m = MOD) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD, b >>= 1;
  }
  return ans;
}

const int gn = 3, ign = qpow(gn), img = qpow(gn, (MOD - 1) / 4);
const int N = 6e5 + 10;

namespace FFT { 
  int rev[N], W[2][N]; 
  bool done = 0;
  void initW() {
    done = 1;
    for (int i = 0; (1 << i) <= 524288; i++) {
      W[1][1 << i] = qpow(gn, (MOD - 1) / (1<<i));
      W[0][1 << i] = qpow(ign, (MOD - 1) / (1<<i));
    }
  }
}

inline int glim(int n) {
  int lim = 1;
  while (lim <= n) lim <<= 1;
  return lim;
}
void fft_init(int n) {
  using namespace FFT;
  if (!done) initW();
  for (int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) ? n >> 1 : 0);
}
void fft(int *f, int n, int flg) {
  using namespace FFT;
  for (int i = 0; i < n; i++) if (rev[i] < i) swap(f[i], f[rev[i]]);
  for (int len = 2; len <= n; len <<= 1) {
    int wn = W[flg==1][len], k = len >> 1;
    for (int i = 0; i < n; i += len)
      for (int w = 1, j = i; j < i + k; j++, w = 1ll * w * wn % MOD) {
        int tmp = 1ll * w * f[j + k] % MOD;
        int x = f[j] - tmp, y = f[j] + tmp;
        f[j + k] = x < 0 ? x + MOD : x;
        f[j] = y >= MOD ? y - MOD : y;
      }
  }
  if (flg == -1) {
    int inv = qpow(n);
    for (int i = 0; i < n; i++) f[i] = 1ll * f[i] * inv % MOD;
  }
}

const int SZ = 2e7 + 1;
int ifac[SZ], fac[SZ];

void fac_init(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = 1ll * fac[i - 1] * i % MOD;
  }
  ifac[n] = qpow(fac[n]);
  for (int i = n - 1; i >= 0; i--) {
    ifac[i] = 1ll * ifac[i + 1] * (i + 1) % MOD;
  }
}

int pw[N], pn, ps[N];
bool vis[N];
void sieve(int n, int k) {
  pw[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      pw[i] = qpow(i, k);
      ps[pn++] = i;
    }
    for (int j = 0; j < pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      pw[i * ps[j]] = 1ll * pw[i] * pw[ps[j]] % MOD;
      if (i % ps[j] == 0) break;
    }
  }
}
                    
int st[N];
void stirling_init(int n) {
  sieve(n, n);
  static int f[N], g[N];
  for (int i = 0; i <= n; i++) {
    f[i] = (i & 1) ? MOD - ifac[i] : ifac[i];
    g[i] = 1ll * pw[i] * ifac[i] % MOD;
  }         
  int lim = glim(n + n);
  fft_init(lim);
  fft(f, lim, 1), fft(g, lim, 1);
  for (int i = 0; i < lim; i++) {
    f[i] = 1ll * f[i] * g[i] % MOD;
  }
  fft(f, lim, -1);
  for (int i = 0; i <= n; i++) st[i] = f[i];
}

inline int comb(int n, int r) {
  if (n < 0 || r < 0 || n - r < 0) return 0;
  return 1ll * fac[n] * ifac[r] % MOD * ifac[n - r] % MOD;
}
inline int icomb(int n, int r) {
  if (n < 0 || r < 0 || n - r < 0) return 0;
  return 1ll * ifac[n] * fac[r] % MOD * fac[n - r] % MOD;
}

#define N SummerPockets

inline char nc() {
  const int SZ = 1 << 20;
  static char buf[SZ], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SZ, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T> inline T rd() {
  T x = 0; char ch = nc(); bool f = 1;
  while (!isdigit(ch)) { f ^= ch == '-'; ch = nc(); }
  while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = nc(); }
  return f ? x : -x;
}
#define gi rd<int>

void write(int x) {
  if (x > 9) write(x/10);
  putchar(x % 10 + 48);
}

int main() {
#ifdef LOCAL
  double STIME = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  auto add = [&](int &x, int y) {
    x += y;
    if (x >= MOD) x -= MOD;
  };          
  int N = gi(), M = gi(), S = gi(), L = gi();
  fac_init(max(N, L));
  stirling_init(L);
  while (S--) {
    int n, m, k;        
    n = gi(), m = gi(), k = gi();
    int ans = 0, lim = min(min(m, L), k);
    for (int i = 0; i <= lim; i++) {
      add(ans, 1ll * st[i] * fac[n - i] % MOD * ifac[m - i] % MOD * ifac[k - i] % MOD);
    }
    write(1ll * ans * fac[m] % MOD * fac[k] % MOD * ifac[n] % MOD), puts("");
  }
#ifdef LOCAL
  cerr << (clock() - STIME) / CLOCKS_PER_SEC << " ms\n";
#endif
  return 0;
}