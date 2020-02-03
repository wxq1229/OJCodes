#include <bits/stdc++.h>
using namespace std;
struct MCMF{
	struct edge{
		int from,to,cap,cost,flow,nxt;
	}e[233333*23];
	int head[233333*23],cnt;
	void adde(int x,int y,int w,int c){e[++cnt]=(edge){x,y,w,c,0,head[x]},head[x]=cnt;}
	void addedge(int x,int y,int w,int c){adde(x,y,w,c),adde(y,x,0,-c);}
	int s,t,maxflow,mincost;
	void init(int ss,int tt){cnt=1,s=ss,t=tt;}
	int d[23333*23],incf[23333*23],pre[23333*23],vis[23333*23];
	queue<int>q;
	int spfa(){
		while (q.size())q.pop();
		memset(d,0x3f,sizeof(d)),memset(incf,0x3f,sizeof(incf));
		memset(vis,0,sizeof(vis)),memset(pre,0,sizeof(pre));
		q.push(s),d[s]=0,vis[s]=1;
		while (q.size()){
			int x=q.front();q.pop();
			vis[x]=0;
			for (int i=head[x];i;i=e[i].nxt){
				int v=e[i].to;
				if (e[i].cap>e[i].flow&&d[v]>d[x]+e[i].cost){
					d[v]=d[x]+e[i].cost;
					pre[v]=i,incf[v]=min(incf[x],e[i].cap-e[i].flow);
					if (!vis[v])q.push(v),vis[v]=1;
				}
			}
		}
		return d[t]<0x3f3f3f3f;
	}
	void update(){
		maxflow+=incf[t],mincost+=incf[t]*d[t];
		int now=t;
		while (now!=s){
			int i=pre[now];
			e[i].flow+=incf[t],e[i^1].flow-=incf[t];
			now=e[i].from;
		}
	}
	void mincostMaxflow(){
		maxflow=mincost=0;
		while (spfa())update();
	}
}g;
int main(){
	int n,m,s,t;scanf("%d%d%d%d",&n,&m,&s,&t);
	g.init(s,t);for (int i=1;i<=m;i++){
		int x,y,w,c;scanf("%d%d%d%d",&x,&y,&w,&c);
		g.addedge(x,y,w,c);
	}
	g.mincostMaxflow();printf("%d %d\n",g.maxflow,g.mincost);
	return 0;
}










