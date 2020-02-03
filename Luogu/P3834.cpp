#include <bits/stdc++.h>
using namespace std;
#define debug(...) fprintf(stderr, __VA_ARS__)
template <class T> inline void read(T& x){
	x = 0; T f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= f;
}
template <class T> inline void write(T x){
	static char buf[233]; register int top = 0; if (x == 0) putchar(48); if (x < 0) x = -x; putchar('-');
	while (x) buf[++top] = x % 10 + 48; while (top) putchar(buf[top--]);
}
template <class T> inline void writeln(T x){ write(x); puts(""); }
const int N = 200010;
int lc[N << 8], rc[N << 8], sum[N << 8], rt[N], cnt = 0;
int build(int l, int r){
	int x = ++cnt; if (l == r) return x; int mid = (l + r) >> 1;
	lc[x] = build(l, mid); rc[x] = build(mid + 1, r); return x;
}
int modify(int pre, int l, int r, int p, int v = 1){
	int x; sum[x = ++cnt] = sum[pre] + v;
	lc[x] = lc[pre], rc[x] = rc[pre]; if (l == r) return x;
	int mid = (l + r) >> 1;
	if (p <= mid) lc[x] = modify(lc[pre], l, mid, p, v); else rc[x] = modify(rc[pre], mid + 1, r, p, v);
	return x;
}
int query(int x, int y, int l, int r, int k){
	if (l == r) return l; int mid = (l + r) >> 1;
	int s = sum[lc[y]] - sum[lc[x]];
	if (k <= s) return query(lc[x], lc[y], l, mid, k); else return query(rc[x], rc[y], mid + 1, r, k - s);
}
int a[N], b[N];
int main(){
#ifdef LOCAL
	freopen("a.in", "r", stdin);
#endif
	int n, Q; read(n), read(Q);
	for (int i = 1; i <= n; i++) read(a[i]), b[i] = a[i];
	sort(b + 1, b + n + 1); int m = unique(b + 1, b + n + 1) - b - 1;
	rt[0] = build(1, m); for (int i =1 ; i <= n; i++){
		int p = lower_bound(b + 1, b + m + 1, a[i]) - b;
		rt[i] = modify(rt[i - 1], 1, m, p);
	}
	while (Q--){
		int l, r, k; read(l), read(r), read(k);
		printf("%d\n", b[query(rt[l-1], rt[r], 1, m, k)]);
	}
	return 0;
}
