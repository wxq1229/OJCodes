#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i = (int)(a); i <= (int)(b); ++i)
#define ROF(i,a,b) for (int i = (int)(a); i >= (int)(b); --i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using ll = long long;
using vi = vector<int>;

const int P = 998244353, N = 1e5 + 10;
void upd(int &x,int y) { x += y; if (x >= P) x -= P; }

struct Opt { int t, p, v; } op[N];
int n, m, Q, a[N];
vi g[N], gr[N];
int ind[N], outd[N];
int mul[N], dp[N], add[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	FOR(i,1,n) cin >> a[i];
	cin >> m;
	FOR(i,1,m) {
		cin >> op[i].t;
		if (op[i].t == 1) cin >> op[i].p >> op[i].v;
		else if (op[i].t == 2) cin >> op[i].v;
		else {
			cin >> op[i].p;
			FOR(_,1,op[i].p) {
				int j; cin >> j; 
				g[i].pb(j);
				gr[j].pb(i);
				++ind[j];
				++outd[i];
			}
		}
	}
	const int S = m + 1;
	cin >> Q;
	FOR(i,1,Q) {
		int u; cin >> u;
		g[S].pb(u);
		gr[u].pb(S);
		++ind[u];
		++outd[S];
	}
	FOR(i,1,m+1) mul[i] = 1;
	queue<int> q;
	FOR(i,1,m+1) if (!outd[i]) {
		q.push(i);
		if (op[i].t == 2) mul[i] = op[i].v;
	}
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (auto v:gr[u]) {
			mul[v] = (ll) mul[v] * mul[u] % P;
			if (--outd[v] == 0) q.push(v);
		}
	}
	FOR(i,1,m+1) {
		reverse(g[i].begin(), g[i].end());
	}
	vi tps;
	FOR(i,1,m+1) if (ind[i] == 0) q.push(i);
	while (q.size()) {
		int u = q.front();
		q.pop();
		tps.pb(u);
		for (auto v:g[u])
			if (--ind[v] == 0) q.push(v);
	}
	dp[S] = 1;
	for (auto u:tps) {
		int cm = 1;
		for (auto v:g[u]) {
			upd(dp[v], (ll) dp[u] * cm % P);
			cm = (ll) cm * mul[v] % P;
		}
	}
	FOR(i,1,m) if (op[i].t == 1) {
		// if (op[i].p == 291) {
			// cerr << "upd 291 " << dp[i] << '\n';
		// }
		upd(add[op[i].p], (ll) op[i].v * dp[i] % P);
	}
	FOR(i,1,n) cout << ((ll) mul[S] * a[i] + add[i]) % P << " ";
	cout << '\n'; 
	return 0;
}