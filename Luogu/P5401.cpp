#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353, i2 = (MOD + 1) / 2;

inline int qpow(int a, int b = MOD - 2, int m = MOD) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD, b >>= 1;
  }
  return ans;
}

const int gn = 3, ign = qpow(gn), img = qpow(gn, (MOD - 1) / 4);
const int N = 1e6 + 10;

namespace FFT { int rev[N]; }
inline int glim(int n) {
  int lim = 1;
  while (lim <= n) lim <<= 1;
  return lim;
}
void fft_init(int n) {
  using namespace FFT;
  for (int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) ? n >> 1 : 0);
}
void fft(int *f, int n, int flg) {
  using namespace FFT;
  for (int i = 0; i < n; i++) if (rev[i] < i) swap(f[i], f[rev[i]]);
  for (int len = 2; len <= n; len <<= 1) {
    int wn = qpow(flg == 1 ? gn : ign, (MOD - 1) / len), k = len >> 1;
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

void poly_mul(const int *a, const int *b, int lim, int *c) {
  fft_init(lim);
  static int f[N], g[N];
  for (int i = 0; i < lim; i++) f[i] = a[i], g[i] = b[i];
  fft(f, lim, 1), fft(g, lim, 1);
  for (int i = 0; i < lim; i++) f[i] = 1ll * f[i] * g[i] % MOD;
  fft(f, lim, -1);
  for (int i = 0; i < lim; i++) c[i] = f[i];
}

struct poly {
  vector<int> a;
  inline int operator [] (int i) const { return a[i]; }
  inline int &operator [] (int i) { return a[i]; }
  inline int size() const { return a.size(); }
  inline int deg() const { return size() - 1; }
  void resize(int n) { a.resize(n); }
  void reverse() { ::reverse(a.begin(), a.end()); }
  void init(int n = 0, int v = 0) { a = vector<int>(n, v); }
  poly(int n = 0, int v = 0) { init(n, v); }
  poly(initializer_list<int> v) { a = v; }
};

poly operator - (const poly &a) {
  poly b = a;
  for (int i = 0; i < b.size(); i++) b[i] = MOD - b[i];
  return b;
}

poly operator + (const poly &a, const poly &b) {
  poly c(max(a.size(), b.size()));
  for (int i = 0; i < c.size(); i++) c[i] = (a[i] + b[i]) % MOD;
  return c;
}
poly operator - (const poly &a, const poly &b) { return a + (-b); }

poly operator * (const poly &a, const poly &b) {
  static int f[N], g[N], h[N];
  int lim = glim(a.deg() + b.deg());
  for (int i = 0; i < lim; i++) f[i] = g[i] = h[i] = 0;
  for (int i = 0; i < a.size(); i++) f[i] = a[i];
  for (int i = 0; i < b.size(); i++) g[i] = b[i];
  poly_mul(f, g, lim, h);
  poly c(a.deg() + b.deg() + 1);
  for (int i = 0; i < c.size(); i++) c[i] = h[i];
  return c;
}     

poly operator * (const poly &a, int b) { return a * (poly) {b}; }
poly operator / (const poly &a, int b) { return a * (poly) {qpow(b)}; }

ostream &operator<<(ostream &os, const poly &a) {
  int n = a.size(); os << '{';
  for (int i = 0; i < n; i++) {
    os << a[i];
    if (i == n - 1) os << "}";
    else os << ", ";
  }
  return os;
}

int fac[N], ifac[N], inv[N];

void fac_init(int n) {
  fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
  inv[1] = 1;
  for (int i = 2; i <= n; i++) {
    inv[i] = 1ll * inv[MOD % i] * (MOD - MOD / i) % MOD;
    ifac[i] = 1ll * ifac[i - 1] * inv[i] % MOD;
    fac[i] = 1ll * fac[i - 1] * i % MOD;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);          
  int D, n, m;
  cin >> D >> n >> m;
  if (n - 2 * m >= D) { 
    cout << qpow(D, n) << '\n'; 
    return 0; 
  }
  if (n - 2 * m < 0) { 
    cout << "0\n"; 
    return 0; 
  }
  fac_init(D);
  poly ga(D + 1), gb(D + 1);
  for (int i = 0; i <= D; i++) {
    ga[i] = ifac[i];
    gb[i] = 1ll * ifac[i] * qpow((D - 2 * i + MOD) % MOD, n) % MOD * ((i & 1) ? MOD - 1: 1) % MOD;
  }
  poly g = ga * gb; g.resize(D + 1);
  for (int i = 0; i <= D; i++) {
    g[i] = 1ll * g[i] * fac[D] % MOD * ifac[D - i] % MOD * qpow(i2, i) % MOD;
  }
  poly fa(D + 1), fb(D + 1);
  for (int i = 0; i <= D; i++) {
    fa[i] = 1ll * fac[D - i] * g[D - i] % MOD;
    fb[i] = 1ll * ((i & 1) ? MOD - 1 : 1) * ifac[i] % MOD;
  }
  poly f = fa * fb; f.resize(D + 1);
  int ans = 0;
  // cerr << f << '\n';
  for (int i = 0; i <= n - 2 * m; i++) {
    (ans += 1ll * ifac[i] * f[D - i] % MOD) %= MOD;
  }
  cout << ans << endl;
  return 0;
}