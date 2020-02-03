#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define MAXN 100010
typedef long long ll;
const ll INF=1e18;
int n,m,s,t;
int head[MAXN],cnt=1;
int cur[MAXN],d[MAXN];
struct edge{
	int to,nxt;
	ll cap,flow;
}e[MAXN<<1];
void add(int x,int y,ll w){
	e[++cnt].to=y;
	e[cnt].cap=w;
	e[cnt].flow=0;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
void addedge(int x,int y,ll w){
	add(x,y,w);
	add(y,x,0);
}
int bfs(){
	queue<int>q;
	q.push(s);
	memset(d,0,sizeof(d));
	d[s]=1;
	while (q.size()){
		int x=q.front();
		q.pop();
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if (d[v]==0&&e[i].cap>e[i].flow){
				d[v]=d[x]+1;
				q.push(v);
			}
		}
	}
	return d[t];
}
ll dfs(int x,ll a){
	if (x==t||a==0)return a;
	for (int& i=cur[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (d[v]==d[x]+1&&e[i].cap>e[i].flow){
			int out=dfs(v,min(a,e[i].cap-e[i].flow));
			if (out){
				e[i].flow+=out;
				e[i^1].flow-=out;
				return out;
			}
			else d[v]=0;
		}
	}
	return 0;
}
ll dinic(){
	ll maxflow=0;
	while (bfs()){
		memcpy(cur,head,sizeof(head));		
		ll out=0;
		while (out=dfs(s,INF))maxflow+=out;
	}
	return maxflow;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	rep (i,0,m-1){
		int u,v;ll w;
		scanf("%d%d%lld",&u,&v,&w);
		addedge(u,v,w);
	}
	printf("%lld\n",dinic());
	return 0;
}
