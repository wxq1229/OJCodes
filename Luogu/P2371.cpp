#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=1e18;
const int N=5e5*12+10;
struct SPFA{
    int n;
    struct edge{int v,w;edge*nxt;}pool[N],*cur,*fst[N];
    void init() {for(int i=0;i<n;i++) fst[i]=nullptr;cur=pool;}
    void ade(int u,int v,int w){cur->v=v,cur->w=w,cur->nxt=fst[u],fst[u]=cur;++cur;}
    ll dis[N]; bool vis[N];
    void spfa(int s) {
        for(int i=0;i<n;i++) vis[i]=0,dis[i]=INF;
        dis[s]=s;vis[s]=1;
        queue<int>q; q.push(s);
        while (q.size()){
            int u=q.front();q.pop();
            vis[u]=0;
            for(edge*p=fst[u];p;p=p->nxt){
                int v=p->v,w=p->w;
                if(dis[v]>dis[u]+w){
                    dis[v]=dis[u]+w;
                    if(!vis[v]) vis[v]=1,q.push(v);
                }
            }
        }
    }
}g;
int a[N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n,mod=(int)1e9; ll l,r;
    cin>>n>>l>>r;
    for(int i=0;i<n;i++) cin>>a[i],mod=min(mod,a[i]?a[i]:(int)1e9);
    g.n=mod;g.init();
    for(int i=0;i<mod;i++)
        for(int j=0;j<n;j++) g.ade(i,(i+a[j])%mod,a[j]);
    g.spfa(0);
    // for(int i=0;i<mod;i++) cerr<<g.dis[i]<<" ";cerr<<endl;
    ll ans=0;
    for(int i=0;i<mod;i++) if(g.dis[i]<=r) ans+=(r-g.dis[i])/mod+1;
    for(int i=0;i<mod;i++) if(g.dis[i]<=l-1) ans-=(l-1-g.dis[i])/mod+1;
    cout<<ans<<'\n';
    return 0;
}