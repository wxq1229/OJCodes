#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
struct segtree{
	int lc[233333*400],rc[233333*400],sum[233333*400],cnt=0;
	void pushup(int x){sum[x]=sum[lc[x]]+sum[rc[x]];}
	void ins(int &x,int pre,int l,int r,int p,int v){
		x=++cnt;
		lc[x]=lc[pre],rc[x]=rc[pre],sum[x]=sum[pre]+v;
		if (l==r)return;
		int mid=(l+r)>>1;
		if (p<=mid)ins(lc[x],lc[pre],l,mid,p,v);
		else ins(rc[x],rc[pre],mid+1,r,p,v);
	}
	int query(int x,int y,int l,int r,int k){
		if (k>sum[y]-sum[x]) return 0;
		if (l==r) return l;
		int mid=(l+r)>>1;
		if (k<=sum[rc[y]]-sum[rc[x]])return query(rc[x],rc[y],mid+1,r,k);
		else return query(lc[x],lc[y],l,mid,k-(sum[rc[y]]-sum[rc[x]]));
		
	}
	void build(int &x,int l,int r){
		x=++cnt;
		if (l==r)return;
		int mid=(l+r)>>1;
		build(lc[x],l,mid),build(rc[x],mid+1,r),pushup(x);
	}
}T;
int n,m,Q;
int rt[2333333],pa[2333333];
int val[2333333],tot=0;
pair<int,pair<int,int> > es[2333333];
int findpa(int x){return x==pa[x]?x:pa[x]=findpa(pa[x]);}
struct edge{
	int to,nxt;
}e[2333333];
int head[2333333],cnt=0,a[2333333];
void addedge(int x,int y){
	e[++cnt]=(edge){y,head[x]},head[x]=cnt;
}
int fa[233333*40][20],L[2333333],R[2333333],leafs[2333333],idx=0;
inline int isleaf(int x){return !head[x];}
void dfs(int x){
	for (int i=1;i<=18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	L[x]=idx;
	if (isleaf(x))return (void)(R[x]=++idx,leafs[idx]=x);
	for (int i=head[x];i;i=e[i].nxt)
		fa[e[i].to][0]=x,dfs(e[i].to);
	R[x]=idx;
}
void kruskal(){
	sort(es+1,es+m+1);int size=n;
	for (int i=1;i<=n;i++)pa[i]=i;
	for (int i=1;i<=m;i++){
		int w=es[i].fi,x=es[i].se.fi,y=es[i].se.se;
		x=findpa(x),y=findpa(y);
		if (x==y)continue;
		++size,addedge(size,x),addedge(size,y);
		pa[x]=pa[y]=pa[size]=size,a[size]=w;
	}
	T.build(rt[0],1,tot);
	dfs(size);
	for (int i=1;i<=idx;i++)
		T.ins(rt[i],rt[i-1],1,tot,lower_bound(val+1,val+tot+1,a[leafs[i]])-val,1);
}
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]),val[++tot]=a[i];
	sort(val+1,val+tot+1),tot=unique(val+1,val+tot+1)-val-1;
	for (int i=1;i<=m;i++)scanf("%d%d%d",&es[i].se.fi,&es[i].se.se,&es[i].fi);
	kruskal();
	for (int i=1;i<=Q;i++){
		int x,v,k;scanf("%d%d%d",&x,&v,&k);
		for (int j=18;j>=0;j--)
			if (fa[x][j]&&a[fa[x][j]]<=v)x=fa[x][j];
		int pos=T.query(rt[L[x]],rt[R[x]],1,tot,k);
		if (!pos)puts("-1");else printf("%d\n",val[pos]);
	}
	return 0;
}











