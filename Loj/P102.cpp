#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int N=15010;
const int INF=0x3f3f3f3f;
struct MCMF{
	int head[N],cnt;
	struct edge{
		int from,to,nxt;
		int cap,flow,cost;
	}e[N<<1];
	inline void add(int x,int y,int w,int c){
		e[++cnt].to=y;
		e[cnt].from=x;
		e[cnt].cap=w;
		e[cnt].flow=0;
		e[cnt].cost=c;
		e[cnt].nxt=head[x];
		head[x]=cnt;
	}
	inline void addedge(int x,int y,int w,int c){
		add(x,y,w,c);
		add(y,x,0,-c);
	}
	int s,t,maxflow,mincost;
	void init(int k1,int k2){
		s=k1,t=k2;
		cnt=1;
		memset(head,0,sizeof(head));
	}
	int d[N],inq[N],incf[N],pre[N];
	int spfa(){
		queue<int> q;
		q.push(s);
		memset(inq,0,sizeof(inq));
		memset(d,0x3f,sizeof(d));
		memset(incf,0x3f,sizeof(incf));
		memset(pre,0,sizeof(pre));
		incf[s]=INF;inq[s]=1;
		pre[s]=0;d[s]=0;
		while (q.size()){
			int x=q.front();
			q.pop();
			inq[x]=0;
			for (int i=head[x];i;i=e[i].nxt){
				int v=e[i].to;
				if (d[v]>d[x]+e[i].cost&&e[i].cap>e[i].flow){
					incf[v]=min(incf[x],e[i].cap-e[i].flow);
					pre[v]=i;
					d[v]=d[x]+e[i].cost;
					if (!inq[v]){
						inq[v]=1;
						q.push(v);
					}	
				}
			}
		}
		return d[t]<INF;
	}
	void update(){
		int now=t;
		maxflow+=incf[t];
		mincost+=incf[t]*d[t];
		while (now!=s){
			int i=pre[now];
			e[i].flow+=incf[t];
			e[i^1].flow-=incf[t];
			now=e[i].from;
		}
	}
	void mincostMaxflow(){
		maxflow=mincost=0;
		while (spfa())update();
	}
}g;
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	g.init(1,n);
	rep (i,1,m){
		int u,v,w,c;
		scanf("%d%d%d%d",&u,&v,&w,&c);
		g.addedge(u,v,w,c);
	}
	g.mincostMaxflow();
	printf("%d %d\n",g.maxflow,g.mincost);
	return 0;
}












