#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
struct edge{
	int to,nxt,w;
}e[N<<1];
int fst[N],cnt;
inline void ade(int x,int y,int w){
	e[++cnt]=(edge){y,fst[x],w},fst[x]=cnt;
}
inline void addedge(int x,int y,int w){
	ade(x,y,w),ade(y,x,w);
}
int dis[N],dfn[N],id[N],size[N],fa[N],top[N],son[N],dep[N],idx=0,anc[N][23];
void dfs1(int x,int prev,int deep,int dd){
	dfn[x]=++idx,id[idx]=x,dep[x]=deep,size[x]=1;
	anc[x][0]=fa[x]=prev,size[son[x]=0]=-1,dis[x]=dd;
	for(int i=1;i<=18;i++)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=fst[x];i;i=e[i].nxt){
		int v=e[i].to; if(v==prev) continue;
		dfs1(v,x,deep+e[i].w,dd+1),size[x]+=size[v];
		if(size[v]>size[son[x]]) son[x]=v;
	}
}
void dfs2(int x,int topf){
	top[x]=topf; if(son[x]){
		dfs2(son[x],topf);
		for(int i=fst[x];i;i=e[i].nxt){
			int v=e[i].to; if(v==fa[x]||v==son[x])continue;
			dfs2(v,v);
		}
	}
}
int getlca(int x,int y){
	for(;top[x]!=top[y];dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
	return dep[x]<dep[y]?x:y;
}
int getdist(int x,int y){
	int lca=getlca(x,y);
	return 1ll*dep[x]+1ll*dep[y]-2ll*dep[lca];
}
struct node{
	int l,r,lca;
}t[N<<2];
inline void pushup(int x){
	t[x].lca=getlca(t[x<<1].lca,t[x<<1|1].lca);
}
void build(int x,int l,int r){
	t[x]=(node){l,r,0};
	if(l==r){t[x].lca=l;return;} int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	pushup(x);
}
int qry(int x,int ql,int qr){
	int l=t[x].l,r=t[x].r;
	if(ql<=l&&r<=qr){return t[x].lca;}
	int mid=(l+r)>>1;
	if(qr<=mid) return qry(x<<1,ql,qr);
	else if(mid<ql) return qry(x<<1|1,ql,qr);
	else return getlca(qry(x<<1,ql,qr),qry(x<<1|1,ql,qr));
}
struct Segtree{
	int lc[N*40],rc[N*40],sum[N*40],cnt;
	void ins(int pre,int &x,int l,int r,int p,int v=1){
		x=++cnt,lc[x]=lc[pre],rc[x]=rc[pre],sum[x]=sum[pre]+v;
		if(l==r)return;	int mid=(l+r)>>1;
		if(p<=mid) ins(lc[pre],lc[x],l,mid,p,v);
		else ins(rc[pre],rc[x],mid+1,r,p,v);
	}
	void build(int &x,int l,int r){
		x=++cnt,sum[x]=lc[x]=rc[x]=0; if(l==r)return;
		int mid=(l+r)>>1; build(lc[x],l,mid),build(rc[x],mid+1,r);
	}
	int qry(int x,int y,int l,int r,int ql,int qr){
		if(ql<=l&&r<=qr) return sum[y]-sum[x]; int mid=(l+r)>>1,ret=0;
		if(ql<=mid) ret+=qry(lc[x],lc[y],l,mid,ql,qr);
		if(mid<qr) ret+=qry(rc[x],rc[y],mid+1,r,ql,qr);
		return ret;
	}
}T;
int rt[N],n,Q;
void init(){
	dfs1(1,0,0,1),dfs2(1,1);
	T.build(rt[0],1,n); build(1,1,n);
	for(int i=1;i<=idx;i++) T.ins(rt[i-1],rt[i],1,n,id[i]);
}
int main(){
#ifdef WXQ
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d",&n,&Q);
	for(int i=1,x,y,w;i<n;i++) scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	init();
	int lastans=0; while(Q--){
		int p,l,r; scanf("%d%d%d",&p,&l,&r);
		p^=lastans,l^=lastans,r^=lastans;
//		cout << p << " " << l << " " << r << endl;
		int k1=T.qry(rt[dfn[p]-1],rt[dfn[p]+size[p]-1],1,n,l,r);
		if(k1==r-l+1){printf("%d\n",lastans=dep[qry(1,l,r)]-dep[p]);continue;}
		if(k1!=0){lastans=0,puts("0");continue;}
		int x=p; for(int i=18;i>=0;i--){
			int nxt=anc[x][i]; if(!nxt) continue;
			if(T.qry(rt[dfn[nxt]-1],rt[dfn[nxt]+size[nxt]-1],1,n,l,r)==0) x=nxt;
		}
		x=fa[x];
		int lca=qry(1,l,r);
		if(dis[lca]>dis[x]) printf("%d\n",lastans=getdist(p,lca));
		else printf("%d\n",lastans=dep[p]-dep[x]);
	}
	return 0;
}
