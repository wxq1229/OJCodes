#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <queue>
using namespace std;
#define fore(i,x) for(int i=head[x],v=e[i].to,w=e[i].w;i;i=e[i].nxt,v=e[i].to,w=e[i].w)
const int N=3e5+10;
struct edge
{
	int to,nxt,w;
}e[N<<1];
int head[N],cnt;
inline void ade(int x,int y,int w)
{e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
inline void addedge(int x,int y,int w)
{ade(x,y,w),ade(y,x,w);}
int n,sum[N],f[N],deg[N];
void dfs(int x,int prev)
{
	fore(i,x) if(v!=prev)
	{
		dfs(v,x);
		if(deg[v]==1) sum[x]+=w;
		else sum[x]+=min(sum[v],w);
	}
}
void getans(int x,int prev)
{
	fore(i,x) if(v!=prev)
	{
		if(deg[x]==1) f[v]=sum[v]+w;
		else f[v]=sum[v]+min(f[x]-min(sum[v],w),w);
		getans(v,x);
	}
}
void sol()
{
	memset(deg,0,sizeof(deg));
	memset(sum,0,sizeof(sum));
	memset(f,0,sizeof(f));
	memset(head,0,sizeof(head));
	memset(e,0,sizeof(e));
	cnt=0;
	scanf("%d",&n);
	for(int x,y,w,i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&w);
		addedge(x,y,w);
		++deg[x],++deg[y];
	}
	dfs(1,0);
	f[1]=sum[1],getans(1,0);
	int ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,f[i]);
	printf("%d\n",ans);
}
int main()
{
	int T; scanf("%d",&T); while(T--)sol();
	return 0;
}