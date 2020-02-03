#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
const int MAXN=100010;
typedef long long ll;
ll a[MAXN],b[MAXN];
int head[MAXN],cnt=0;
struct edge{
	int to,nxt;
}e[MAXN<<1];
void adde(int x,int y){
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
void addedge(int x,int y){
	adde(x,y);
	adde(y,x);
}
int size[MAXN],fa[MAXN],dep[MAXN],top[MAXN],son[MAXN],id[MAXN],idx=0;
void dfs1(int x,int prev,int deep){
	size[x]=1;
	fa[x]=prev;
	dep[x]=deep;
	int maxson=-1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa[x])continue;
		dfs1(v,x,deep+1);
		size[x]+=size[v];
		if (size[v]>maxson){
			maxson=size[v];
			son[x]=v;
		}
	}
}
void dfs2(int x,int topf){
	top[x]=topf;
	id[x]=++idx;
	a[id[x]]=b[x];
	if (!son[x])return;
	dfs2(son[x],topf);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa[x]||v==son[x])continue;
		dfs2(v,v);
	}
}
int n,m,r,p;
struct seg{
	int l,r;
	ll sum,add;
}t[MAXN<<2];
inline void add(ll& x,ll v){x=(x+v)%p;}
inline int sum(ll x,ll y){return (x+y)%p;}
void pushup(int x){
	t[x].sum=sum(t[x<<1].sum,t[x<<1|1].sum);
}
void pushdown(int x){
	if (!t[x].add)return;
	int l=t[x].l,r=t[x].r;
	int mid=(l+r)>>1;
	add(t[x<<1].add,t[x].add);
	add(t[x<<1|1].add,t[x].add);
	add(t[x<<1].sum,t[x].add*(mid-l+1));
	add(t[x<<1|1].sum,t[x].add*(r-mid));
	t[x].add=0;
}
void build(int x,int l,int r){
	t[x].l=l,t[x].r=r;
	t[x].add=0,t[x].sum=0;
	if (l==r){
		t[x].sum=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int y1,int y2,ll v){
	int l=t[x].l,r=t[x].r;
	if (y1<=l&&r<=y2){
		add(t[x].add,v);
		add(t[x].sum,v*(r-l+1));
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if (y1<=mid)update(x<<1,y1,y2,v);
	if (mid<y2)update(x<<1|1,y1,y2,v);
	pushup(x);
}
int query(int x,int ql,int qr){
	int l=t[x].l,r=t[x].r;
	if (ql<=l&&r<=qr)return t[x].sum%p;
	pushdown(x);
	int mid=(l+r)>>1;
	ll res=0;
	if (ql<=mid) add(res,query(x<<1,ql,qr));
	if (mid<qr) add(res,query(x<<1|1,ql,qr));
	return res%p; 
}
void updatelink(int x,int y,ll v){
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		update(1,id[top[x]],id[x],v);
		x=fa[top[x]];
	}
	if (id[x]>id[y])swap(x,y);
	update(1,id[x],id[y],v);
}
int querylink(int x,int y){
	ll res=0;
	while (top[x]!=top[y]){
		if (dep[top[x]]<dep[top[y]]) swap(x,y);
		add(res,query(1,id[top[x]],id[x]));
		x=fa[top[x]];
	}
	if (id[x]>id[y])swap(x,y);
	add(res,query(1,id[x],id[y]));
	return res%p;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&r,&p);
	rep (i,1,n)scanf("%lld",&b[i]);
	rep (i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	dfs1(r,0,1);
	dfs2(r,r);
	build(1,1,n);
	rep (i,1,m){
		int opt,x,y,z;
		scanf("%d%d",&opt,&x);
		if (opt==4)printf("%d\n",query(1,id[x],id[x]+size[x]-1));
		else{
			scanf("%d",&y);
			if (opt==1)scanf("%d",&z),updatelink(x,y,z);
			else if (opt==2)printf("%d\n",querylink(x,y));
			else if (opt==3)update(1,id[x],id[x]+size[x]-1,y);
		}
	}
	return 0;
}










