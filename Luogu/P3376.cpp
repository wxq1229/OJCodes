#include <bits/stdc++.h>
using namespace std;
struct Dinic{
	struct edge{int to,nxt,cap,flow;}e[23333*23];
	int head[23333*23],cnt;
	void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w,0},head[x]=cnt;}
	void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,0);}
	int s,t;void init(int ss,int tt){cnt=1,s=ss,t=tt;}
	int d[23333*23];
	int bfs(){
		memset(d,0,sizeof(d)),d[s]=1;
		queue<int>q;q.push(s);
		while (q.size()){
			int x=q.front();q.pop();
			for (int v,i=head[x];i;i=e[i].nxt)
				if (e[i].cap>e[i].flow&&!d[v=e[i].to])q.push(v),d[v]=d[x]+1;
		}
		return d[t];
	}
	int cur[23333*23];
	int dfs(int x,int a){
		if (!a||x==t)return a;
		for (int &i=cur[x];i;i=e[i].nxt){
			int v=e[i].to,nxt;
			if (d[v]==d[x]+1&&e[i].cap>e[i].flow){
				if (nxt=dfs(v,min(e[i].cap-e[i].flow,a))) 
					return e[i].flow+=nxt,e[i^1].flow-=nxt,nxt;
				else d[v]=0;
			}
		}
		return 0;
	}
	int Maxflow(){
		int maxflow=0,flow;
		while (bfs()){
			memcpy(cur,head,sizeof(cur));
			while (flow=dfs(s,0x3f3f3f3f))maxflow+=flow;
		}
		return maxflow;
	}
}g;
int main(){
	int n,m,s,t;scanf("%d%d%d%d",&n,&m,&s,&t);
	g.init(s,t);for (int i=1;i<=m;i++){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		g.addedge(x,y,w);
	}
	printf("%d\n",g.Maxflow());
	return 0;
}
