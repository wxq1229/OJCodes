#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;++i)
#define per(i,a,n) for (int i=n-1;i>=a;--i)
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

const int N=1e5+10;
const db INF=1e18,eps=1e-5;
int n,L,U;
vector<pair<int,db>> e[N];

namespace SegmentTree {
	struct node {
		int l,r; db add,mx;
	}t[N<<2];

	inline void pushup(int x) {t[x].mx=max(t[x<<1].mx,t[x<<1|1].mx);}
	inline void pushdown(int x) {
		if (t[x].add==0) return;
		int lc=x<<1,rc=x<<1|1; db add=t[x].add;
		t[lc].add+=add,t[rc].add+=add;
		t[lc].mx+=add,t[rc].mx+=add;
		t[x].add=0;
	}

	void build(int x,int l,int r) {
		t[x].add=0,t[x].l=l,t[x].r=r,t[x].mx=-INF;
		if (l==r) return; int mid=(l+r)>>1; 
		build(x<<1,l,mid),build(x<<1|1,mid+1,r);
		pushup(x);
	}

	void mdf(int x,int p,db v) {
		int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
		if (l==r) {t[x].mx=max(t[x].mx,v);return;}
		pushdown(x);
		if (p<=mid) mdf(x<<1,p,v); else mdf(x<<1|1,p,v);
		pushup(x);
	}

	db qry(int x,int ql,int qr) {
		if (ql>qr||ql<0||qr<0) return -INF;
		int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
		if (ql<=l&&r<=qr) return t[x].mx;
		pushdown(x); db ans=-INF;
		if (ql<=mid) ans=max(ans,qry(x<<1,ql,qr));
		if (mid<qr) ans=max(ans,qry(x<<1|1,ql,qr));
		return ans;
	}

	void upd(int x,int ql,int qr,db v) {
		int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
		if (ql<=l&&r<=qr) {t[x].mx+=v,t[x].add+=v;return;}
		pushdown(x);
		if (ql<=mid) upd(x<<1,ql,qr,v);
		if (mid<qr) upd(x<<1|1,ql,qr,v);
		pushup(x);
	}
}
using SegmentTree::mdf;
using SegmentTree::qry;
using SegmentTree::build;
using SegmentTree::upd;

int mdep[N],len[N],dep[N],son[N],fa[N],dfn[N],tim;

void dfs1(int u,int f) {
	fa[u]=f,dep[u]=mdep[u]=dep[f]+1;
	for (auto ei:e[u]) {
		int v=ei.fi; if (v==f) continue;
		dfs1(v,u);
		if (mdep[v]>mdep[u]) 
			son[u]=v,mdep[u]=mdep[v];
	}
	len[u]=mdep[u]-dep[u]+1;
}
void dfs2(int u) {
	dfn[u]=++tim; if (!son[u]) return;
	dfs2(son[u]);
	for (auto ei:e[u]) if (ei.fi!=fa[u]&&ei.fi!=son[u])
		dfs2(ei.fi);
}

db mxlen;
void dp(int u) {
	if (son[u]) dp(son[u]);
	db ws=0;
	for (auto ei:e[u]) if (ei.fi==son[u]) {ws=ei.se;break;}
	upd(1,dfn[u]+1,dfn[u]+len[u]-1,ws),mdf(1,dfn[u],0);
	for (auto ei:e[u]) {
		int v=ei.fi; db w=ei.se;
		if (v==son[u]||v==fa[u]) continue;
		dp(v);
		rep(i,0,len[v]) {
			int l=L-i-1,r=min(U-i-1,len[u]-1);
			db tmp=qry(1,dfn[v]+i,dfn[v]+i);
			mxlen=max(mxlen,w+tmp+qry(1,dfn[u]+l,dfn[u]+r));
		}
		rep(i,0,len[v]) mdf(1,dfn[u]+i+1,w+qry(1,dfn[v]+i,dfn[v]+i));
	}
	int l=L,r=min(len[u]-1,U);
	mxlen=max(mxlen,qry(1,dfn[u]+l,dfn[u]+r));
}

bool check(db avg) {
	mxlen=-INF;
	rep(i,1,n+1) for (auto &ei:e[i]) ei.se-=avg;
	build(1,1,n),dp(1);
	rep(i,1,n+1) for (auto &ei:e[i]) ei.se+=avg;
	return mxlen>=0;
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&L,&U);
	rep(i,0,n-1) {
		int u,v; db w;
		scanf("%d%d%lf",&u,&v,&w);
		e[u].pb(mp(v,w));
		e[v].pb(mp(u,w));
	}
	dfs1(1,0),dfs2(1);
	db l=0,r=1e6;
	while (l+eps<r) {
		db mid=(l+r)/2.0;
		if (check(mid)) l=mid; else r=mid;
	}
	printf("%.3f\n",l);
	return 0;
}