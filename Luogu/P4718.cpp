#include <bits/stdc++.h>   

using namespace std; 
     
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

  ll mxp;
  void factor(ll n) {
    if (n == 1) return;
    if (miller(n)) {
      mxp = max(mxp, n);
      return;
    }
    ll d = rho(n);
    while (d == n) d = rho(n);
    factor(d), factor(n / d);
  }
}
using Factor::mxp;
using Factor::factor;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    ll n;
    cin >> n;
    mxp = 0;
    factor(n);                                       
    if (mxp == n) cout << "Prime\n";
    else cout << mxp << '\n';
  }
  return 0;
}