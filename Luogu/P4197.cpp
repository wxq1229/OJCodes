#include <bits/stdc++.h>
using namespace std;
struct segtree{
	int lc[233333*400],rc[233333*400],sum[233333*400],cnt=0;
	void pushup(int x){sum[x]=sum[lc[x]]+sum[rc[x]];}
	int merge(int a,int b,int l,int r){
		if (!a||!b) return a+b;
		if (l==r){sum[a]+=sum[b];return a;}
		int mid=(l+r)>>1;
		lc[a]=merge(lc[a],lc[b],l,mid),rc[a]=merge(rc[a],rc[b],mid+1,r);
		pushup(a);return a;
	}
	void ins(int &x,int l,int r,int p,int v){
		if (!x)x=++cnt;
		if (l==r){sum[x]+=v;return;}
		int mid=(l+r)>>1;
		if (p<=mid)ins(lc[x],l,mid,p,v);else ins(rc[x],mid+1,r,p,v);
		pushup(x);
	}
	int query(int x,int l,int r,int k){
		if (k>sum[x]) return 0;
		if (l==r) return l;
		int mid=(l+r)>>1;
		if (k<=sum[rc[x]])return query(rc[x],mid+1,r,k);
		else return query(lc[x],l,mid,k-sum[rc[x]]);
	}
}T;
int rt[2333333],fa[2333333],val[2333333],tot=0,n,m,Q;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
void link(int x,int y){
	x=find(x),y=find(y);
	if (x!=y)fa[y]=x,rt[x]=T.merge(rt[x],rt[y],1,tot);
}
struct edge{
	int x,y,w;
	bool operator < (const edge &k1)const{return w<k1.w;}
}e[2333333];
struct Query{
	int x,v,k,id;
	bool operator < (const Query &k1)const{return v<k1.v;}
}q[2333333];
int a[2333333],ans[2333333];
int main(){
	scanf("%d%d%d",&n,&m,&Q);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]),val[++tot]=a[i];
	sort(val+1,val+tot+1),tot=unique(val+1,val+tot+1)-val-1;
	for (int i=1;i<=n;i++)fa[i]=i,T.ins(rt[i],1,tot,lower_bound(val+1,val+tot+1,a[i])-val,1);
	for (int i=1;i<=m;i++)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].w);sort(e+1,e+m+1);
	for (int i=1;i<=Q;i++)scanf("%d%d%d",&q[i].x,&q[i].v,&q[i].k),q[i].id=i;sort(q+1,q+Q+1);
	int now=1;
	for (int i=1;i<=Q;i++){
		while (now<=m&&e[now].w<=q[i].v) link(e[now].x,e[now].y),now++;
		int u=find(q[i].x);
		int ret=T.query(rt[u],1,tot,q[i].k);
		ans[q[i].id]=ret?val[ret]:-1;
	}
	for (int i=1;i<=Q;i++)printf("%d\n",ans[i]);
	return 0;
}
/*
10 11 4
1 2 3 4 5 6 7 8 9 10
1 4 4
2 5 3
9 8 2
7 8 10
7 1 4
6 7 1
6 4 8
2 1 5
10 8 10
3 4 7
3 4 6
1 5 2
1 5 6
1 5 8
8 9 2
*/









