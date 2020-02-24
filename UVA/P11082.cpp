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


const int N=1e5+10;

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
        memset(nxt,0,sizeof(nxt));
        cnt=1;
    }
}flow;

int n,m,sr[233],sc[233],s1[233],s2[233];
int id[233][233];
#define X(i) (i)
#define Y(i) ((i)+n)

void solve(int kase) {
    if(kase>1) puts("");
    printf("Matrix %d\n",kase);
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) scanf("%d",s1+i);
    rep(i,1,m+1) scanf("%d",s2+i);
    rep(i,1,n+1) sr[i]=s1[i]-s1[i-1];
    rep(i,1,m+1) sc[i]=s2[i]-s2[i-1];
    rep(i,1,n+1) sr[i]-=m;
    rep(i,1,m+1) sc[i]-=n;
    const int S=n+m+1,T=n+m+2;
    flow.init(n+m+5,S,T);
    rep(i,1,n+1) rep(j,1,m+1)
        id[i][j]=flow.cnt+1,flow.addedge(X(i),Y(j),19);
    rep(i,1,n+1) flow.addedge(S,X(i),sr[i]);
    rep(i,1,m+1) flow.addedge(Y(i),T,sc[i]);
    flow.Maxflow();
    rep(i,1,n+1) {
        rep(j,1,m+1) printf("%d ",flow.flow[id[i][j]]+1);
        puts("");
    }
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
	int T; scanf("%d",&T); rep(_,1,T+1) solve(_);
    return 0;
}
