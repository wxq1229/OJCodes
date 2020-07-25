#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i = (int)(a); i <= (int)(b); i++)
#define ROF(i,a,b) for (int i = (int)(a); i >= (int)(b); i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second 
typedef pair<int,int> pii;

const int N = 1e5 + 10;
int n, m, need;
struct edge {
	int u, v, w;
	bool col;

	bool operator<(const edge& o) const { return w<o.w || (w==o.w && col>o.col); }
} e[N], es[N];

int fa[N];
int find(int u) { return u==fa[u] ? u : fa[u]=find(fa[u]); }
void init() { FOR(i,1,n) fa[i] = i; }	

pii kruskal() {
	init(); sort(es + 1, es + m + 1);
	int white = 0, tot = n, sum = 0;;
	FOR(i,1,m) {
		int u = es[i].u, v = es[i].v, pu = find(u), pv = find(v);
		if (pu == pv) continue;
		fa[pu] = pv;
		white += es[i].col == 0;
		sum += es[i].w;
		if (--tot == 1) break;
	}
	return mp(white, sum);
}

pair<bool,int> check(int mid) {
	FOR(i,1,m) {
		es[i] = e[i];
		if (es[i].col == 0) es[i].w -= mid;
	}
	pii res = kruskal();
	return mp(res.fi <= need, res.se);
}

int main() {
	cin>>n>>m>>need;
	FOR(i,1,m) {
		cin>>e[i].u>>e[i].v>>e[i].w>>e[i].col;
		++e[i].u, ++e[i].v;
	}
	int lo=-100, hi=100, ans = -1, p = -1;
	while (lo<=hi) {
		int mid = (lo+hi)>>1;
		pair<bool,int> chk = check(mid);
		if (chk.fi) { lo = mid+1; ans = chk.se; p = mid; }
		else hi = mid-1;
	}
	cout << ans+need*p << '\n';
	return 0;
}