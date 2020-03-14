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

const int N=1e6+10;
namespace Pool {
    int buf[N*23],*p=buf;
    inline int* New(int len) {int *ret=p; p+=len; return ret;}
}
using Pool::New;

int n,fa[N],dep[N],mdep[N],son[N];
VI e[N];

void dfs(int u,int f,int deep) {
    dep[u]=mdep[u]=deep;
    fa[u]=f;
    for (auto v:e[u]) if (v!=f) {
        dfs(v,u,deep+1);
        if (mdep[v]>mdep[u])
            mdep[u]=mdep[v],son[u]=v;
    }
}

int *f[N],ans[N];

void dp(int u) {
    if (son[u]) {
        int v=son[u];
        f[v]=f[u]+1,dp(v);
        ans[u]=ans[v]+1;
    }
    f[u][0]=1;
    if (f[u][0]>=f[u][ans[u]]) ans[u]=0;
    int mx=f[u][ans[u]];
    for (auto v:e[u]) if (v!=fa[u]&&v!=son[u]) {
        f[v]=New(mdep[v]-dep[v]+1);
        dp(v);
        for (int i=1;i<=mdep[v]-dep[v]+1;i++) {
            f[u][i]+=f[v][i-1];
            if (f[u][i]>mx||(f[u][i]==mx&&i<ans[u])) ans[u]=i,mx=f[u][i];
        }
    }
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d",&n);
    rep(i,0,n-1) {
        int u,v; scanf("%d%d",&u,&v);
        e[u].pb(v),e[v].pb(u);
    }
    dfs(1,0,1);
    f[1]=New(mdep[1]-dep[1]+1);
    dp(1);
    rep(i,1,n+1) printf("%d\n",ans[i]);
    return 0;
}