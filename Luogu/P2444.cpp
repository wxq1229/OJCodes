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

const int N = 1e5 + 10, SIGMA = 2;

struct node {
	int go[SIGMA], fail;
	int fg;
	void clear() {
		memset(go,0,sizeof(go));
		fail = fg = 0;
	}
} t[N];
int root, cnt;

int newnode() { int u=++cnt; t[u].clear(); return u; }
int append(int u,int c) {
	if (!t[u].go[c]) t[u].go[c] = newnode();
	return t[u].go[c];
}

void build() {
	queue<int> q; int u = root;
	rep(i,0,SIGMA) if (t[u].go[i]) {
		t[t[u].go[i]].fail = u;
		q.push(t[u].go[i]);
	}
	while (q.size()) {
		u = q.front(); q.pop();
		t[u].fg |= t[t[u].fail].fg;
		rep(i,0,SIGMA) {
			int &v = t[u].go[i];
			if (!v) v = t[t[u].fail].go[i];
			else t[v].fail = t[t[u].fail].go[i], q.push(v);
		}
	}
}

bool vis[N], found  = 0, instack[N];

void dfs(int u) {
	instack[u] = 1; vis[u] = 1;
	rep(i,0,SIGMA) {
		int v = t[u].go[i];
		if (instack[v]) { found = 1; return; }
		else if (!vis[v] && !t[v].fg) dfs(v);
	}
	instack[u] = 0;
}

char s[N];

int main() {
	int n; scanf("%d", &n);
	rep(i,0,n) {
		scanf("%s", s);
		int len = strlen(s), u = root;
		rep(j,0,len) u = append(u,s[j]-'0');
		t[u].fg = 1;
	}
	build(), dfs(root);
//	rep(i,0,11) printf("%d ",t[i].fail);
	puts(found ? "TAK" : "NIE");
	return 0;
}