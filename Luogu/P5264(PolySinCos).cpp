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

void poly_inv(const int *f, int n, int *g) {
  if (n == 1) { g[0] = qpow(f[0]); return; }
  poly_inv(f, (n + 1) >> 1, g);
  int lim = glim((n - 1) << 1);
  static int tf[N];
  for (int i = 0; i < lim; i++) {
    tf[i] = i < n ? f[i] : 0;
    g[i] = i < n ? g[i] : 0;
  }        
  fft_init(lim);
  fft(tf, lim, 1), fft(g, lim, 1);
  for (int i = 0; i < lim; i++) g[i] = 1ll * g[i] * (2ll - 1ll* tf[i] * g[i] % MOD + MOD) % MOD;
  fft(g, lim, -1);
  for (int i = n; i < lim; i++) g[i] = 0;
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

void poly_deriv(const int *f, int n, int *g) {
  for (int i = 1; i < n; i++) g[i - 1] = 1ll * f[i] * i % MOD;
  g[n - 1] = 0;
}

void poly_integ(const int *f, int n, int *g) {
  for (int i = 0; i < n; i++) g[i + 1] = 1ll * f[i] * qpow(i + 1) % MOD;
  g[0] = g[n] = 0;
}

void poly_ln(const int *f, int n, int *g) {
  int lim = glim((n - 1) << 1);
  static int derf[N], invf[N], derg[N];
  for (int i = 0; i < lim; i++) derf[i] = invf[i] = derg[i] = g[i] = 0;
  poly_inv(f, n, invf), poly_deriv(f, n, derf);
  poly_mul(invf, derf, lim, derg);
  for (int i = n; i < lim; i++) derg[i] = 0;
  poly_integ(derg, n, g);
}

void poly_exp(const int *f, int n, int *g) {
  if (n == 1) { g[0] = 1; return; }
  poly_exp(f, (n + 1) >> 1, g);
  static int tf[N], lng[N]; 
  int lim = glim((n - 1) << 1);
  for (int i = 0; i < lim; i++) lng[i] = 0;
  for (int i = n; i < lim; i++) g[i] = 0;
  poly_ln(g, n, lng);                
  for (int i = 0; i < lim; i++) {
    tf[i] = i < n ? f[i] : 0;
    g[i] = i < n ? g[i] : 0;
  }
  fft_init(lim);
  fft(tf, lim, 1), fft(g, lim, 1), fft(lng, lim, 1);
  for (int i = 0; i < lim; i++) {
    g[i] = 1ll * g[i] * (1ll - lng[i] + tf[i] + MOD) % MOD;
  }
  fft(g, lim, -1);
  for (int i = n; i < lim; i++) g[i] = 0;
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

  template <typename T>
  poly get_poly(int n, T gt) const {
    static int f[N], g[N];
    for (int i = 0; i < n; i++) f[i] = i < size() ? a[i] : 0, g[i] = 0;
    gt(f, n, g);
    poly ans(n);
    for (int i = 0; i < n; i++) ans[i] = g[i];
    return ans;
  }

	poly inv(int n) const { return get_poly(n, poly_inv); }
	poly exp(int n) const { return get_poly(n, poly_exp); }
	poly ln(int n) const { return get_poly(n, poly_ln); }
	
	poly sin(int) const;
	poly cos(int) const;
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

ostream &operator<<(ostream &os, const poly &a) {
  int n = a.size(); os << '{';
  for (int i = 0; i < n; i++) {
    os << a[i];
    if (i == n - 1) os << "}";
    else os << ", ";
  }
	return os;
}

poly poly::sin(int n) const {
  poly A = (poly) {img} * (*this), B = (poly) {MOD - img} * (*this);
//  cerr << "A " << A << "\nB " << B << '\n'; 
//  cerr << "exp A " << A.exp(n) << "\nexp B " << B.exp(n) << endl;
  return (A.exp(n) - B.exp(n)) * (poly) {qpow(2ll * img % MOD)};
} 
poly poly::cos(int n) const {
  poly A = (poly) {img} * (*this), B = (poly) {MOD - img} * (*this);
//  cerr << "A " << A << "\nB " << B << '\n'; 
//  cerr << "exp A " << A.exp(n) << "\nexp B " << B.exp(n) << endl;
  return (A.exp(n) + B.exp(n)) * (poly) {qpow(2)};
}

int main() {
  ios::sync_with_stdio(false);
  int n, opt;
  cin >> n >> opt;
  poly A(n), B;
  for (int i = 0; i < n; i++) cin >> A[i];
  B = opt ? A.cos(n) : A.sin(n);
  for (int i = 0; i < n; i++) cout << B[i] << " ";
  cout << '\n';
  return 0;
}