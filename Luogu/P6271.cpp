#include <bits/stdc++.h>

using namespace std;

template <int MOD>
struct Modular {
  int value;
                     
  Modular(long long v) {
    value = v % MOD;
    if (value < 0) value += MOD;
  }
  Modular() { value = 0; }

  Modular &operator+=(const Modular &b) { value += b.value; if (value >= MOD) value -= MOD; return *this;	}
  Modular &operator-=(const Modular &b) { value -= b.value; if (value < 0) value += MOD; return *this; }
  Modular &operator*=(const Modular &b) { value = 1ll * value * b.value % MOD; return *this; }
  Modular &operator/=(const Modular &b) { return (*this) *= inverse(b); }

  Modular &operator++(int) { return *this += 1; }
  Modular &operator++() { return *this += 1; }
  Modular &operator--(int) { return *this -= 1; }
  Modular &operator--() { return *this -= 1; }

  template <typename T>
  friend Modular power(Modular a, T n) {
    Modular ans = 1;
    while (n) {
      if (n & 1) ans *= a;
      a *= a, n >>= 1;
    }
    return ans;
  }
  friend Modular inverse(const Modular &a) { return power(a, MOD - 2); }

  friend Modular operator+(Modular a, const Modular &b) { return a += b; }
  friend Modular operator-(Modular a, const Modular &b) { return a -= b; }
  friend Modular operator-(Modular a) { a.value = MOD - a.value; return a; }
  friend Modular operator*(Modular a, const Modular &b) { return a *= b; }
  friend Modular operator/(Modular a, const Modular &b) { return a /= b; }
  friend Modular operator+(long long a, const Modular &b) { return Modular(a) += b; }
  friend Modular operator-(long long a, const Modular &b) { return Modular(a) -= b; }
  friend Modular operator*(long long a, const Modular &b) { return Modular(a) *= b; }
  friend Modular operator/(long long a, const Modular &b) { return Modular(a) /= b; }

  friend istream &operator>>(istream &is, Modular &a) { long long v; is >> v; a = v; return is; }
  friend ostream &operator<<(ostream &os, const Modular &a) {
    os << a.value; return os;
  }

  friend bool operator==(const Modular &a, const Modular &b) { return a.value == b.value; }
  friend bool operator!=(const Modular &a, const Modular &b) { return a.value != b.value; }
};

const int md = 1e9 + 7;
typedef Modular<md> Mint;
       
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
  poly(const vector<Mint> &v) {
    a = v;
  }
#if __cplusplus >= 201103L
  poly(const initializer_list<Mint> &l) {
    a = l;
  }
#endif

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
};

poly operator*(const poly &a, const Mint &b) {
  poly ans = a;
  for (int i = 0; i < ans.size(); i++) {
    ans[i] *= b;
  }
  return ans;
}
poly operator*(const Mint &a, const poly &b) { return b * a; }
poly operator*(const poly &a, const poly &b) {
  int n = a.deg(), m = b.deg();
  poly c(n + m + 1);
  for (int i = 0; i < c.size(); i++) {
    c[i] = 0;
    for (int j = 0; j <= i; j++) {
      c[i] += a[j] * b[i - j];
    }
  }
  return c;
}
poly &operator*=(poly &a, const Mint &b) {
  return a = a * b;
}
poly &operator*=(poly &a, const poly &b) {
  return a = a * b;
}

poly operator/(const poly &a, const Mint &b) {
  poly ans = a;
  for (int i = 0; i < ans.size(); i++) {
    ans[i] /= b;
  }
  return ans;
}
poly &operator/=(poly &a, const Mint &b) {
  return a = a / b;
}

poly operator+(const poly &a, const Mint &b) {
  poly ans = a;
  ans[0] += b;
  return ans;
}
poly operator+(const Mint &a, const poly &b) {
  return b + a;
}
poly operator+(const poly &a, const poly &b) {
  poly c(max(a.size(), b.size()));   
  for (int i = 0; i < c.size(); i++) {
    c[i] = a[i] + b[i];
  }
  return c;
}
poly &operator+=(poly &a, const Mint b) {
  return a = a + b;
}
poly &operator+=(poly &a, const poly &b) {
  return a = a + b;
}

ostream &operator<<(ostream &stream, const poly &f) {
  stream << "{";
  for (int i = 0; i < f.size(); i++) {
    if (i) stream << ", ";
    stream << f[i];
  }
  stream << "}";
  return stream;
}
       
const int N = 233;
Mint pow_sum[N], mul[N];
poly prep[N], sufp[N];
// prep[i] = (x - 1) * (x - 2) * ... * (x - i)
// prep[0] = 1
// sufp[i] = (x - i) * (x - (i+1)) * ... (x - (k+2))
// sufp[k + 3] = 1

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int k, w;
  cin >> k >> w;
  Mint n = 1;
  vector<int> p(w), a(w);
  for (int i = 0; i < w; i++) {
    cin >> p[i] >> a[i];
    n *= power(Mint(p[i]), a[i]);
  }
  auto calc = [&](int i, int j) {
    return power(power(Mint(p[i]), a[i]), j) - power(Mint(p[i]), k) * power(power(Mint(p[i]), a[i] - 1), j);
  };

  poly pow_f;
  {                   
    prep[0] = {1};
    for (int i = 1; i <= k + 2; i++) {
      prep[i] = prep[i - 1] * (poly) {-Mint(i), 1};
    }
    sufp[k + 3] = {1};
    for (int i = k + 2; i >= 1; i--) {
      sufp[i] = sufp[i + 1] * (poly) {-Mint(i), 1};
    }
    mul[0] = 1;
    for (int i = 1; i <= k + 2; i++) {
      mul[i] = mul[i - 1] * Mint(i);
    }
    pow_sum[0] = 0;
    for (int i = 1; i <= k + 2; i++) {
      pow_sum[i] = pow_sum[i - 1] + power(Mint(i), k);
    }       
    for (int i = 1; i <= k + 2; i++) {
      pow_f += pow_sum[i] * prep[i - 1] * sufp[i + 1] / mul[i - 1] / mul[k + 2 - i] * Mint(((k + 2 - i) & 1) ? -1 : 1); 
    }
  }
//  cerr << pow_f << '\n';

  Mint ans = 0;
  for (int i = 0; i <= k + 1; i++) {
    Mint tmp = 1;
    for (int j = 0; j < w; j++) {
      tmp *= calc(j, i);
    } 
//    cerr << tmp << " ";
    ans += tmp * pow_f[i];
  }
//  cerr << '\n';
  cout << ans << '\n';                                    
  return 0;
}