#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
const int INF=233333333;
const int N=233333;
int head[N],cnt=0;
struct edge{int to,nxt,w;}e[N*23];
void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
struct rmq{
	ll lg[N],dp[N][23],dis[N],id[N],cnt=0;
	void dfs(int x,int prev,ll d){
		dp[id[x]=++cnt][0]=dis[x]=d;
		for (int v,i=head[x];i;i=e[i].nxt)if ((v=e[i].to)!=prev)
			dfs(v,x,d+e[i].w),dp[++cnt][0]=dis[x];
	}
	void init(){
		lg[0]=-1;for (int i=1;i<=2e5;i++)lg[i]=lg[i/2]+1;
		dfs(1,0,0);for (int j=1;j<=18;j++)
			for (int i=1;i<=cnt&&i+(1<<j)-1<=cnt;i++)
				dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
	}
	ll query(int x,int y){
		if (x==y)return 0;
		if (id[x]>id[y])swap(x,y);
		int l=id[x],r=id[y],k=lg[r-l+1];
		return dis[x]+dis[y]-2*min(dp[l][k],dp[r-(1<<k)+1][k]);
	}
}T;
int size[N],mx[N],rt,sum,fa[N],vis[N];
void getrt(int x,int prev){
	size[x]=1,mx[x]=0;
	for (int i=head[x],v;i;i=e[i].nxt)
		if (!vis[v=e[i].to]&&v!=prev)getrt(v,x),size[x]+=size[v],mx[x]=max(mx[x],size[v]);
	mx[x]=max(mx[x],sum-size[x]);
	if (mx[x]<mx[rt])rt=x;
}
ll dis[N],disfa[N],sumv[N];
vector<pair<int,int> >g[N];
void solve(int x){
	vis[x]=1;
	for (int v,i=head[x];i;i=e[i].nxt)if (!vis[v=e[i].to]){
		mx[rt=0]=INF,sum=size[v],getrt(v,x);
		fa[rt]=x,g[x].pb(mp(rt,v)),solve(rt);
	}
}
void add(int x,ll v){
	sumv[x]+=v;
	for (int now=x;fa[now];now=fa[now]){
		ll d=T.query(x,fa[now]);
		dis[fa[now]]-=disfa[now];
		disfa[now]+=d*v;
		dis[fa[now]]+=disfa[now];
		sumv[fa[now]]+=v;
	}
}
ll calc(int x){
	ll ans=dis[x];
	for (int now=x;fa[now];now=fa[now])
		ans+=dis[fa[now]]-disfa[now],ans+=(sumv[fa[now]]-sumv[now])*T.query(x,fa[now]);
	return ans;
}
ll query(int x){
	ll ans=calc(x);
	for (int i=0;i<g[x].size();i++)
		if (calc(g[x][i].se)<ans)return query(g[x][i].fi);
	return ans;
}
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	int fstrt,n,m;scanf("%d%d",&n,&m);
	for (int x,y,w,i=1;i<=n-1;i++)scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	T.init(),sum=n,mx[rt=0]=INF,getrt(1,0),fstrt=rt,solve(rt);
	rt=fstrt;for (int i=1;i<=m;i++){
		int x,v;scanf("%d%d",&x,&v);
		add(x,v),printf("%lld\n",query(rt));
	}
	return 0;
}










