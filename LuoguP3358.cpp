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

const int N=1e5+10,INF=0x3f3f3f3f;

struct MCMF {
    int n,S,T,maxflow,mincost;
    int to[N<<1],cap[N<<1],cost[N<<1],fst[N],nxt[N<<1],flow[N<<1],cnt;
    inline void init(int tn,int s,int t) {
        n=tn,S=s,T=t,cnt=1;
        rep(i,0,n+1) fst[i]=0;
    }

    void ade(int u,int v,int w,int c) {
        to[++cnt]=v,nxt[cnt]=fst[u],fst[u]=cnt;
        cap[cnt]=w,flow[cnt]=0,cost[cnt]=c;
    }
    void addedge(int u,int v,int w,int c) {ade(u,v,w,c),ade(v,u,0,-c);}

    int q[N],vis[N],pre[N],incf[N],d[N],t;
    bool spfa() {
        rep(i,0,n+1) vis[i]=0,d[i]=INF,pre[i]=0,incf[i]=INF;
        pre[S]=0,d[S]=0,vis[S]=1;
        t=1,q[0]=S;
        rep(i,0,t) {
            int u=q[i]; vis[u]=0;
            for (int j=fst[u];j;j=nxt[j]) {
                int v=to[j],w=cost[j];
                if(d[v]>d[u]+w&&cap[j]>flow[j]) {
                    d[v]=d[u]+w;
                    incf[v]=min(incf[u],cap[j]-flow[j]);
                    pre[v]=j;
                    if (!vis[v]) vis[v]=1,q[t++]=v;
                }
            }
        }
        return d[T]!=INF;
    }

    void augment() {
        maxflow+=incf[T];
        mincost+=d[T]*incf[T];
        for (int u=T;u!=S;u=to[pre[u]^1])
            flow[pre[u]]+=incf[T],flow[pre[u]^1]-=incf[T];
    }

    void mcmf() {
        mincost=maxflow=0;
        while (spfa()) augment();
    }
}g;

namespace Disc {
    int val[N],tot;

    void init(int *a,int n) {
        tot=n; rep(i,1,n+1) val[i]=a[i];
        sort(val+1,val+tot+1);
        tot=unique(val+1,val+tot+1)-val-1;
    }

    inline int getid(int v) {return lower_bound(val+1,val+tot+1,v)-val;}
    inline int getval(int i) {return val[i];}
}
using Disc::getid;
using Disc::getval;

int l[N],r[N],a[N];

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    int tt=0,n,k; scanf("%d%d",&n,&k);
    rep(i,1,n+1) scanf("%d%d",l+i,r+i),a[++tt]=l[i],a[++tt]=r[i];
    Disc::init(a,tt);
    tt=Disc::tot;
    int s=0,t=tt+1;
    g.init(tt+5,s,t);
    rep(i,1,tt+1) g.addedge(i,i+1,INF,0);
    g.addedge(s,1,k,0);
    rep(i,1,n+1) g.addedge(getid(l[i]),getid(r[i]),1,l[i]-r[i]);
    g.mcmf();
    printf("%d\n",-g.mincost);
    return 0;
}