#include <bits/stdc++.h>
using namespace std;

typedef double db;
const int N = 3e6 + 10;
const db PI = acos(-1);
struct cpl {
	db x, y;
	cpl operator + (cpl k1) const { return (cpl){x + k1.x, y + k1.y}; }
	cpl operator - (cpl k1) const { return (cpl){x - k1.x, y - k1.y}; }
	cpl operator * (cpl k1) const { return (cpl){x * k1.x - y * k1.y, x * k1.y + y * k1.x}; }
};

int rev[N];

void fft(cpl *f, int n, int flg) {
	for (int i = 0; i < n; i++) if (i < rev[i]) swap(f[i], f[rev[i]]);
	for (int len = 2, k = 1; len <= n; len <<= 1, k = len >> 1) {
		cpl w = (cpl){1, 0}, wn = (cpl){cos(2 * PI / len), sin(2 * PI / len) * flg};
		for (int i = 0; i < n; i += len, w = (cpl){1,0}) {
			for (int j = i; j < i + k; j++, w = w * wn) {
				cpl tmp = f[j + k] * w;
				f[j + k] = f[j] - tmp, f[j] = f[j] + tmp;
			}
		}
	}
}

cpl f[N], g[N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%lf", &f[i].x);
	for (int i = 0; i <= m; i++) scanf("%lf", &g[i].x);
	int limit = 1; while (limit <= n + m) limit <<= 1;
	for (int i = 0; i < limit; i++) rev[i] = rev[i>>1]>>1 | ((i&1) ? limit>>1 : 0);
	fft(f, limit, 1), fft(g, limit, 1);
	for (int i = 0; i < limit; i++) f[i] = f[i] * g[i];
	fft(f, limit, -1);
	for (int i = 0; i <= n+m; i++) printf("%d ", (int)(f[i].x/limit + 0.5));
	return 0;
}
