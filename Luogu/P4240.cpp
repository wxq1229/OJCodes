#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5, N = maxn+10, mod = 998244353, maxb = 33;
typedef long long ll;

bool vis[N];
int ps[N], pn, mu[N], phi[N], inv[N];

int f[N];
vector<int> g[N], h[maxb + 10][maxb + 10];

void init() {
	int n = maxn; inv[1] = 1;
	for (int i = 2; i <= n; i++) inv[i] = 1ll * inv[mod%i] * (mod-mod/i) % mod;
	phi[1] = mu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			ps[pn++] = i;
			mu[i] = -1;
			phi[i] = i-1;
		}
		for (int j = 0; j < pn && i * ps[j] <= n; j++) {
			vis[i * ps[j]] = 1;
			if (i%ps[j] == 0) {
				mu[i*ps[j]] = 0;
				phi[i*ps[j]] = phi[i] * ps[j];
				break;
			}
			mu[i*ps[j]] = -mu[i];
			phi[i*ps[j]] = phi[i]*(ps[j]-1);
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j+=i) {
			f[j] += 1ll * mu[j/i] * i % mod * inv[phi[i]] % mod;
			if (f[j] >= mod) f[j] -= mod;
			if (f[j] < 0) f[j] += mod;
		}
	for (int i = 1; i <= n; i++) {
		int lim = n / i;
		g[i] = vector<int>(lim + 1);
		g[i][0] = 0;
		for (int j = 1; j <= lim; j++) {
			g[i][j] = g[i][j-1] + phi[i*j];
			if (g[i][j] >= mod) g[i][j] -= mod;
      if (g[i][j] < 0) g[i][j] += mod;
		}
	}
	
	for (int a = 1; a <= maxb; a++) {
		for (int b = 1; b <= maxb; b++) {
			int lim = min(n/a, n/b);
			auto &now = h[a][b];
			now = vector<int>(lim + 1);
			now[0] = 0;
			for (int i = 1; i <= lim; i++) {
				now[i] = now[i-1] + 1ll * g[i][a] * g[i][b] % mod * f[i] % mod;
				if (now[i] >= mod) now[i] -= mod;
        if (now[i] < 0) now[i] += mod;
			}
		}
	}
}

int solve(int n, int m) {
	int ans = 0; if (n > m) swap(n,m);
  for (int i = 1; i <= m/maxb; i++) {
    ans += 1ll * g[i][n/i] * g[i][m/i] % mod * f[i] % mod;
    if (ans >= mod) ans -= mod;
  }
	for (int l = m/maxb + 1, r = 0; l <= n; l = r+1) {
		r = min(n/(n/l), m/(m/l)); ans += (h[n/l][m/l][r] - h[n/l][m/l][l-1] + mod) % mod;
		if (ans >= mod) ans -= mod;
	}
	return ans;
}

int main() {
	init();
	int _, n, m; for (scanf("%d", &_); _; _--) {
		scanf("%d%d", &n, &m);
		printf("%d\n", solve(n,m));
	}
	return 0;
}
