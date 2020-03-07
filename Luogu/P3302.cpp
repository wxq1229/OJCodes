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

const int N=3e5+10;
namespace Desc {
    int val[N],tot;
    inline void init(int *a,int n) {
        rep(i,1,n+1) val[i]=a[i];
        sort(val+1,val+n+1);
        tot=unique(val+1,val+n+1)-val-1;
    }
    inline int getid(int x) {return lower_bound(val+1,val+tot+1,x)-val;}
    inline int getval(int i) {return val[i];}
}
using Desc::getid;
using Desc::getval;

int lc[N*40],rc[N*40],sum[N*40],oc=0,rt[N];
inline void clr(int &x) {lc[x]=rc[x]=sum[x]=0;}
inline int newnode() {int x=++oc;clr(x);return x;}

void build(int &x,int l,int r) {
    x=newnode(); if(l==r) return; int mid=(l+r)>>1;
    build(lc[x],l,mid),build(rc[x],mid+1,r);
}

void ins(int pre,int &x,int l,int r,int p,int v=1) {
    x=newnode(); lc[x]=lc[pre],rc[x]=rc[pre],sum[x]=sum[pre]+v;
    if(l==r) return; int mid=(l+r)>>1;
    if(p<=mid) ins(lc[pre],lc[x],l,mid,p,v);
    else ins(rc[pre],rc[x],mid+1,r,p,v);
}

int qry(int x,int y,int lca,int flca,int l,int r,int k) {
    if(l==r) return l; 
    int mid=(l+r)>>1,sz=sum[lc[x]]+sum[lc[y]]-sum[lc[lca]]-sum[lc[flca]];
    if(k<=sz) return qry(lc[x],lc[y],lc[lca],lc[flca],l,mid,k);
    else return qry(rc[x],rc[y],rc[lca],rc[flca],mid+1,r,k-sz);
}

int n,m,a[N],Q,p[N][30],dep[N];
VI g[N];
#define LOGN 21

inline int getlca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    per(i,0,LOGN) if(dep[p[x][i]]>=dep[y]) x=p[x][i];
    if(x==y) return x;
    per(i,0,LOGN) if(p[x][i]!=p[y][i]) x=p[x][i],y=p[y][i];
    return p[x][0];
}

int F[N],siz[N],vis[N];
inline int find(int x) {return F[x]==x?F[x]:F[x]=find(F[x]);}

void dfs(int u,int ff,int deep,int pp) {
    siz[pp]++,vis[u]=1,F[u]=pp;
    int pos=getid(a[u]); ins(rt[ff],rt[u],1,Desc::tot,pos);
    p[u][0]=ff; rep(i,1,LOGN) p[u][i]=p[p[u][i-1]][i-1];
    dep[u]=deep;
    for (auto v:g[u]) if(v!=ff) dfs(v,u,deep+1,pp);
}

inline void merge(int u,int v) {
    int pu=find(u),pv=find(v);
    if(pu==pv) return;
    if(siz[pu]<siz[pv]) swap(u,v),swap(pu,pv);
    g[u].pb(v),g[v].pb(u);
    dfs(v,u,dep[u]+1,pu);
}

inline int query(int u,int v,int k) {
    int lca=getlca(u,v),flca=p[lca][0];
    return getval(qry(rt[u],rt[v],rt[lca],rt[flca],1,Desc::tot,k));
}

inline int nc() {char ch;while(isspace(ch=getchar()));return ch;}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%*d%d%d%d",&n,&m,&Q);
    rep(i,1,n+1) scanf("%d",a+i);
    Desc::init(a,n);
    build(rt[0],1,Desc::tot);
    rep(i,1,m+1) {
        int u,v; scanf("%d%d",&u,&v);
        g[u].pb(v),g[v].pb(u);
    }
    rep(i,1,n+1) F[i]=i;
    rep(i,1,n+1) if(!vis[i]) dfs(i,0,1,i);
    int lstans=0; while(Q--) {
        char opt=nc();
        int u,v,k;scanf("%d%d",&u,&v);
        if(opt=='Q') {
            scanf("%d",&k);
            u^=lstans,v^=lstans,k^=lstans;
            printf("%d\n",lstans=query(u,v,k));
        } else {
            u^=lstans,v^=lstans;
            merge(u,v);
        }
    }
    return 0;
}