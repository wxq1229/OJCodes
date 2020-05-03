#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a; i<n; i++)
#define per(i,a,n) for (int i=n-1; i>=a; i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef pair<int,int> pii;
typedef long long ll;
typedef vector<int> VI;

const int N = 601, SIGMA = 26;

struct node {
	short fail,go[SIGMA];
	int s;
	void clear() {
		fail = s = 0;
		memset(go,0,sizeof(go));
	}
} t[N];
short root, cnt;

void init() { root = cnt = 0; t[root].clear(); }
short newnode() { short u=++cnt; t[u].clear(); return u; }
short append(short u,short c) {
	if (!t[u].go[c]) t[u].go[c] = newnode();
	return t[u].go[c];
}

void build() {
	queue<short> q; short u=root;
	rep(i,0,SIGMA) if (t[u].go[i]) {
		t[t[u].go[i]].fail = u;
		q.push(t[u].go[i]);
	}
	while (q.size()) {
		short u = q.front(); q.pop();
		t[u].s |= t[t[u].fail].s;
		rep(i,0,SIGMA) {
			short &v = t[u].go[i];
			if (!v) v = t[t[u].fail].go[i];
			else t[v].fail = t[t[u].fail].go[i], q.push(v);
		}
	}
}

int ALL;
pii lst[N][1<<12];
short lstch[N][1<<12];

void print(pii u) {
	pii S = mp(root,0);
	string ans="";
	while (u != S) {
		ans.pb(lstch[u.fi][u.se] + 'A');
		u = lst[u.fi][u.se];
	}
	reverse(all(ans));
	printf("%s\n", ans.c_str());
}

void solve() {
	memset(lstch,-1,sizeof(lstch));
	queue<pii> q;
	q.push(mp(root,0));
	lstch[root][0] = 0;
	while (q.size()) {
		pii u = q.front(); q.pop();
		if (u.se==ALL) {print(u); return;}
		rep(i,0,SIGMA) {
			short nxt = t[u.fi].go[i];
			pii v = mp(nxt,u.se|t[nxt].s);
			if (lstch[v.fi][v.se]==-1) {
				// cerr << "(" << u.fi << ',' << u.se << ") -> (" << v.fi << "," << v.se << ")\n";
				q.push(v);
				lst[v.fi][v.se]=u, lstch[v.fi][v.se]=i;
			}
		}
	}
}

inline char readch() {
	char ch=getchar();
	while (isspace(ch)) ch=getchar();
	return ch;
}

int main() {
	int n; scanf("%d",&n);
	rep(i,0,n) {
		short u=root; char ch=getchar(); while (isspace(ch)) ch=getchar();
		while (!isspace(ch)) {
			u=append(u,ch-'A'); ch=getchar();
		}
		t[u].s |= (1<<i);
	}
	build(); ALL = (1<<n) - 1; solve();
	return 0;
}