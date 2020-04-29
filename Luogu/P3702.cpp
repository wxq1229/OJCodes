#include <bits/stdc++.h>

using namespace std;

const int N = 210, mod = 20170408;

int p;

struct poly {
  int a[N];
  poly() { memset(a, 0, sizeof(a)); }
  
  inline int &operator [] (int i) { return a[i]; }
  inline int operator [] (int i) const { return a[i]; }
  
  poly operator * (const poly &o) const {
    static int A[N];
    for (int i = 0; i <= p * 2; i++) A[i] = 0;
    for (int i = 0; i < p; i++)
      for (int j = 0; j < p; j++) {
        int k = (i+j) % p; A[k] += 1ll * a[i] * o[j] % mod;
        if (A[k] >= mod) A[k] -= mod;
      }
    poly ans;
    for (int i = 0; i < p; i++) ans[i] = A[i];
    return ans;
  }
};

poly qpow(poly A, int n) {
  poly ans; ans[0] = 1;
  for (; n; n >>= 1, A = A * A)
    if (n & 1) ans = ans * A;
  return ans;
}

vector<int> ps;
bool vis[20000010];

void sieve(int n) {
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) ps.push_back(i);
    for (auto j : ps) {
      if (i * j > n) break;
      vis[i*j] = 1; if (i % j == 0) break;
    }
  }
}

int n, m;
poly A, B, ans1, ans2;

int main() {
  scanf("%d%d%d", &n, &m, &p);
  sieve(m);
  for (int i = 1; i <= m; i++) ++A[i % p], ++B[i % p];
  for (auto pr : ps) --B[pr % p];
  ans1 = qpow(A, n), ans2 = qpow(B, n);
  printf("%d\n", (ans1[0] - ans2[0] + mod) % mod);
  return 0;
}
