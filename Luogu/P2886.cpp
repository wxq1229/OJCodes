#include <bits/stdc++.h>
using namespace std;
template <class T> inline T Rd() {
	T x = 0, f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) f = ch == '-' ? -f : f;
	for (; isdigit(ch); ch = getchar()) x = (x<<1) + (x<<3) + (ch^48);
	return x * f;
}
#define read() Rd<int>()
#define readll() Rd<long long>()
const int INF = 0x3f3f3f3f;
struct Matrix {
	int a[250][250], n, m;
	void init(int R, int C, int val = INF) {
		n = R, m = C;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) a[i][j] = val;
	}
	Matrix() { }
	Matrix(int R, int C, int val = INF) { init(R, C, val); }
	Matrix operator * (const Matrix &k1) const {
		Matrix ret(this->n, k1.m);
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= k1.m; j++)
				for (int k = 1; k <= k1.n; k++)
					ret.a[i][j] = min(ret.a[i][j], a[i][k] + k1.a[k][j]);
		return ret;
	}
} G;
Matrix fpow(Matrix M, int t) {
	Matrix ret = M; t--;
	for (; t; t >>= 1, M = M * M)
		if (t & 1) ret = ret * M;
	return ret;
}
int id[1000010], cnt = 0, n, m, S, T;
int main() {
	n = read(), m = read(), S = read(), T = read();
	G.init(m * 2, m * 2);
	for (int i = 1; i <= m; i++) {
		int w = read(), x = read(), y = read();
		id[x] = id[x] ? id[x] : ++cnt;
		id[y] = id[y] ? id[y] : ++cnt;
		int u = id[x], v = id[y];
		G.a[u][v] = min(w, G.a[u][v]);
		G.a[v][u] = min(w, G.a[v][u]);
	}
	G.n = cnt, G.m = cnt;
	G = fpow(G, n);
	printf("%d\n", G.a[id[S]][id[T]]);
	return 0;
}
