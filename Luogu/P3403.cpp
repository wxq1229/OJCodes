#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
const ll INF=1e18;
int n;
struct edge{int v,w;edge*nxt;}pool[N<<1];
edge *fst[N],*cur=pool;
void ade(int u,int v,int w){
    cur->nxt=fst[u],fst[u]=cur;
    cur->v=v,cur->w=w; ++cur;
}
ll dis[N]; bool vis[N];
void spfa(){
    for(int i=0;i<n;i++)dis[i]=INF;
    queue<int>q;
    q.push(1);
    dis[1]=1,vis[1]=1;
    while(q.size()){
        int u=q.front();q.pop();
        vis[u]=0;
        for(edge*p=fst[u];p;p=p->nxt) {
            int v=p->v,w=p->w;
            if(dis[v]>dis[u]+w){
                dis[v]=dis[u]+w;
                if(!vis[v]) vis[v]=1,q.push(v);
            }
        }
    }
}
ll h; int x,y,z;
int main(){
    scanf("%lld%d%d%d",&h,&x,&y,&z);
    if(x==1||y==1||z==1) {printf("%lld\n",h);return 0;}
    n=x;
    for(int i=0;i<n;i++) ade(i,(i+y)%n,y),ade(i,(i+z)%n,z);
    spfa();
    ll ans=0;
    for(int i=0;i<n;i++) if(dis[i]!=INF&&h>=dis[i]) ans+=(h-dis[i])/x+1;
    printf("%lld\n",ans);
    return 0;
}