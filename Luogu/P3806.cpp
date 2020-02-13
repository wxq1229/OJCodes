#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fore(i,x) for(int i=head[x],v=e[i].to,w=e[i].w;i;i=e[i].nxt,v=e[i].to,w=e[i].w)
const int N=1e5+10;
int n,m;
struct edge
{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt=0;
inline void ade(int x,int y,int w)
{e[++cnt]=(edge){y,head[x],w};head[x]=cnt;}
inline void addedge(int x,int y,int w){ade(x,y,w),ade(y,x,w);}
vector<int>qs;
int ans[1010];
int siz[N],vis[N],mx[N],rt,all;
void getrt(int x,int prev)
{
	siz[x]=1,mx[x]=0;
	fore(i,x) if(!vis[v]&&v!=prev)
	{
		getrt(v,x),siz[x]+=siz[v];
		mx[x]=max(mx[x],siz[v]);
	}
	mx[x]=max(mx[x],all-siz[x]);
	if(mx[x]<mx[rt]) rt=x;
}
int dis[N],tot=0;
inline void getd(int x,int prev,int d)
{
	dis[++tot]=d;
	fore(i,x) if(v!=prev&&!vis[v]) getd(v,x,d+w);
}
#define IT multiset<int>::iterator
multiset<int> s;
void dfz(int x)
{
	vis[x]=1;
	fore(ei,x) if(!vis[v])
	{
		tot=0,getd(v,x,w);
		for(int i=0;i<m;i++)
		{
			if(ans[i]) continue;
			for(int j=1;j<=tot;j++)
			{
				if(dis[j]==qs[i]){ans[i]=1;break;}
				IT it=s.lower_bound(qs[i]-dis[j]);
				if(it==s.end()) continue;
				if(dis[j]+(*it)==qs[i]){ans[i]=1;break;}
			}
		}
		for(int i=1;i<=tot;i++) s.insert(dis[i]);
	}
	s.clear();
	fore(i,x) if(!vis[v])
	{
		all=mx[rt=0]=siz[v];
		getrt(v,x),dfz(rt);
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y,w;i<n;i++)
		scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	for(int i=1,x;i<=m;i++) scanf("%d",&x),qs.pb(x);
	all=mx[rt=0]=n,getrt(1,0),dfz(rt);
	for(int i=0;i<m;i++) puts(ans[i]?"AYE":"NAY");
	return 0;
}