#include <bits/stdc++.h>

using namespace std;

template <typename T>
T exgcd(T a, T b, T& x, T& y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  T d = exgcd(b, a % b, x, y);
  T t = y; y = x - a / b * y, x = t;
  return d;
}
template <typename T>
T inverse(T a, T m) {
  T x = 0, y = 0;
  T d = exgcd(a, m, x, y);
  assert(d == 1);
  return x;
}

template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;
  
  Modular() : value() { }
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }
      
  template <typename U>
  Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }
  
  Type operator()() const { return value; }
  constexpr static Type mod() { return T::value; }

  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }

  Modular& operator+=(const Modular& other) { value += other.value; if (value >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { value  -= other.value; if (value < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular operator++() { *this += 1; return *this; }
  Modular operator--() { *this -= 1; return *this; }
  Modular operator++(int) { Modular res(*this); *this += 1; return res; }
  Modular operator--(int) { Modular res(*this); *this -= 1; return res; }
  Modular operator-() const { return Modular(-value); }

  template <typename U = T>
  typename enable_if<is_same<typename decay<decltype(U::value)>::type, int>::value, Modular>::type& operator*=(const Modular& other)  {
    value = 1ll * value * other.value % mod();
    return *this;
  }        
  template <typename U = T>
  typename enable_if<is_same<typename decay<decltype(U::value)>::type, int64_t>::value, Modular>::type& operator*=(const Modular& other) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) * other.value / mod());
    value = normalize(value * other.value - q * mod());
    return *this;
  }

  Modular& operator/=(const Modular &other) { return *this *= Modular(inverse(other.value, mod())); }

  friend ostream& operator<<(ostream& stream, const Modular& number) {
    stream << number();
    return stream;
  }
  friend istream& operator>>(istream& stream, Modular& number) {
    stream >> number.value;
    return stream;
  }
  friend bool operator==(const Modular& lhs, const Modular& rhs) { return lhs.value == rhs.value; }
  friend bool operator!=(const Modular& lhs, const Modular& rhs) { return lhs.value != rhs.value; }
  
  friend Modular operator+(const Modular& lhs, const Modular& rhs) { return Modular(lhs) += rhs; }
  template <typename U> friend Modular operator+(const Modular& lhs, const U& rhs) { return Modular(lhs) += rhs; }
  template <typename U> friend Modular operator+(const U& lhs, const Modular& rhs) { return Modular(lhs) += rhs; }

  friend Modular operator-(const Modular& lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }
  template <typename U> friend Modular operator-(const Modular& lhs, const U& rhs) { return Modular(lhs) -= rhs; }
  template <typename U> friend Modular operator-(const U& lhs, const Modular& rhs) { return Modular(lhs) -= rhs; }

  friend Modular operator*(const Modular& lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }
  template <typename U> friend Modular operator*(const Modular& lhs, const U& rhs) { return Modular(lhs) *= rhs; }
  template <typename U> friend Modular operator*(const U& lhs, const Modular& rhs) { return Modular(lhs) *= rhs; }

  friend Modular operator/(const Modular& lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }
  template <typename U> friend Modular operator/(const Modular& lhs, const U& rhs) { return Modular(lhs) /= rhs; }
  template <typename U> friend Modular operator/(const U& lhs, const Modular& rhs) { return Modular(lhs) /= rhs; }

  template <typename U>
  friend Modular power(const Modular& a, const U& b) {
    Modular x = a, ans = 1;
    U p = b;
    while (p) {
      if (p & 1) ans *= x;
      x *= x, p >>= 1;
    }
    return ans;
  } 
  friend Modular inverse(const Modular& a) { return 1 / a; }

 private:
  Type value;
};         
                                     
const int md = 998244353;
using Mint = Modular<integral_constant<decay<decltype(md)>::type, md>>;

const Mint gn = 3, ign = inverse(gn), img = power(gn, (md - 1) / 4);
const int N = 1e6 + 10;

namespace FFT {
  int rev[N];
  Mint W[2][N];
  bool done = 0;

  void initW() {
    done = 1;
    for (int i = 0; (1 << i) < N; i++) {
      W[1][1 << i] = power(gn, (md - 1) / (1<<i));
      W[0][1 << i] = power(ign, (md - 1) / (1<<i));
    }
  }
}

inline int glim(int n) { int lim = 1; while (lim <= n) lim <<= 1; return lim; }

void fft_init(int n) {
  using namespace FFT;
  if (!done) initW();
  for (int i = 0; i < n; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) ? n >> 1 : 0);
}

void fft(Mint *f, int n, int flg) {
  using namespace FFT;
  for (int i = 0; i < n; i++) if (rev[i] < i) swap(f[i], f[rev[i]]);
  for (int len = 2; len <= n; len <<= 1) {
    int k = len >> 1;
    Mint wn = W[flg==1][len];
    for (int i = 0; i < n; i += len) {
      Mint w = 1;
      for (int j = i; j < i + k; j++, w *= wn) {
        Mint tmp = f[j + k] * w;
        f[j + k] = f[j] - tmp;
        f[j] = f[j] + tmp;
      }
    }
  }
  if (flg == -1) {
    Mint inv = inverse((Mint) n);
    for (int i = 0; i < n; i++) f[i] *= inv;
  }
}

void poly_inv(const Mint *f, int n, Mint *g) {
  if (n == 1) { g[0] = inverse(f[0]); return; }
  poly_inv(f, (n + 1) >> 1, g);
  int lim = glim((n - 1) << 1);
  static Mint tf[N];
  for (int i = 0; i < lim; i++) {
    tf[i] = i < n ? f[i] : 0;
    g[i] = i < n ? g[i] : 0;
  }
  fft_init(lim);
  fft(tf, lim, 1), fft(g, lim, 1);
  for (int i = 0; i < lim; i++) {
    g[i] = g[i] * (2 - tf[i] * g[i]);
  }
  fft(g, lim, -1);
  for (int i = n; i < lim; i++) g[i] = 0;
}

void poly_mul(const Mint *a, const Mint *b, int lim, Mint *c) {
  fft_init(lim);
  static Mint f[N], g[N];
  for (int i = 0; i < lim; i++) f[i] = a[i], g[i] = b[i];
  fft(f, lim, 1), fft(g, lim, 1);
  for (int i = 0; i < lim; i++) f[i] = f[i] * g[i];
  fft(f, lim, -1);
  for (int i = 0; i < lim; i++) c[i] = f[i];
}

void poly_deriv(const Mint *f, int n, Mint *g) {
  for (int i = 1; i < n; i++) g[i - 1] = f[i] * i;
  g[n - 1] = 0;
}

void poly_integ(const Mint *f, int n, Mint *g) {
  for (int i = 0; i < n; i++) g[i + 1] = f[i] * inverse(Mint(i + 1));
  g[0] = g[n] = 0;
}

void poly_ln(const Mint *f, int n, Mint *g) {
  int lim = glim((n - 1) << 1);
  static Mint derf[N], invf[N], derg[N];
  for (int i = 0; i < lim; i++) derf[i] = invf[i] = derg[i] = g[i] = 0;
  poly_inv(f, n, invf), poly_deriv(f, n, derf);
  poly_mul(invf, derf, lim, derg);
  for (int i = n; i < lim; i++) derg[i] = 0;
  poly_integ(derg, n, g);
}

void poly_exp(const Mint *f, int n, Mint *g) {
  if (n == 1) { g[0] = 1; return; }
  poly_exp(f, (n + 1) >> 1, g);
  static Mint tf[N], lng[N];
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
    g[i] = g[i] * (1 - lng[i] + tf[i]);
  }
  fft(g, lim, -1);
  for (int i = n; i < lim; i++) g[i] = 0;
}

struct poly {
  vector<Mint> a;
  inline Mint operator [] (int i) const { return i < size() ? a[i] : 0; }
  inline Mint &operator [] (int i) { return a[i]; }
  inline int size() const { return a.size(); }
  inline int deg() const { return size() - 1; }
  void resize(int n) { a.resize(n); }
  void reverse() { ::reverse(a.begin(), a.end()); }

  void init(int n = 0, Mint v = 0) { a = vector<Mint>(n, v); }
  poly(int n = 0, Mint v = 0) { init(n, v); }
           
  poly(const vector<Mint>& v) { a = v; }
  poly(const initializer_list<Mint> &l) { a = l; }

  template <typename T>
  poly get_poly(int n, T gt) const {
    static Mint f[N], g[N];
    for (int i = 0; i < n; i++) f[i] = i < size() ? a[i] : 0, g[i] = 0;
    gt(f, n, g);
    poly ans(n);
    for (int i = 0; i < n; i++) ans[i] = g[i];
    return ans;
  }

  inline Mint operator()(Mint x) const {
    Mint ans = 0, cur = 1;
    int n = a.size();
    for (int i = 0; i < n; i += 4) {
      Mint x0 = cur, x1 = x0 * x, x2 = x1 * x, x3 = x2 * x;
      ans += x0 * a[i];
      (i + 1 < n) && (ans += x1 * a[i + 1], 1);
      (i + 2 < n) && (ans += x2 * a[i + 2], 1);
      (i + 3 < n) && (ans += x3 * a[i + 3], 1);
      cur = x3 * x;
    }
    return ans;
  }

  poly inv(int n) const { return get_poly(n, poly_inv); }
  poly exp(int n) const { return get_poly(n, poly_exp); }
  poly ln(int n) const { return get_poly(n, poly_ln); }
  poly deriv(int n) const { return get_poly(n, poly_deriv); }
  poly integ(int n) const { return get_poly(n, poly_integ); }

  poly sin(int) const;
  poly cos(int) const;
  poly pow(int, int) const;
};

poly operator - (const poly &a) {
  poly b = a;
  for (int i = 0; i < b.size(); i++) b[i] = -b[i];
  return b;
}

poly operator + (const poly &a, const poly &b) {
  poly c(max(a.size(), b.size()));
  for (int i = 0; i < c.size(); i++) c[i] = a[i] + b[i];
  return c;
}
poly operator - (const poly &a, const poly &b) { return a + (-b); }

poly operator * (const poly &a, const poly &b) {
  static Mint f[N], g[N], h[N];
  if (1ll * a.deg() * b.deg() < 2333) {
    for (int i = 0; i < a.size() + b.size(); i++) h[i] = 0;
    for (int i = 0; i < a.size(); i++)
      for (int j = 0; j < b.size(); j++) {
        h[i + j] += a[i] * b[j];
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

poly operator * (const poly &a, Mint b) {
  return a * poly(1, b);
}
poly operator / (const poly &a, Mint b) {
  return a * poly(1, inverse(b));
}

pair<poly, poly> div_mod(const poly &a, const poly &b) {
  int n = a.deg(), m = b.deg();
  if (n < m) {
    return make_pair(poly(0,0), a);
  }
  poly f = a, g = b;
  f.reverse(), g.reverse();
  poly q = f * g.inv(n - m + 1);
  q.resize(n - m + 1), q.reverse();
  poly r = a - b * q; r.resize(m);
  return make_pair(q, r);
}

poly operator / (const poly &a, const poly &b) { return div_mod(a, b).first; }
poly operator % (const poly &a, const poly &b) { return div_mod(a, b).second; }

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
  poly A = poly(1, img) * (*this), B = poly(1, -img) * (*this);
  return (A.exp(n) - B.exp(n)) * poly(1, inverse(img * 2));
}

poly poly::cos(int n) const {
  poly A = poly(1, img) * (*this), B = poly(1, -img) * (*this);
  return (A.exp(n) + B.exp(n)) * poly(1, inverse(Mint(2)));
}

poly poly::pow(int k, int n) const {
  int len = this->size(), fst = 0;
  for (int i = 0; i < len; i++) if ((*this)[i] != 0) {
    fst = i;
    break;
  }
  poly b(n);
  for (int i = 0; i < n; i++) b[i] = (*this)[i + fst];
  Mint b0 = b[0];
  b = b / b0;
  poly c = (b.ln(n) * Mint(k)).exp(n);
  poly ans(n); long long mov = 1ll * fst * k;
  if (mov >= n) return ans;
  for (int i = 0; i + mov < n; i++) ans[i + mov] = c[i] * power(b0, k);
  return ans;
}

namespace PolyTree {
  const int N = 4e5 + 10;
  poly mul[N << 2], a[N];

  void build(int x, int l, int r) {
    if (l == r) {
      mul[x] = a[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(x<<1, l, mid);
    build(x<<1|1, mid + 1, r);
    mul[x] = mul[x<<1] * mul[x<<1|1];
  }
}

namespace PolyEval {
  using namespace PolyTree;

  Mint ans[PolyTree::N];
  vector<Mint> px;
  void solve(int x, int l, int r, const poly &p) {
    if (r - l + 1 <= 555) {
      for (int i = l; i <= r; i++) {
        ans[i] = p(px[i]);
      }
      return;
    }
    int mid = (l + r) >> 1;
    solve(x<<1, l, mid, p % mul[x<<1]);
    solve(x<<1|1, mid + 1, r, p % mul[x<<1|1]);
  }

  vector<Mint> poly_eval(const poly &f, const vector<Mint> &pos, bool built = 0) {
    int n = pos.size();
    px = pos;
    for (int i = 0; i < n; i++) {
      a[i] = poly(2,0);
      a[i][0] = -pos[i], a[i][1] = 1;
    }
    !built && (build(1, 0, n - 1), 1);
    solve(1, 0, n - 1, f % mul[1]);
    vector<Mint> res(n);
    for (int i = 0; i < n; i++) {
      res[i] = ans[i];
    }
    return res;
  }
}
using PolyEval::poly_eval;

namespace PolyInter {
  using namespace PolyTree;
  vector<Mint> x, y, mval;

  poly solve(int x, int l, int r) {
    if (l == r) {
      return poly(1, y[l] / mval[l]);
    }
    int mid = (l + r) >> 1, lc = x<<1, rc = x<<1|1;
    return solve(lc, l, mid) * mul[rc] + solve(rc, mid + 1, r) * mul[lc];
  }

  poly poly_inter(const vector<Mint> &pos, const vector<Mint> &val) {
    int n = pos.size();
    x = pos; y = val;
    for (int i = 0; i < n; i++) {
      a[i] = poly(2, 0);
      a[i][0] = -x[i];
      a[i][1] = 1;
    }
    build(1, 0, n - 1);
    poly M = mul[1].deriv(n + 1);
    mval = poly_eval(M, x, 1);
    return solve(1, 0, n - 1);
  }
}
using PolyInter::poly_inter;

vector<Mint> fac, ifac;
void gen_fac(int n) {
  fac = vector<Mint>(n);
  ifac = vector<Mint>(n);
  fac[0] = 1;
  for (int i = 1; i < n; i++) {
    fac[i] = fac[i - 1] * i;
  }
  ifac[n - 1] = inverse(fac[n - 1]);
  for (int i = n - 2; i >= 0; i--) {
    ifac[i] = ifac[i + 1] * (i + 1);
  }
//  for (int i = 0; i < n; i++) cerr << fac[i] << " "; cerr << endl;
//  for (int i = 0; i < n; i++) cerr << ifac[i] << " "; cerr << endl;
}

poly B;
void genB(int n) {
  gen_fac(n + 1);
  B = poly(n);
  for (int i = 0; i < n; i++) {
    B[i] = ifac[i + 1];
  }
  B = B.inv(n);
  for (int i = 0; i < n; i++) {
    B[i] *= fac[i];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);          
  int n;
  cin >> n;
  vector<Mint> a(n + 1);
  for (int i = 0; i < n + 1; i++) {
    cin >> a[i];
  }     
  genB(n + 2);
  poly f(n + 1), g(n + 1);
  for (int i = 0; i <= n; i++) {
    f[i] = B[i] * ifac[i];
    g[i] = a[n - i] * fac[n - i];
  }
  poly tF = f * g; tF.resize(n + 2);
  poly F(n + 2);
  F[0] = 0;
  for (int i = 1; i < n + 2; i++) {
    F[i] = tF[n - i + 1] * ifac[i];
  }
//  cerr << F << '\n';
  {
    poly fa(n + 2), fb(n + 2);
    int lim = n + 1;
    for (int i = 0; i <= lim; i++) {
      fa[i] = F[lim - i] * fac[lim - i];
      fb[i] = ifac[i];
    }
    tF = fa * fb;
    tF.resize(n + 2);
    F = poly(lim + 1);
    for (int i = 0; i <= lim; i++) {
      F[i] = tF[lim - i] * ifac[i];
    }
  }
  for (int i = 0; i < n + 2; i++) {
    cout << F[i] << " ";
  }
  return 0;
}