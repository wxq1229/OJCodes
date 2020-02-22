#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<(b);++i)
#define per(i,a,b) for (int i=(a)-1;i>=(b);--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=1e6+10;
int n,m,rt;
ll val[N];
VI g[N];
int dfn[N],dep[N],siz[N],tim;
int top[N],fa[N],son[N];

void dfs1(int x,int ff,int deep) {
	dfn[x]=++tim,siz[x]=1;
	dep[x]=deep,fa[x]=ff;
	rep(i,0,SZ(g[x])) {
		int v=g[x][i]; if(v==ff) continue;
		dfs1(v,x,deep+1),siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int topf) {
	top[x]=topf; if(!son[x]) return;
	dfs2(son[x],topf);
	rep(i,0,SZ(g[x])) {
		int v=g[x][i]; if(v==fa[x]||v==son[x]) continue;
		dfs2(v,v);
	}
}
inline int getlca(int x,int y) {
	while(top[x]!=top[y]) dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}

inline int lowbit(int x) {return x&(-x);}
struct BIT {
	ll bt[N];
	void add(int x,ll v) {for(;x<=n;x+=lowbit(x))bt[x]+=v;}
	ll qwq(int x) {
		ll ret=0;
		for(;x;x-=lowbit(x)) ret+=bt[x];
		return ret;
	}
}b[3];

void upd(int x,ll v) {
	b[0].add(dfn[x],v);
	b[0].add(dfn[x]+siz[x],-v);
}
void upds(int x,ll v) {
	b[1].add(dfn[x],-v*(dep[x]-1));
	b[1].add(dfn[x]+siz[x],v*(dep[x]-1));
	b[2].add(dfn[x],v);
	b[2].add(dfn[x]+siz[x],-v);
}

ll qwq(int x) {return b[0].qwq(dfn[x])+b[1].qwq(dfn[x])+b[2].qwq(dfn[x])*dep[x];}
ll qry(int x,int y) {
	int lca=getlca(x,y);
	return qwq(x)+qwq(y)-qwq(lca)-qwq(fa[lca]);
}


void init(int rt) {
	dfs1(rt,0,1),dfs2(rt,rt);
	rep(i,1,n+1) upd(i,val[i]);
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&rt);
	rep(i,1,n+1) scanf("%lld",&val[i]);
	rep(i,0,n-1) {
		int x,y; scanf("%d%d",&x,&y);
		g[x].pb(y),g[y].pb(x);
	}
	init(rt);
	while(m--) {
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) upd(x,y);
		else if(opt==2) upds(x,y);
		else if(opt==3) printf("%lld\n",qry(x,y));
	}
	return 0;
}