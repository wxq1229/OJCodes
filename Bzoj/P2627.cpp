// ** Luogu

#include <bits/stdc++.h>

using namespace std;

template <typename A, typename B>
ostream& operator<<(ostream& stream, const pair<A, B>& p) {
  return stream << "{" << p.first << ',' << p.second << "}";
}
template <typename T>
ostream& operator<<(ostream& stream, const vector<T>& a) {
  stream << "{";
  bool fst = 1;
  for (auto v : a) {
    if (fst) fst = 0;
    else stream << ", ";
    stream << v;
  }
  stream << "}";
  return stream;
}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
                          
namespace Factor {            
  ll add(ll a, ll b, ll md) {
    a += b;
    if (a >= md) a -= md;
    return a;
  }
  ll mul(ll a, ll b, ll md) {
    ll ret = (a * b - (ll) ((ld) a / md * b + 1e-7) * md) % md;
    if (ret < 0) ret += md;
    return ret;
  }
  ll power(ll a, ll b, ll md) {
    ll ans = 1;
    while (b) {
      if (b & 1) {
        ans = mul(ans, a, md);
      }
      b >>= 1;
      a = mul(a, a, md);
    }
    return ans;
  }      
  ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
  }

  bool miller(ll n) {
    if(n < 2) return false;
    if (n == 2 || n == 3 || n == 5 || n == 7) return true;
    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;
    const vector<int> pr = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    ll s = n - 1;
    int d = 0;
    while (~s & 1) s >>= 1, ++d;
    for (auto p : pr) {
      if (n == p) return true;
      if (n != p && n % p == 0) {
        return false;
      }
      ll x = power(p % n, s, n);
      for (int it = 0; it < d; it++) {
        ll y = mul(x, x, n);
        if (y == 1 && x != 1 && x != n - 1) {
          return false;
        }
        x = y;
      }
      if (x != 1) return false;
    }
    return true;
  }

  mt19937_64 rng((ull) chrono::system_clock::now().time_since_epoch().count());
  ll rho(ll n) { 
    const int c = rng() % 10 + 3;
    auto g = [&](ll x) {
      return add(mul(x, x, n), c, n);
    };
    ll x = rng() % (n - 2) + 1;
    for (int k = 1; ; k <<= 1) {                        
       ll y = x, ml = 1;  
       for (int it = 1; it <= k; it++) {
         y = g(y);
         ml = mul(ml, abs(x - y), n);
         if (it % 127 == 0) {     
           ll d = gcd(ml, n);
           if (d > 1) return d;
         }
       }   
       ll d = gcd(ml, n);
       if (d > 1) return d;
       x = y;
    }
  }

  vector<ll> pr;
  void fact(ll n) {
    if (n == 1) return;
    if (miller(n)) {
      pr.push_back(n);
      return;
    }
    ll d = rho(n);
    while (d == n) d = rho(n);
    fact(d), fact(n / d);
  }

  vector<pair<ll, int>> factor(ll n) {
    pr.clear(); fact(n);
    map<ll, int> cnt;
    vector<pair<ll, int>> d;
    for (auto p : pr) ++cnt[p];
    for (auto it : cnt) d.push_back(it);
    return d;  
  }
}
using Factor::factor;

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
                                     
const int md = 1e9 + 7;
using Mint = Modular<integral_constant<int, md>>;

const int N = 3333;
Mint coeff[N][N], B[N], comb[N][N];

void init() {
  int n = 3000;
  comb[0][0] = 1;
  for (int i = 1; i <= n + 1; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
    }
  }
  B[0] = 1;
  for (int i = 1; i <= n; i++) {
    B[i] = 0;
    for (int j = 0; j < i; j++) {
      B[i] += comb[i + 1][j] * B[j];
    }
    B[i] *= -1 / Mint(i + 1);
  }
  for (int i = 0; i <= n; i++) {
    Mint inv = inverse(Mint(i + 1));
    for (int j = 1; j <= i + 1; j++) {
      coeff[i][j] = inv * comb[i + 1][j] * B[i + 1 - j];
    }
    if (i) ++coeff[i][i];
  }
}
                                                      
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  init();
  int tt;
  cin >> tt;
  while (tt--) {
    ll n; int x, y;
    cin >> n >> x >> y;
    vector<pair<ll, int>> d = factor(n);
    //cerr << n << ": " << d << endl;

    auto calc = [&](int k) {
      auto f = [&](ll p, int e) {
        Mint ans = 0;
        for (int i = 0; i < 2; i++) {
          ll pw = i ? p : 1;
          Mint tmp = 0;
          for (int j = 0; j <= e - i; j++) {
            tmp += power(power(Mint(p), j), x) * power(power(Mint(p), e - i - j), k);
          }
          ans += tmp * ((i & 1) ? -1 : 1) * power(Mint(pw), y);
        }
        return ans;
      };
      Mint ans = 1;
//      cerr << n << ": " <<  d << '\n';
      for (auto pr : d) ans *= f(pr.first, pr.second);
      return ans;
    };


    Mint ans = 0;
    for (int i = 0; i <= y + 1; i++) {
      //cerr << i << " " << coeff[y][i] << " * " << calc(i) << endl;
      ans += calc(i) * coeff[y][i];
    }
    //cerr << ans << endl;
    cout << ans * power(Mint(n), y) << '\n';
  }
  return 0;
}