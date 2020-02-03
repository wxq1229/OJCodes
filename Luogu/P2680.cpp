#include <bits/stdc++.h>
using namespace std;
const int MAXN=3e5+10;
int n,m;
struct edge{int to,w,nxt;}e[MAXN<<1];
int head[MAXN],cnt=0;
void adde(int x,int y,int w){e[++cnt]=(edge){y,w,head[x]},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
int dis[MAXN],lste[MAXN];
void dfs(int x,int prev,int d){
	dis[x]=d;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev) continue;
		lste[v]=i;
		dfs(v,x,d+e[i].w);
	}
}
struct event{
	int s,t,lca,w;
}evt[MAXN];
vector<pair<int,int> > q[MAXN];
int vis[MAXN],fa[MAXN];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
void tarjan(int x){
	vis[x]=1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v]) continue;
		tarjan(v);
		fa[v]=x;
	}
	for (int i=0;i<q[x].size();i++){
		int y=q[x][i].second,id=q[x][i].first;
		if (vis[y]!=2) continue;
		int lca=find(y);
		evt[id].lca=lca;
		evt[id].w=dis[x]+dis[y]-2*dis[lca];
	}
	vis[x]=2;
}
int d[MAXN];
void add(int id){
	int x=evt[id].s,y=evt[id].t;
	int lca=evt[id].lca;
	d[x]++,d[y]++,d[lca]-=2;
}
void getsum(int x,int prev){
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev) continue;
		getsum(v,x);
		d[x]+=d[v];
	}
}
int check(int lmt){
	memset(d,0,sizeof(d));
	vector<int> ids;
	for (int i=1;i<=m;i++){
		if (evt[i].w<=lmt) continue;
		ids.push_back(i);
	}
	int tot=ids.size(),maxt=0;
	if (tot==0)return 1;
	for (int i=0;i<tot;i++)
		maxt=max(maxt,evt[ids[i]].w),add(ids[i]);
	getsum(1,0);
	for (int i=1;i<=n;i++)
		if (d[i]==tot&&maxt-e[lste[i]].w<=lmt) return 1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++) fa[i]=i;
	for (int i=1;i<=n-1;i++){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		addedge(x,y,w);
	}
	dfs(1,0,0);
	for (int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		evt[i].s=x,evt[i].t=y;
		q[x].push_back(make_pair(i,y));
		q[y].push_back(make_pair(i,x));
	}
	tarjan(1);
	int l=0,r=1e9,ans=0;
	while (l<=r){
		int mid=(l+r)>>1;
		if (check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}










