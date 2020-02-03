#include <bits/stdc++.h>
using namespace std;
const int N=233333;
const int INF=233333333;
struct segtree{
	int lc[N*400],rc[N*400],sum[N*400],cnt=0;
	void pushup(int x){sum[x]=sum[lc[x]]+sum[rc[x]];}
	void ins(int &x,int l,int r,int p,int v=1){
		if (!x)x=++cnt;
		if (l==r)return (void)(sum[x]+=v);
		int mid=(l+r)>>1;
		if (p<=mid)ins(lc[x],l,mid,p,v);else ins(rc[x],mid+1,r,p,v);
		pushup(x);
	}
	int querysum(int x,int y,int l,int r,int ql,int qr){
		if (ql<=l&&r<=qr)return sum[x]-sum[y];
		int mid=(l+r)>>1,ret=0;
		if (ql<=mid)ret+=querysum(lc[x],lc[y],l,mid,ql,qr);
		if (mid<qr)ret+=querysum(rc[x],rc[y],mid+1,r,ql,qr);
		return ret;
	}
	int querykth(int x,int y,int l,int r,int k){
		if (l==r)return l;
		int mid=(l+r)>>1,s=sum[lc[x]]-sum[lc[y]];
		if (k<=s)return querykth(lc[x],lc[y],l,mid,k);
		else return querykth(rc[x],rc[y],mid+1,r,k-s);
	}
}T;
int disfa[N],dis[N],n,mod;
struct edge{int to,nxt,w;}e[N*23];
int head[N],cnt=0;
void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
struct LCA{
	int size[N],fa[N],dep[N],dis[N],son[N],top[N];
	void dfs1(int x,int prev,int deep,int d){
		dep[x]=deep,dis[x]=d,size[x]=1,fa[x]=prev,size[son[x]=0]=-1;
		for (int i=head[x],v;i;i=e[i].nxt)if ((v=e[i].to)!=prev)
			dfs1(v,x,deep+1,d+e[i].w),size[x]+=size[v],son[x]=size[v]>size[son[x]]?v:son[x];
	}
	void dfs2(int x,int topf){
		top[x]=topf;if (!son[x])return;
		dfs2(son[x],topf);for (int i=head[x],v;i;i=e[i].nxt)
			if ((v=e[i].to)!=fa[x]&&v!=son[x])dfs2(v,v);
	}
	int getlca(int x,int y){
		while (top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	int dist(int x,int y){
		int lca=getlca(x,y);
		return (dis[x]+dis[y]-2*dis[lca])%mod;
	}
	void init(int r=1){dfs1(r,0,1,0),dfs2(r,r);}
}g;
int rt,all,mx[N],size[N],fa[N],vis[N];
void getrt(int x,int prev){
	size[x]=1,mx[x]=0;
	for (int v,i=head[x];i;i=e[i].nxt)
		if (!vis[v=e[i].to]&&v!=prev)getrt(v,x),size[x]+=size[v],mx[x]=max(mx[x],size[v]);
	mx[x]=max(mx[x],all-size[x]);
	if (mx[x]<mx[rt])rt=x;
}
void getd(int x,int prev,int d,int &tr,int &tr2){
	T.ins(tr,0,mod-1,d),T.ins(tr2,0,mod-1,d);
	for (int i=head[x],v;i;i=e[i].nxt)
		if (!vis[v=e[i].to]&&v!=prev)getd(v,x,(d+e[i].w)%mod,tr,tr2);
}
void solve(int x){
	vis[x]=1;
	for (int i=head[x],v;i;i=e[i].nxt){
		if (vis[v=e[i].to])continue;
		mx[rt=0]=INF,all=size[v],getrt(v,x);
		fa[rt]=x,getd(v,x,e[i].w%mod,disfa[rt],dis[x]);
		solve(rt);
	}
	T.ins(dis[x],0,mod-1,0);
}
int query(int x){
	int k=T.sum[dis[x]],ans=k?T.querykth(dis[x],0,0,mod-1,k):-1,tmp;
	for (int now=x;fa[now];now=fa[now]){
		int d=g.dist(x,fa[now]);
//		printf("%d %d:\n",fa[now],now);
		k=T.querysum(dis[fa[now]],disfa[now],0,mod-1,0,mod-d-1);
		tmp=k?T.querykth(dis[fa[now]],disfa[now],0,mod-1,k):-1;
//		printf("tmp1=%d\n",tmp);
		if (tmp!=-1)ans=max(ans,d+tmp);
		k=T.querysum(dis[fa[now]],disfa[now],0,mod-1,0,mod-1);
		tmp=k?T.querykth(dis[fa[now]],disfa[now],0,mod-1,k):-1;
//		printf("tmp2=%d\n",tmp);
		if (tmp!=-1)ans=max(ans,(d+tmp)%mod);
	}
	return max(ans,0);
}
int main(){
	scanf("%d%d",&n,&mod);
	for (int x,y,w,i=1;i<=n-1;i++)scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	g.init(),mx[rt=0]=INF,all=n,getrt(1,0),solve(rt);
//	for (int i=1;i<=n;i++)printf("%d ",fa[i]);puts("");
	for (int i=1;i<=n;i++)printf("%d\n",query(i));
	return 0;
}

