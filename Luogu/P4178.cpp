#include <bits/stdc++.h>
using namespace std;
#define fore(i,x) for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
const int N=1e5+10;
int n,K;
struct edge
{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt=0;
inline void ade(int x,int y,int w)
{e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
inline void addedge(int x,int y,int w){ade(x,y,w),ade(y,x,w);}
int siz[N],mx[N],rt,all,vis[N];
void getrt(int x,int prev)
{
	siz[x]=1,mx[x]=0;
	fore(i,x)if(!vis[v]&&v!=prev)
	{
		getrt(v,x),siz[x]+=siz[v];
		mx[x]=max(mx[x],siz[v]);
	}
	mx[x]=max(mx[x],all-siz[x]);
	if(mx[x]<mx[rt]) rt=x;
}
int dis[N],tot;
void getd(int x,int prev,int d)
{
	dis[++tot]=d;
	fore(i,x) if(v!=prev&&!vis[v]) getd(v,x,d+e[i].w);
}
int calc(int x,int w)
{
	tot=0,getd(x,0,w);
	sort(dis+1,dis+tot+1);
	int nw=tot,ans=0; for(int i=1;i<=tot;i++)
	{
		while(dis[nw]+dis[i]>K) nw--;
		if(nw<=i) break; ans+=nw-i;
	}
	return ans;
}
int ans;
void dfz(int x)
{
	vis[x]=1,ans+=calc(x,0);
	fore(i,x) if(!vis[v]) ans-=calc(v,e[i].w);
	fore(i,x) if(!vis[v])
	{
		rt=0,all=mx[rt]=siz[v];
		getrt(v,x),dfz(rt);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y,w;i<=n-1;i++)
		scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	scanf("%d",&K);
	rt=0,all=mx[rt]=n;
	getrt(1,0),dfz(rt);
	printf("%d\n",ans);
	return 0;
}