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
using Mint = Modular<integral_constant<decay<decltype(md)>::type, md>>;

const int N = 333;

Mint fac[N], ifac[N];
void gen_fac(int n) {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) {
    fac[i] = fac[i - 1] * i;
  }                      
  ifac[n] = inverse(fac[n]);
  for (int i = n - 1; i >= 0; i--) {
    ifac[i] = ifac[i + 1] * (i + 1);
  }                                                                 
}                         
Mint comb(int n, int r) {
  if (n < 0 || r < 0 || n - r < 0) return 0;
  return fac[n] * ifac[r] * ifac[n - r];
}

int dec(int x) {                   
  int ret = 1;
  for (int i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      int cnt = 0;
      while (x % i == 0) ++cnt, x /= i;
      if (cnt & 1) ret *= i;
    }
  }
  if (x != 1) ret *= x;
  return ret;         
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  gen_fac(n);      
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i] = dec(a[i]);
  }                         
  vector<int> group;
  {
    vector<int> ta = a;
    sort(ta.begin(), ta.end());
    ta = vector<int>(ta.begin(), unique(ta.begin(), ta.end()));
    for (int i = 0; i < n; i++) {
      a[i] = lower_bound(ta.begin(), ta.end(), a[i]) - ta.begin();
    }       
    group = vector<int>(ta.size());
    for (int i = 0; i < n; i++) {
      ++group[a[i]];
    }                       
  }                   
  vector<Mint> dp(n + 1);
  dp[0] = 1;   
  for (auto gcnt : group) {
    vector<Mint> new_dp(n + 1);
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= min(i, gcnt); j++) {
        new_dp[i] += comb(gcnt - 1, j - 1) * fac[gcnt] * ifac[j] * dp[i - j];
      }
    }                      
    swap(dp, new_dp);  
  }
  Mint ans = 0, coeff = 1;
  for (int i = n; i >= 1; i--) {
    ans += coeff * dp[i] * fac[i];
    coeff *= -1;
  }
  cout << ans << '\n';
  return 0;
}
