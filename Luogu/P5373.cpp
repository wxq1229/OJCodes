#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MOD = 998244353;

inline int qpow(int a, int b = MOD - 2, int m = MOD) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD, b >>= 1;
  }
  return ans;
}

void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}

const int gn = 3, ign = qpow(gn), img = qpow(gn, (MOD - 1) / 4);
const int N = 66666;

namespace FFT { 
  int rev[N], W[2][N]; 
  bool done = 0;
  void initW() {
    done = 1;
    for (int i = 0; (1 << i) < N; i++) {
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

  template <typename T>
  poly get_poly(int n, T gt) const {
    static int f[N], g[N];
    for (int i = 0; i < n; i++) f[i] = i < size() ? a[i] : 0, g[i] = 0;
    gt(f, n, g);
    poly ans(n);
    for (int i = 0; i < n; i++) ans[i] = g[i];
    return ans;
  }

  inline int operator()(int x) const {
    int n = a.size(), cur = 1, ans = 0;
    for (int i = 0; i < n; i += 4) {
      int x0 = cur, x1 = 1ll * x0 * x % MOD;
      int x2 = 1ll * x1 * x % MOD, x3 = 1ll * x2 * x % MOD;
      add(ans, 1ll * x0 * a[i] % MOD);
      if (i + 1 < n) add(ans, 1ll * x1 * a[i + 1] % MOD);
      if (i + 2 < n) add(ans, 1ll * x2 * a[i + 2] % MOD);
      if (i + 3 < n) add(ans, 1ll * x3 * a[i + 3] % MOD);
      cur = 1ll * x3 * x % MOD;
    }
    return ans;
  }
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
  int sd = a.deg() + b.deg();
  if (a.deg() == 0 || b.deg() == 0) {
    for (int i = 0; i < a.size() + b.size(); i++) h[i] = 0;
    for (int i = 0; i < a.size(); i++)
      for (int j = 0; j < b.size(); j++) {
        add(h[i + j], 1ll * a[i] * b[j] % MOD);
      }
    poly c(a.deg() + b.deg() + 1);
    for (int i = 0; i < c.size(); i++) c[i] = h[i];
    return c;
  }
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
template <typename T> void write(T x) {
	if (x < 0) putchar('-'), x = -x;
	if (x > 9) write(x / 10);
	putchar(x % 10 + 48);
}

poly pwg[N], pwbg[N];

int main() {
	int n, m;
	n = gi(), m = gi();
	++n, ++m;
	poly f(n);
	poly g(m);
	for (int i = 0; i < n; ++i)
		f[i] = gi();
	for (int i = 0; i < m; ++i)
		g[i] = gi();
	const int BLOCK = sqrt(n) + 1;
	pwg[0]= poly(1, 1);
	for (int i = 1; i <= BLOCK; ++i) {
		pwg[i] = pwg[i - 1] * g;
		if (pwg[i].size() > n) pwg[i].resize(n);
	}
	pwbg[0] = poly(1, 1);
	pwbg[1] = pwg[BLOCK];
	for (int i = 2; i < BLOCK; ++i) {
		pwbg[i] = pwbg[i - 1] * pwg[BLOCK];
		if (pwbg[i].size() > n) pwbg[i].resize(n);
	}
	// for (auto p : pwbg) cerr << p << '\n';
	poly coeff(1, 0), ans(n, 0);
	for (int i = 0; i < n; ++i) {
		coeff.resize(max(coeff.size(), pwg[i%BLOCK].size()));
		for (int j = 0; j < coeff.size(); ++j)
			::add(coeff[j], (ll) f[i] * pwg[i % BLOCK][j] % MOD);
		if ((i + 1) % BLOCK == 0 || i == n - 1) {
			poly add = pwbg[i / BLOCK] * coeff;
			for (int j = 0; j < min(add.size(), n); ++j)
				::add(ans[j], add[j]);
			coeff = poly(1);
		}
	}
	for (int i = 0; i < n; ++i)
		write(ans[i]), putchar(' ');
	return 0;
}