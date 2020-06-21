#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 10, md = 1e9 + 7, i2 = (md + 1) / 2, i6 = (md + 1) / 6;

inline int add(int a, int b) {
  a += b;
  if (a >= md) a -= md;
  return a;
}
inline int sub(int a, int b) {
  a -= b;
  if (a < 0) a += md;
  return a;
}
                                               
template <typename T>
inline int sqr(T x) {
  x %= md;
  return 1ll * x * x % md;
}
template <typename T>
inline int sum1(T n) {
  n %= md;                
  return 1ll * n * (n + 1) % md * i2 % md;
}              
template <typename T>
inline int sum2(T n) {
  n %= md;
  return 1ll * n * (n + 1) % md * (2ll * n + 1) % md * i6 % md;
}

bool vis[N];
int ps[N], pn, sp1[N], sp2[N];

void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) {
      ++pn;
      ps[pn] = i;
    }
    for (int j = 1; j <= pn && i * ps[j] <= n; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) {
        break;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    sp1[i] = add(sp1[i - 1], ps[i]);
    sp2[i] = add(sp2[i - 1], sqr(ps[i]));
  }
}

int rid[2][N], sqn, tot;
long long n, val[N];
inline int id(long long v) {
  if (v <= sqn) return rid[0][v];
  else return rid[1][n / v];
}

int g1[N], g2[N];

inline int get_g(long long n) {
  int i = id(n);
  return sub(g2[i], g1[i]);
}
inline int get_sp(int k) {
  return sub(sp2[k], sp1[k]);
}

int S(long long n, int k) {
  if (ps[k] >= n) return 0;
//  cerr << "S(" << n << ',' << k << ")\n";
  int ans = sub(get_g(n), get_sp(k));
  for (int i = k + 1; i <= pn && 1ll * ps[i] * ps[i] <= n; i++) {
    long long pw = ps[i];
    for (int e = 1; pw <= n; e++, pw *= ps[i]) {
      int pm = pw % md;
      ans = add(ans, 1ll * pm * (pm - 1) % md * add(S(n / pw, i), e > 1) % md); 
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  double STIME = clock();
#endif
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  sqn = (int) sqrt(n);
  sieve(sqn);
  for (long long l = 1, r = 0; l <= n; l = r + 1) {
    r = n / (n / l);
    ++tot;
    val[tot] = n / l;           
    long long v = val[tot];
    if (v <= sqn) rid[0][v] = tot;
    else rid[1][n / v] = tot;
  	g1[tot] = sub(sum1(v), 1);
  	g2[tot] = sub(sum2(v), 1);
  }
  for (int k = 1; k <= pn; k++) {
    for (int i = 1; i <= tot; i++) {
      if (1ll * ps[k] * ps[k] > val[i]) continue;
      int j = id(val[i] / ps[k]);
      g1[i] = sub(g1[i], 1ll * ps[k] * sub(g1[j], sp1[k - 1]) % md);
      g2[i] = sub(g2[i], 1ll * sqr(ps[k]) * sub(g2[j], sp2[k - 1]) % md); 
    }
  }
  cout << add(S(n, 0), 1) << '\n';
#ifdef LOCAL
  cerr << "Time used: " << clock() - STIME << " ms\n";
#endif
  return 0;
}