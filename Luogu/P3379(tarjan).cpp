#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
const int MAXN=5e5+10;
struct edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
int vis[MAXN],fa[MAXN];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
vector<pair<int,int> > q[MAXN];
int ans[MAXN];
void tarjan(int x){
	vis[x]=1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v]) continue;
		tarjan(v);
		fa[v]=x;
	}
	for (int i=0;i<q[x].size();i++){
		int y=q[x][i].se;
		if (vis[y]!=2) continue;
		int lca=find(y);
		ans[q[x][i].fi]=lca;
	}
	vis[x]=2;
}
int main(){
	int n,m,r;scanf("%d%d%d",&n,&m,&r);
	for (int i=1;i<=n;i++)fa[i]=i;
	for (int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	for (int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		q[x].pb(mp(i,y));
		q[y].pb(mp(i,x));
	}
	tarjan(r);
	for (int i=1;i<=m;i++)
		printf("%d\n",ans[i]);
	return 0;
}
