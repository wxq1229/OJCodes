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

const int N=2e5+10;

int n,m,qt,et;
struct BIT {
	int c[N],n;
	inline void init(int sz) {n=sz; rep(i,0,n+1) c[i]=0;}
	void upd(int x,int v=1) {for (;x<=n;x+=x&-x) c[x]+=v;}
	int qwq(int x) {
		int ret=0;
		for (;x;x-=x&-x) ret+=c[x];
		return ret;
	}
	int qry(int l,int r) {return qwq(r)-qwq(l-1);}
}bt;

int dep[N],fa[N],top[N],siz[N],son[N],dfn[N],tim;
VI e[N];

void dfs1(int u,int ff,int deep) {
	dep[u]=deep,fa[u]=ff;
	siz[u]=1;
	for (auto v:e[u]) if (v!=ff) {
		dfs1(v,u,deep+1);
		siz[u]+=siz[v];
		if (siz[v]>siz[son[u]]) son[u]=v;
	}
}
void dfs2(int u,int topf) {
	top[u]=topf;
	dfn[u]=++tim;
	if (son[u]) {
		dfs2(son[u],topf);
		for (auto v:e[u]) if (v!=fa[u]&&v!=son[u])
			dfs2(v,v);
	}
}

void upd(int u,int v=1) {bt.upd(dfn[u],v);}
int qry(int u,int v) {
	int ret=0;
	while (top[u]!=top[v]) {
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		ret+=bt.qry(dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if (dfn[u]>dfn[v]) swap(u,v);
	ret+=bt.qry(dfn[u],dfn[v]);
	return ret;
}

struct event {
	int op,u,v,k,id;
	inline void debug() {
		printf("%d %d %d %d %d\n",op,u,v,k,id);
	}
}evt[N],q1[N],q2[N];
int ans[N];
void solve(int l,int r,int ql,int qr) {
	if (ql>qr||l>r) return;
	// printf("%d %d:\n",l,r);
	// rep(i,ql,qr+1) evt[i].debug();
	if (l==r) {
		rep(i,ql,qr+1) if (evt[i].op==1) ans[evt[i].id]=l;
		return;
	}
	// puts("---------------------\n\n");
	int mid=(l+r)>>1,t1=0,t2=0;
	rep(i,ql,qr+1) {
		if (evt[i].op==0) {
			if (evt[i].v<=mid) q1[++t1]=evt[i];
			else q2[++t2]=evt[i],upd(evt[i].u,evt[i].k);
		} else {
			int tmp=qry(evt[i].u,evt[i].v);
			// cout<<tmp<<endl;
			if (tmp>=evt[i].k) q2[++t2]=evt[i];
			else evt[i].k-=tmp,q1[++t1]=evt[i];
		}
	}
	rep(i,1,t1+1) evt[ql+i-1]=q1[i];
	rep(i,1,t2+1) evt[ql+t1+i-1]=q2[i];
	rep(i,1,t2+1) if (q2[i].op==0) upd(q2[i].u,-q2[i].k);
	solve(l,mid,ql,ql+t1-1);
	solve(mid+1,r,ql+t1,qr);
}

int lst[N];
int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) {
		int v; scanf("%d",&v);
		evt[++et]=(event){0,i,lst[i]=v,1,0};
	}
	rep(i,1,n) {
		int u,v; scanf("%d%d",&u,&v);
		e[u].pb(v),e[v].pb(u);
	}
	bt.init(n);
	dfs1(1,0,1),dfs2(1,1);
	// rep(i,1,n+1) printf("%d ",dfn[i]); puts("");
	rep(i,1,m+1) {
		int ty,u,v;
		scanf("%d%d%d",&ty,&u,&v);
		if (ty==0) {
			evt[++et]=(event){0,u,lst[u],-1,0};
			evt[++et]=(event){0,u,lst[u]=v,1,0};
		}
		else evt[++et]=(event){1,u,v,ty,++qt};
	}
	solve(-1e8,1e8,1,et);
	rep(i,1,qt+1) 
		if (ans[i]!=-1e8) printf("%d\n",ans[i]);
		else puts("invalid request!");
	return 0;
}