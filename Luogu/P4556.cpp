#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
struct segtree{
	int lc[233333*40],rc[233333*40],Max[233333*40],id[233333*40],cnt=0;
	void pushup(int x){
		if (Max[lc[x]]>=Max[rc[x]]){
			Max[x]=Max[lc[x]];id[x]=id[lc[x]];
		}else{
			Max[x]=Max[rc[x]];id[x]=id[rc[x]];
		}
	}
	int merge(int a,int b,int l,int r){
		if (!a||!b) return a+b;
		if (l==r){
			Max[a]=Max[a]+Max[b],id[a]=l;
			return a;
		}
		int mid=(l+r)>>1;
		lc[a]=merge(lc[a],lc[b],l,mid);rc[a]=merge(rc[a],rc[b],mid+1,r);
		return pushup(a),a;
	}	
	void ins(int &x,int l,int r,int p,int v){
		if (!x) x=++cnt;
		if (l==r){id[x]=l;Max[x]+=v;return;}
		int mid=(l+r)>>1;
		if (p<=mid)ins(lc[x],l,mid,p,v);else ins(rc[x],mid+1,r,p,v);
		pushup(x);
	}
}T;
struct edge{int to,nxt;}e[MAXN<<1];
int head[MAXN],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
int dep[MAXN],fa[MAXN][20];
void dfs(int x,int prev,int deep){
	dep[x]=deep;
	fa[x][0]=prev;
	for (int i=1;i<=18;i++)fa[x][i]=fa[fa[x][i-1]][i-1];
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev)continue;
		dfs(v,x,deep+1);
	}
}
int getlca(int x,int y){
	if (dep[x]<dep[y]) swap(x,y);
	for (int i=18;i>=0;i--)
		if (dep[fa[x][i]]>=dep[y])x=fa[x][i];
	if (x==y)return x;
	for (int i=18;i>=0;i--)
		if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int rt[MAXN],ans[MAXN];
void getans(int x,int prev){
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev)continue;
		getans(v,x);
		rt[x]=T.merge(rt[x],rt[v],1,100000);
	}
	ans[x]=T.id[rt[x]];
	if (T.Max[rt[x]]==0)ans[x]=0;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for (int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	dfs(1,0,1);
	for (int i=1;i<=m;i++){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		int lca=getlca(x,y);
		T.ins(rt[lca],1,100000,z,-1),T.ins(rt[fa[lca][0]],1,100000,z,-1);
		T.ins(rt[x],1,100000,z,1),T.ins(rt[y],1,100000,z,1);
	}
	getans(1,0);
	for (int i=1;i<=n;i++)printf("%d\n",ans[i]);
	return 0;
}











