#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<(b);++i)
#define per(i,a,b) for (int i=(a)-1;i>=(b);--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=1e5+10,INF=0x3f3f3f3f;

struct Dinic {
	int n,S,T;
	int to[N<<1],nxt[N<<1],fst[N],cap[N<<1],flow[N<<1],cnt=0;

	inline void ade(int x,int y,int w) {
		to[++cnt]=y,cap[cnt]=w,flow[cnt]=0;
		nxt[cnt]=fst[x],fst[x]=cnt;
	}
	inline void addedge(int x,int y,int w) {ade(x,y,w),ade(y,x,0);}

	int d[N],q[N];
	bool bfs() {
		rep(i,0,n+1) d[i]=0;
		int tn=1; q[0]=S;
		d[S]=1;
		rep(_,0,tn) {
			int u=q[_];
			for(int i=fst[u];i;i=nxt[i]) {
				int v=to[i];
				if(d[v]==0&&cap[i]>flow[i]) {
					d[v]=d[u]+1;
					q[tn++]=v;
				}
			}
		}
		return d[T]!=0;
	}

	int cur[N];
	int dfs(int x,int ag) {
		if(x==T||ag==0) return ag;
		for(int &i=cur[x];i;i=nxt[i]) {
			int v=to[i];
			if(cap[i]>flow[i]&&d[v]==d[x]+1) {
				int out=dfs(v,min(ag,cap[i]-flow[i]));
				if(out) {
					flow[i]+=out;
					flow[i^1]-=out;
					return out;
				}
				else d[v]=0;
			}
		}
		return 0;
	}

	int Maxflow() {
		int ans=0,out=0;
		while(bfs()) {
			rep(i,0,n+1) cur[i]=fst[i];
			while(out=dfs(S,1e9)) ans+=out;
		}
		return ans;
	}

	void init(int tn,int s,int t) {
		S=s,T=t,n=tn;
		rep(i,0,n+1) fst[i]=0;
		cnt=1;
	}
}flow;

#define IDL(x) (x)
#define IDR(x) ((x)+n)
#define NODE(x) ((x)<=n?(x):(x)-n)
int n,m;
int vis[233][233],mark[N];
VI g[N];

void dfs(int x) {
	printf("%d ",x);
	mark[x]=1;
	for(auto v:g[x]) if(vis[x][v])
		dfs(v);
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&m);
	const int S=n*2+1,T=n*2+2;
	flow.init(n*2+5,S,T);
	rep(i,1,n+1) flow.addedge(S,IDL(i),1),flow.addedge(IDR(i),T,1);
	rep(i,0,m) {
		int x,y; scanf("%d%d",&x,&y);
		flow.addedge(IDL(x),IDR(y),INF);
		g[x].pb(y),g[y].pb(x);
	}
	int ans=n-flow.Maxflow();
	rep(i,2,flow.cnt+1) if(flow.flow[i]==1)
		vis[NODE(flow.to[i^1])][NODE(flow.to[i])]=1;
	rep(i,1,n) if(!mark[i]) dfs(i),puts("");
	printf("%d\n",ans);
	return 0;
}