#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int fst[N],nxt[N<<1],to[N<<1],cnt=0;
inline void ade(int x,int y){
	to[++cnt]=y,nxt[cnt]=fst[x],fst[x]=cnt;
}
inline void addedge(int x,int y){ade(x,y),ade(y,x);}
struct Segtree{
	int lc[N*233],rc[N*233],sum[N*233],nd[N*233],cnt;
	void ins(int pre,int &x,int l,int r,int p,int id){
		x=++cnt,sum[x]=sum[pre]+1,lc[x]=lc[pre],rc[x]=rc[pre];
		if(l==r){nd[x]=id;return;} int mid=(l+r)>>1;
		if(p<=mid)ins(lc[pre],lc[x],l,mid,p,id);
		else ins(rc[pre],rc[x],mid+1,r,p,id);
	}
	int qry(int x,int y,int l,int r,int k){
		if(l==r)return nd[y]; int s=sum[lc[y]]-sum[lc[x]],mid=(l+r)>>1;
		if(k<=s) return qry(lc[x],lc[y],l,mid,k);
		else return qry(rc[x],rc[y],mid+1,r,k-s);
	}
	void build(int &x,int l,int r){
		sum[x=++cnt]=lc[x]=rc[x]=0;
		if(l==r)return; int mid=(l+r)>>1;
		build(lc[x],l,mid),build(rc[x],mid+1,r);
	}
}T;
int dfn[N],size[N],id[N],tim;
void dfs(int x,int prev){
	size[x]=1,dfn[x]=++tim,id[tim]=x;
	for(int i=fst[x];i;i=nxt[i]){
		if(to[i]==prev) continue;
		dfs(to[i],x),size[x]+=size[to[i]];
	}
}
int rt[N],a[N],val[N],tot,n,Q;
void init(){
	for(int i=1;i<=n;i++) val[i]=a[i];
	sort(val+1,val+n+1),tot=unique(val+1,val+n+1)-val-1;
	dfs(1,0),T.build(rt[0],1,tot);
	for(int i=1;i<=tim;i++)
		T.ins(rt[i-1],rt[i],1,tot,lower_bound(val+1,val+tot+1,a[id[i]])-val,id[i]);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1,x,y;i<=n-1;i++) scanf("%d%d",&x,&y),addedge(x,y);
	init();
	scanf("%d",&Q);
	for(int it=0;it<Q;it++){
		int x,k; scanf("%d%d",&x,&k);
		int at=T.qry(rt[dfn[x]-1],rt[dfn[x]+size[x]-1],1,tot,k);
		printf("%d\n",at);
	}
	return 0;
}
