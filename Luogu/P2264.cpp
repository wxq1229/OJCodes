#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define fore(i,x) for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
#define N 111111
int n,col[N];
struct edge
{
    int to,nxt;
}e[N<<1];
int head[N],cnt=0;
inline void ade(int x,int y)
{e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
inline void addedge(int x,int y){ade(x,y),ade(y,x);}
int sz[N],vis[N],rt,mx[N],all;
void getrt(int x,int prev)
{
    sz[x]=1,mx[x]=0;
    fore(i,x) if(!vis[v]&&v!=prev)
    {
        getrt(v,x),sz[x]+=sz[v];
        mx[x]=max(mx[x],sz[v]);
    }
    mx[x]=max(mx[x],all-sz[x]);
    if(mx[x]<mx[rt]) rt=x;
}
int siz[N];
void dfs(int x,int prev)
{
    siz[x]=1; fore(i,x) if(!vis[v]&&v!=prev)
        dfs(v,x),siz[x]+=siz[v];
}
ll tot[N],sum; int tmp[N];
void upd(int x,int prev,int k1)
{
    int c=col[x]; 
    if(!tmp[c]) tot[c]+=siz[x]*k1,sum+=siz[x]*k1;
    tmp[c]++;
    fore(i,x) if(!vis[v]&&v!=prev)
        upd(v,x,k1);
    tmp[c]--;
}
void clear(int x,int prev)
{
    tot[col[x]]=0;
    fore(i,x) if(!vis[v]&&v!=prev) clear(v,x);
}
ll nw,osiz,ans[N];
void getans(int x,int prev)
{
    int c=col[x];
    if(!tmp[c]) nw++,sum-=tot[c];
    ans[x]+=nw*osiz+sum;
    tmp[c]++; fore(i,x) if(!vis[v]&&v!=prev)
        getans(v,x);
    tmp[c]--;
    if(!tmp[c]) nw--,sum+=tot[c];
}
void calc(int x)
{
    dfs(x,0),upd(x,0,1);
    ans[x]+=sum; int c=col[x];
    fore(i,x) if(!vis[v])
    {
        sum-=siz[v],tot[c]-=siz[v];
        tmp[c]++,upd(v,x,-1),tmp[c]--;
        tmp[c]++,osiz=siz[x]-siz[v],sum-=tot[c],nw=1;
        getans(v,x);
        tmp[c]--,nw=0,sum+=tot[c];
        sum+=siz[v],tot[c]+=siz[v];
        tmp[c]++,upd(v,x,1),tmp[c]--;
    }
    clear(x,0);
    sum=0,osiz=0,nw=0;
}
void dfz(int x)
{
    calc(x),vis[x]=1;
    fore(i,x) if(!vis[v])
    {
        mx[rt=0]=all=sz[v];
        getrt(v,x),dfz(rt);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&col[i]);
    for(int i=1,x,y;i<n;i++)
        scanf("%d%d",&x,&y),addedge(x,y);
    mx[rt=0]=all=n,getrt(1,0),dfz(rt);
    for(int i=1;i<=n;i++) printf("%lld\n",ans[i]);
    return 0;
}