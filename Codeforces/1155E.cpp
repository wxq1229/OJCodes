#include <bits/stdc++.h>

using namespace std;

const int n = 11, MOD = (int) 1e6 + 3;
int x[23], y[23];

inline int qpow(int a, int b = MOD - 2) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD, b >>= 1;
  }
  return ans;
}

int inv[23], mul_inv[23];

int calc(int x0) {
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int tmp = 1;
    for (int j = 0; j < n; j++) if (j != i) {
    	tmp = 1ll * tmp * (x0 - x[j] + MOD) % MOD;
    }
  	ans += 1ll * y[i] * tmp % MOD * mul_inv[i] % MOD;
  	if (ans >= MOD) ans -= MOD;
  }
  return ans;
}

int main() {  
  for (int i = 1; i <= n; i++) inv[i] = qpow(i);
  for (int i = 0; i < n; i++) {
    mul_inv[i] = 1;
    for (int j = 0; j < n; j++) if (i != j) {
      int tmp = i - j < 0 ? MOD - inv[j - i] : inv[i - j];
      mul_inv[i] = 1ll * mul_inv[i] * tmp % MOD;
    }
  }
  for (int i = 0; i < n; i++) {
    printf("? %d\n", i);      
    fflush(stdout);
    x[i] = i, scanf("%d", y + i);
  }
  for (int i = 0; i < MOD; i++) if (calc(i) == 0) {
    printf("! %d\n", i);      
    fflush(stdout);
    return 0;
  }
  printf("! -1\n");
  fflush(stdout);
  return 0;
}
