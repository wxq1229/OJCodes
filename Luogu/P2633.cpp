#include <bits/stdc++.h>
using namespace std;
struct segtree{
	int lc[233333*400],rc[233333*400],sum[233333*400],cnt=0;
	void ins(int &x,int pre,int l,int r,int p){
		lc[x=++cnt]=lc[pre],rc[x]=rc[pre],sum[x]=sum[pre]+1;
		if (l==r)return;
		int mid=(l+r)>>1;
		if (p<=mid)ins(lc[x],lc[pre],l,mid,p);else ins(rc[x],rc[pre],mid+1,r,p);
	}
	void build(int &x,int l,int r){
		lc[x=++cnt]=sum[x]=rc[x]=0;
		if (l==r)return;
		int mid=(l+r)>>1;
		build(lc[x],l,mid),build(rc[x],mid+1,r);
	}
	int query(int x,int y,int lca,int falca,int l,int r,int k){
		if (k>sum[x]+sum[y]-sum[lca]-sum[falca])return 0;
		if (l==r)return l;
		int mid=(l+r)>>1,s=sum[lc[x]]+sum[lc[y]]-sum[lc[lca]]-sum[lc[falca]];
		if (k<=s)return query(lc[x],lc[y],lc[lca],lc[falca],l,mid,k);
		else return query(rc[x],rc[y],rc[lca],rc[falca],mid+1,r,k-s);
	}
}T;
struct edge{
	int to,nxt;
}e[233333];
int head[233333],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
int rt[233333],dep[233333],fa[233333][20],val[233333],a[233333],tot=0;
void dfs(int x,int prev,int deep){
	dep[x]=deep,fa[x][0]=prev,T.ins(rt[x],rt[prev],1,tot,lower_bound(val+1,val+tot+1,a[x])-val);
	for (int i=1;i<=18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=head[x];i;i=e[i].nxt) if (e[i].to!=prev)dfs(e[i].to,x,deep+1);
}
int getlca(int x,int y){
	if (dep[x]<dep[y])swap(x,y);
	for (int i=18;i>=0;i--) if (dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if (x==y)return x;
	for (int i=18;i>=0;i--) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]),val[++tot]=a[i];
	sort(val+1,val+tot+1),tot=unique(val+1,val+tot+1)-val-1;
	for (int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	T.build(rt[0],1,tot),dfs(1,0,1);
	for (int lstans=0,lca,i=1;i<=m;i++){
		int x,y,k;scanf("%d%d%d",&x,&y,&k);
		x^=lstans,lca=getlca(x,y);
		printf("%d\n",lstans=val[T.query(rt[x],rt[y],rt[lca],rt[fa[lca][0]],1,tot,k)]);
	}
	return 0;
}
/*
8 5
105 2 9 3 8 5 7 7
1 2
1 3
1 4
3 5
3 6
3 7
4 8
2 5 1
0 5 2
10 5 3
11 5 4
110 8 2
*/

