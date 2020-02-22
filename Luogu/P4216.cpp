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

const int N=2e5+10;
int n,m;
VI g[N];
int dfn[N],id[N],top[N],fa[N],siz[N],son[N],dep[N],tim;

void dfs1(int x,int ff,int deep) {
	dep[x]=deep,fa[x]=ff;
	siz[x]=1,siz[son[x]=0]=0;
	rep(i,0,SZ(g[x])) {
		int v=g[x][i]; if(v==ff)continue;
		dfs1(v,x,deep+1),siz[x]+=siz[v];
		if(siz[v]>siz[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int topf) {
	top[x]=topf,dfn[x]=++tim;
	if(!son[x]) return;
	dfs2(son[x],topf);
	rep(i,0,SZ(g[x])) {
		int v=g[x][i]; if(v==fa[x]||v==son[x]) continue;
		dfs2(v,v);
	}
}
void init(int r) {dfs1(r,0,1),dfs2(r,r);}
int getlca(int x,int y) {
	for(;top[x]!=top[y];dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
	return dep[x]<dep[y]?x:y;
}

namespace BIT {
	int bt[N];
	inline int lowbit(int x) {return x&(-x);}
	void add(int x,int v=1) {for(;x<=n;x+=lowbit(x)) bt[x]+=v;}
	int qwq(int x) {
		int ret=0;
		for(;x;x-=lowbit(x)) ret+=bt[x];
		return ret;
	}
	int qry(int l,int r) {return qwq(r)-qwq(l-1);}
}

void upd(int x) {BIT::add(dfn[x]);}
int qry(int x,int y) {
	int ret=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ret+=BIT::qry(dfn[top[x]],dfn[x]);
		x=fa[top[x]];
	}
	if(dfn[x]>dfn[y]) swap(x,y);
	ret+=BIT::qry(dfn[x],dfn[y]);
	return ret;
}

struct Query {
	int ty,x,y,k,id;
	inline void debug() {cout<<ty<<" "<<x<<" "<<y<<" "<<k<<" "<<id<<endl;}
	bool operator<(Query q)const {return k<q.k||(k==q.k&&ty<q.ty);}
}q[N];
int ans[2][N];

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n); int rt=0;
	rep(i,1,n+1) {
		int ff; scanf("%d",&ff);
		if(!ff) rt=i;
		else g[ff].pb(i),g[i].pb(ff);
	}
	init(rt);
	scanf("%d",&m);
	int qs=0;
	rep(i,1,m+1) {
		int opt,x,y,k;
		scanf("%d%d",&opt,&x);
		if(opt==2) {q[i].ty=1;q[i].x=x;q[i].k=i;q[i].id=0;}
		else {
			scanf("%d%d",&y,&k);
			q[i].ty=2; q[i].x=x,q[i].y=y;
			q[i].k=i-k-1,q[i].id=++qs;
			ans[0][qs]=dep[x]+dep[y]-2*dep[getlca(x,y)]+1;
		}
	}
	sort(q+1,q+m+1);
	rep(i,1,m+1) {
		// q[i].debug(); 
		if(q[i].ty==1) upd(q[i].x);
		else ans[1][q[i].id]=qry(q[i].x,q[i].y);
	}
	rep(i,1,qs+1) printf("%d %d\n",ans[0][i],ans[1][i]);
	return 0;
}