#include <bits/stdc++.h>
using namespace std;
template<typename tp> inline void read(tp &x){
	x=0; tp f=1; char ch=getchar();
	for (;!isdigit(ch);ch=getchar())f=ch=='-'?-f:f;
	for (;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	x=x*f;
}
#define pb push_back
#define same(e1,e2) (min(e1^1,e1)==min(e2^1,e2))
typedef long long ll;
const ll INF=1e18;
const int N=2e6+10;
int cnt=1,fst[N],nxt[N<<1],to[N<<1];ll dis[N<<1];
inline void ade(int x,int y,ll w){
	to[++cnt]=y,nxt[cnt]=fst[x],fst[x]=cnt;
	dis[cnt]=w;
}
inline void addedge(int x,int y,ll w){ade(x,y,w),ade(y,x,w);}
vector<int>ring[N]; int tot=0,dep[N],fa[N];
void dfs(int x,int deep,int lste,int prev){
	dep[x]=deep,fa[x]=prev;
	for (int i=fst[x];i;i=nxt[i]){
		int v=to[i]; //printf("%d->%d\n",x,v);
		if (dep[v]==0) dfs(v,deep+1,i,x);
		else if (!same(i,lste)&&dep[v]<dep[x]){
			++tot;for (int nw=x;nw!=v;nw=fa[nw])ring[tot].pb(nw);
			ring[tot].pb(v);
		}
	}
}
int mark[N];ll dp[N],mxdp;
void DP(int x,int prev){
	for (int i=fst[x];i;i=nxt[i]){
		int v=to[i]; if (mark[v]||v==prev) continue;
		DP(v,x);
		mxdp=max(dp[x]+dp[v]+dis[i],mxdp);
		dp[x]=max(dp[x],dp[v]+dis[i]);
	}
}
int vis[N],id[N],tim;ll a[N],b[N];
void getW(int x,ll dd,int lste){
	vis[x]++,id[++tim]=x,b[tim]=dd;
	for (int i=fst[x];i;i=nxt[i]){
		int v=to[i]; if (!same(i,lste)&&mark[v]&&vis[v]<2)getW(v,dd+dis[i],i);
	}
}
int q[N];
ll solve(int k1){
	int len=ring[k1].size(); ll ans=0;
	for (int i=0;i<len;i++) mark[ring[k1][i]]=1;
	tim=0,getW(ring[k1][0],0,0);
	for (int i=1;i<=len;i++){
		int x=id[i]; 
		mxdp=0,DP(x,0),ans=max(ans,mxdp);
		a[i]=dp[x];
	}
	for (int i=1;i<=len;i++) a[i+len]=a[i];
//	for (int i=1;i<=tim;i++) cerr<<a[i]<<" "<<b[i]<<endl; cout<<"\n\n";
	int l=1,r=1; q[l]=1;
	for (int i=2;i<=tim;i++){
		while (l<=r&&i-q[l]>=len)l++;
		int j=q[l]; if (l<=r)ans=max(ans,a[i]+a[j]+b[i]-b[j]);
		while (l<=r&&a[i]-b[i]>a[q[r]]-b[q[r]])r--;
		q[++r]=i;
	}
	return ans;
}
int main(){
	int n;read(n);
	for (int i=1;i<=n;i++){
		int x;ll w; read(x),read(w);
		addedge(x,i,w);
	}
	for (int i=1;i<=n;i++) if (!dep[i])dfs(i,1,0,0);
	ll ans=0;
	for (int i=1;i<=tot;i++)ans+=solve(i);
	printf("%lld\n",ans);
	return 0;
}








