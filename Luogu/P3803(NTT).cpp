#include <bits/stdc++.h>
using namespace std;

const int N = 3e6 + 10, P = 998244353, G = 3, IG = (P+1) / G;

#define add(x, y) ((x) + (y) >= P ? (x)+(y) - P : (x) + (y))
#define sub(x, y) ((x) - (y) < 0 ? (x)-(y) + P : (x) - (y))

int fpow(int a, int b) {
	int ret = 1; for (a %= P; b; b >>= 1, a = 1ll * a * a % P)
		if (b & 1) ret = 1ll * ret * a % P;
	return ret;
}

int rev[N];
void ntt(int *f, int n, int flg) {
	for (int i = 0; i < n; i++)
		if (rev[i] < i) swap(f[i], f[rev[i]]);
	for (int len = 2, k = 1; len <= n; len <<= 1, k <<= 1) {
		int wn = fpow(flg==1 ? G : IG, (P-1)/len);
		for (int i = 0; i < n; i += len) {
			for (int w = 1, j = i; j < i + k; j++, w = 1ll * w * wn % P) {
				int tmp = 1ll * w * f[j + k] % P;
				f[j + k] = sub(f[j], tmp), f[j] = add(f[j], tmp);
			}
		}
	}
}

int n, m, f[N], g[N];

int main() {
#ifdef WXQ
	freopen("A.in", "r", stdin);
#endif
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%d", f + i);
	for (int i = 0; i <= m; i++) scanf("%d", g + i);
	int limit = 1; while (limit <= n + m) limit <<= 1;
	for (int i = 0; i < limit;i++) rev[i] = rev[i>>1] >> 1 | ((i&1) ? limit>>1 : 0);
	ntt(f, limit, 1), ntt(g, limit, 1);
	for (int i = 0; i < limit; i++) f[i] = 1ll * f[i] * g[i] % P;
	ntt(f, limit, -1); int inv = fpow(limit, P - 2);
	for (int i = 0; i <= n+m; i++) printf("%d ", 1ll * f[i] * inv % P);
	return 0;
}
