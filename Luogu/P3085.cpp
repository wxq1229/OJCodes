#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=4e5+10;
int n;
#define fore(i,x) for(int i=fst[x],v=to[i],c=col[i];i;i=nxt[i],v=to[i],c=col[i])
int fst[N],to[N<<1],nxt[N<<1],col[N<<1],es=0;
inline void ade(int x,int y,int w)
{to[++es]=y,col[es]=w,nxt[es]=fst[x],fst[x]=es;}
inline void addedge(int x,int y,int w)
{
	w=w==1?1:-1;
	ade(x,y,w),ade(y,x,w);
}
int siz[N],vis[N],mx[N],rt,all;
void getrt(int x,int prev)
{
	siz[x]=1,mx[x]=0;
	fore(i,x) if(v!=prev&&!vis[v])
	{
		getrt(v,x),siz[x]+=siz[v];
		mx[x]=max(mx[x],siz[v]);
	}
	mx[x]=max(mx[x],all-siz[x]);
	if(mx[x]<mx[rt]) rt=x;
}
int d[N],fa[N];
void dfs(int x,int prev,int w)
{
	d[x]=w,fa[x]=prev;
	fore(i,x) if(!vis[v]&&v!=prev) dfs(v,x,w+c);
}
int tmp[N<<1],cnt[2][N<<1];
void upd(int x,int k1=1)
{
	if(tmp[n+d[x]]) cnt[1][n+d[x]]+=k1;
	else cnt[0][n+d[x]]+=k1;
	tmp[n+d[x]]++;
	fore(i,x) if(!vis[v]&&v!=fa[x]) upd(v,k1);
	tmp[n+d[x]]--;
}
ll ans=0;
ll calc(int x)
{
	ans+=cnt[1][n-d[x]]+cnt[0][n-d[x]]*(tmp[n+d[x]]!=0);
	if(d[x]==0) ans+=tmp[n]>1;
	tmp[n+d[x]]++;
	fore(i,x) if(!vis[v]&&v!=fa[x]) calc(v);
	tmp[n+d[x]]--;
}
void dfz(int x)
{
	vis[x]=1,dfs(x,0,0);
	tmp[n]=1;
	fore(i,x) if(!vis[v]) calc(v),upd(v);
	fore(i,x) if(!vis[v]) upd(v,-1);
	tmp[n]=0;
	fore(i,x) if(!vis[v])
	{
		all=siz[v],mx[rt=0]=all;
		getrt(v,x),dfz(rt);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y,w;i<=n-1;i++)
		scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	mx[0]=n,all=siz[rt=0]=n;
	getrt(1,0),dfz(rt);
	printf("%lld\n",ans);
	return 0;
}