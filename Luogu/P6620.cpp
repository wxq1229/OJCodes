#include <bits/stdc++.h>

using namespace std;

const int N = 2010;

int n, x, p, m;
int comb[N][N];

struct poly {
  int a[N];
  inline int &operator[](int i) { return a[i]; }   
  inline int operator[](int i) const { return a[i]; }
  poly() {
    for (int i = 0; i <= m; i++) a[i] = 0;
  }         
};


ostream &operator<<(ostream &os, const poly &f) {
  os << "{";
  for (int i = 0; i <= m; i++) {
    os << f[i];
    if (i == m) os << '}'; else os << ", ";
  }
  return os;
}

poly operator*(const poly &a, const poly &b) {
  static int tmp[N], ta[N], tb[N];
  // cerr << a << " * " << b << "= ";
  for (int i = 0; i <= m; i++) ta[i] = a[i], tb[i] = b[i];
  for (int i = 0; i <= m; i++) {
    tmp[i] = 0;
    for (int j = 0; j <= i; j++) {                                      
      (tmp[i] += 1ll * comb[i][j] * ta[j] % p * tb[i - j] % p) %= p;
    }
  }
  poly c;
  for (int i = 0; i <= m; i++) c[i] = tmp[i];
  // cerr << c << '\n';
  return c;
}                   

poly f, ans;

int main() {
#ifdef LOCAL
  double STIME = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> x >> p >> m;
  comb[0][0] = 1;
  for (int i = 1; i <= m; i++) {
    comb[i][0] = 1;
    for (int j = 1; j <= i; j++) {
      comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % p;
    }
  }              
  for (int i = 0; i <= m; i++) {
    f[i] = x;
    if (!i) f[i] = (f[i] + 1) % p;
  }
  ans[0] = 1;
  for (; n; n >>= 1, f = f * f) {
    if (n & 1) ans = ans * f;
  }               
  int res = 0;
  for (int i = 0; i <= m; i++) {
    int ai;
    cin >> ai;
    (res += 1ll * ai * ans[i] % p) %= p;
  }                    
  cout << res << '\n';
#ifdef LOCAL
  cerr << "\nTime used: " << clock() - STIME << " ms\n";
#endif
  return 0;
}