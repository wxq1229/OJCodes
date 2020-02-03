#include <bits/stdc++.h>
using namespace std;
struct dijkstra{
	int d[233333*4],vis[233333*4],head[233333*4],cnt=0;
	struct edge{int to,w,nxt;}e[2333333];
	void adde(int x,int y,int w){e[++cnt]=(edge){y,w,head[x]},head[x]=cnt;}
	void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
	struct node{
		int x,dis;
		bool operator < (const node &k1)const{return dis>k1.dis;}
	};
	priority_queue<node>q;
	void solve(int s=1){
		q.push((node){s,d[s]=0});
		while (q.size()){
			int x=q.top().x;q.pop();
			if (vis[x])continue;
			vis[x]=1;
			for (int i=head[x];i;i=e[i].nxt){
				int v=e[i].to;
				if (d[v]>d[x]+e[i].w)q.push((node){v,d[v]=d[x]+e[i].w});
			}
		}
	}
	void init(){
		while (q.size())q.pop();
		memset(vis,0,sizeof(vis)),memset(d,0x3f,sizeof(d));
		memset(head,0,sizeof(head)),memset(e,0,sizeof(e)),cnt=0;
	}
}dj;
int n,m,Q,K,S,val[233333*4],pa[233333*4];
int findpa(int x){return pa[x]==x?x:pa[x]=findpa(pa[x]);}
struct edge{int to,nxt;}e[2333333];
int head[233333*4],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
struct node{
	int x,y,w;
	bool operator < (const node &k1)const{return w>k1.w;}
}es[2333333];
int fa[233333*4][23],mn[233333*4];
void init(){memset(head,0,sizeof(head)),cnt=0,memset(e,0,sizeof(e)),memset(fa,0,sizeof(fa));}
void dfs(int x){
	mn[x]=dj.d[x];
	for (int i=1;i<=19;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int v,i=head[x];i;i=e[i].nxt)
		fa[v=e[i].to][0]=x,dfs(v),mn[x]=min(mn[x],mn[v]);
}
void kruskal(){
	for (int i=1;i<=n;i++)pa[i]=i;
	int size=n;sort(es+1,es+m+1);
	for (int tot=n,i=1;i<=m;i++){
		int x=findpa(es[i].x),y=findpa(es[i].y),w=es[i].w;
		if (x==y)continue;
		++size,pa[size]=pa[x]=pa[y]=size;
		adde(size,x),adde(size,y),val[size]=w;
		if (--tot==1)break;
	}
	dfs(size);
}
int query(int x,int p){
	for (int i=19;i>=0;i--) if (fa[x][i]&&val[fa[x][i]]>p)x=fa[x][i];
	return mn[x];
}
int main(){
	int T;scanf("%d",&T);while (T--){
		scanf("%d%d",&n,&m),dj.init(),init();
		for (int l,a,x,y,i=1;i<=m;i++){
			scanf("%d%d%d%d",&x,&y,&l,&a);
			dj.addedge(x,y,l),es[i]=(node){x,y,a};
		}
		dj.solve(),kruskal();
		scanf("%d%d%d",&Q,&K,&S);
		int lstans=0;while (Q--){
			int x,p;scanf("%d%d",&x,&p);
			x=(x+K*lstans-1)%n+1,p=(p+K*lstans)%(S+1);
			printf("%d\n",lstans=query(x,p));
		}
	}
	return 0;
}










