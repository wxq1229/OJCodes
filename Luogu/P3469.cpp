#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10, M = 5e5 + 10;

int n, m;
int fst[N], nxt[M<<1], to[M<<1], cnt = 0;
inline void ade(int x, int y){
	to[++cnt] = y, nxt[cnt] = fst[x], fst[x] = cnt;
}
inline void addedge(int x, int y){
	ade(x,y), ade(y,x);
}

int tim=0, dfn[N], low[N], size[N];
ll ans[N];
void tarjan(int x){
	dfn[x] = low[x] = ++tim, size[x] = 1;
	int flg = 0, sum = 0;
	for (int i=fst[x]; i; i=nxt[i]){
		int v = to[i];
		if (!dfn[v]) {
			tarjan(v), size[x] += size[v];
			low[x] = min(low[x], low[v]);
			if (low[v] >= dfn[x]){
				flg = 1;
				ans[x] += 1ll * size[v] * sum;
				sum += size[v];
			}
		}
		else low[x] = min(low[x], dfn[v]);
	}
	if (flg) ans[x] += 1ll * (n - sum - 1) * sum + n - 1;
	else ans[x] = n - 1;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		int x, y; scanf("%d%d", &x, &y);
		addedge(x,y);
	}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]<<1);
	return 0;
}
