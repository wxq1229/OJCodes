#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fore(i,x) for(int i=head[x],v=e[i].to;i;i=e[i].nxt,v=e[i].to)
const int N=1e6+10;
int n;
struct edge
{
	int to,nxt;
}e[N<<1];
int head[N],cnt=0;
inline void ade(int x,int y)
{e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
inline void addedge(int x,int y)
{ade(x,y),ade(y,x);}
ll f[N],dep[N];
int siz[N];
void dfs(int x,int prev,int deep)
{
	dep[x]=deep,siz[x]=1;
	fore(i,x) if(v!=prev)
		dfs(v,x,deep+1),siz[x]+=siz[v];
}
void getans(int x,int prev)
{
	fore(i,x) if(v!=prev)
	{
		f[v]=f[x]+n-2ll*siz[v];
		getans(v,x);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y;i<n;i++)
		scanf("%d%d",&x,&y),addedge(x,y);
	dfs(1,0,0); 
	for(int i=1;i<=n;i++) f[1]+=dep[i];
	getans(1,0);
	ll mx=0; int ans=0;
	for(int i=1;i<=n;i++)
		if(f[i]>mx) mx=f[i],ans=i;
	printf("%d\n",ans);
	return 0;
}