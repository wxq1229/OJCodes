#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
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
typedef unsigned int ui;

const int N=5e5+10;
#define LOGN 20
VI up[N],dn[N],e[N];
int lg[N],p[N][23],top[N],mdep[N],dep[N],son[N];

void dfs1(int u,int f,int deep) {
    dep[u]=deep,mdep[u]=dep[u];
    p[u][0]=f; 
    rep(i,1,LOGN) p[u][i]=p[p[u][i-1]][i-1];
    for (auto v:e[u]) if (v!=f) {
        dfs1(v,u,deep+1);
        if (mdep[v]>mdep[u]) 
            mdep[u]=mdep[v],son[u]=v;
    }
}

void dfs2(int u,int topf) {
    top[u]=topf;
    if (u==top[u]) {
        for (int x=u,i=0;i<=mdep[u]-dep[u];i++,x=son[x]) dn[u].pb(x);
        for (int x=u,i=0;i<=mdep[u]-dep[u];i++,x=p[x][0]) up[u].pb(x);
    }
    if (!son[u]) return;
    dfs2(son[u],topf);
    for (auto v:e[u]) if (v!=p[u][0]&&v!=son[u]) dfs2(v,v);
}

int query(int u,int k) {
    if (k==0) return u;
    u=p[u][lg[k]],k-=(1<<lg[k])+dep[u]-dep[top[u]],u=top[u];
    return k>=0?up[u][k]:dn[u][-k];
}

int rt,n,Q;

ui s;
inline ui get(ui x) {
    x^=x<<13,x^=x>>17,x^=x<<5;
    return s=x;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d%u",&n,&Q,&s);
    lg[0]=-1; rep(i,1,n+1) lg[i]=lg[i>>1]+1;
    rep(i,1,n+1) {
        int fi; scanf("%d",&fi);
        if (!fi) rt=i;
        else e[i].pb(fi),e[fi].pb(i);
    }
    dfs1(rt,0,1),dfs2(rt,rt);
    int lstans=0;
    ll ans=0;
    rep(i,1,Q+1) {
        int u=(get(s)^lstans)%n+1;
        int k=(get(s)^lstans)%dep[u];
        ans^=1ll*i*(lstans=query(u,k));
    }
    printf("%lld\n",ans);
    return 0;
}