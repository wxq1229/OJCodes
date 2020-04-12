#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int SIGMA=26,N=1e6+10;

struct node {
	int go[SIGMA],fail,id,fa;
	void clr() {
		memset(go,0,sizeof(go));
		fail=id=fa=0;
	}
}t[N],trie[N];
int pos[N],root,cnt,wcnt;

void init() { root=cnt=0; t[root].clr(); }
int newnode() { int u=++cnt; t[u].clr(); return u; }

int append(int u,int c) {
	if (!t[u].go[c]) t[u].go[c]=newnode(),t[t[u].go[c]].fa=u;
	return t[u].go[c];
}
void build() {
	queue<int> q; int u=root;
	rep(i,0,26) if (t[u].go[i]) t[t[u].go[i]].fail=u,q.push(t[u].go[i]);
	while (q.size()) {
		u=q.front(); q.pop();
		rep(i,0,26) {
			int &v=t[u].go[i];
			if (!v) v=t[t[u].fail].go[i];
			else t[v].fail=t[t[u].fail].go[i],q.push(v);
		}
	}
}

struct Query { int y,id; };
vector<Query> qs[N];
int ans[N];

struct BIT {
	int c[N]; int n;
	void init(int sz) { n=sz; rep(i,0,n+1) c[i]=0; }
	void upd(int x,int v=1) { for (;x<=n;x+=x&-x) c[x]+=v; }
	int qwq(int x) { int ret=0; for (;x;x-=x&-x) ret+=c[x]; return ret; }
	int qry(int l,int r) {return qwq(r)-qwq(l-1);}
}bt;

struct FailTree {
	VI e[N]; int tim,dfn[N],siz[N];
	void build() { rep(i,1,cnt+1) e[i].pb(t[i].fail),e[t[i].fail].pb(i); }
	void dfs(int u,int f) {
		dfn[u]=++tim,siz[u]=1;
		for (auto v:e[u]) if (v!=f) 
			dfs(v,u),siz[u]+=siz[v]; 
	}
	void init() { build(); tim=0; dfs(root,-1); }
}ft;

void getans(int u) {
	bt.upd(ft.dfn[u],1);
	if (t[u].id) {
		int x=t[u].id;
		for (auto q:qs[x]) {
			int v=pos[q.y];
			ans[q.id]=bt.qry(ft.dfn[v],ft.dfn[v]+ft.siz[v]-1);
		}
	}
	rep(i,0,26) if (trie[u].go[i]) getans(trie[u].go[i]);
	bt.upd(ft.dfn[u],-1);
}

char s[100010];

int main() {
	init();
	scanf("%s",s);
	int n=strlen(s),u=root;
	rep(i,0,n) {
		if ('a'<=s[i]&&s[i]<='z') u=append(u,s[i]-'a');
		else if (s[i]=='P') t[u].id=++wcnt,pos[wcnt]=u;
		else if (s[i]=='B') u=t[u].fa;
	}
	rep(i,0,cnt+1) trie[i]=t[i];
	build();
	bt.init(cnt+1),ft.init();
	int Q; scanf("%d",&Q);
	rep(i,1,Q+1) {
		int x,y; scanf("%d%d",&x,&y);
		qs[y].pb((Query){x,i});
	}
	getans(root);
	rep(i,1,Q+1) printf("%d\n",ans[i]);
	return 0;
}