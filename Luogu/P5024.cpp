#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=233333;
const ll INF=1e18;
int n,m;ll w[N];
struct edge{int to,nxt;}e[N*2];
int head[N],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
struct matrix{
	ll a[3][3],n,m;
	void init(int R,int C){
		n=R,m=C;for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)a[i][j]=-INF;
	}
	matrix(int R=0,int C=0){init(R,C);}
	matrix operator * (const matrix &k1)const{
		matrix ret(this->n,k1.m);
		for (int k=0;k<k1.n;k++)
			for (int i=0;i<n;i++)
				for (int j=0;j<k1.m;j++)ret.a[i][j]=max(ret.a[i][j],a[i][k]+k1.a[k][j]);
		return ret;
	}
}val[N];
struct segtree{
	matrix mat[N*4];
	void pushup(int x){mat[x]=mat[x*2]*mat[x*2+1];}
	void modify(int x,int l,int r,int p){
		if (l==r){mat[x]=val[p];return;}
		int mid=(l+r)>>1;
		if (p<=mid)modify(x*2,l,mid,p);else modify(x*2+1,mid+1,r,p);
		pushup(x);
	}
	matrix query(int x,int l,int r,int ql,int qr){
		if (ql<=l&&r<=qr)return mat[x];
		int mid=(l+r)>>1;
		if (qr<=mid)return query(x*2,l,mid,ql,qr);
		else if (mid<ql)return query(x*2+1,mid+1,r,ql,qr);
		else return query(x*2,l,mid,ql,qr)*query(x*2+1,mid+1,r,ql,qr);
	}
	void build(int x,int l,int r){
		if (l==r){mat[x]=val[l];return;}
		int mid=(l+r)>>1;
		build(x*2,l,mid),build(x*2+1,mid+1,r);
		pushup(x);
	}
}T;
int idx=0,id[N],ed[N],dep[N],fa[N],son[N],top[N],size[N];
void dfs1(int x,int prev,int deep){
	dep[x]=deep,size[x]=1,size[son[x]=0]=-1,fa[x]=prev;
	for (int i=head[x],v;i;i=e[i].nxt)
		if ((v=e[i].to)!=fa[x])dfs1(v,x,deep+1),size[x]+=size[v],son[x]=size[v]>size[son[x]]?v:son[x];
}
ll f[N][2],g[N][2];
void dfs2(int x,int topf){
	top[x]=topf,ed[topf]=x,id[x]=++idx;
	g[x][0]=0,g[x][1]=w[x];
	if (!son[x]){
		f[x][0]=0,f[x][1]=w[x];
		val[id[x]].init(2,1),val[id[x]].a[0][0]=f[x][0],val[id[x]].a[1][0]=f[x][1];
		return;
	}
	dfs2(son[x],topf);
	for (int i=head[x],v;i;i=e[i].nxt) if ((v=e[i].to)!=fa[x]&&v!=son[x])
		dfs2(v,v),g[x][0]+=max(f[v][0],f[v][1]),g[x][1]+=f[v][0];	
	f[x][0]=g[x][0]+max(f[son[x]][0],f[son[x]][1]),f[x][1]=g[x][1]+f[son[x]][0];
	val[id[x]].init(2,2),val[id[x]].a[0][0]=val[id[x]].a[0][1]=g[x][0],val[id[x]].a[1][0]=g[x][1];
}
void modify(int x,ll v){
	val[id[x]].a[1][0]+=v;
	while (x){
		matrix lst=T.query(1,1,n,id[top[x]],id[ed[top[x]]]);
		T.modify(1,1,n,id[x]);
		matrix now=T.query(1,1,n,id[top[x]],id[ed[top[x]]]);
		int nxt=fa[top[x]];
		val[id[nxt]].a[0][0]+=max(now.a[0][0],now.a[1][0])-max(lst.a[0][0],lst.a[1][0]);
		val[id[nxt]].a[0][1]=val[id[nxt]].a[0][0];
		val[id[nxt]].a[1][0]+=now.a[0][0]-lst.a[0][0];
		x=nxt;
	}
}
ll query(int x){
	matrix ans=T.query(1,1,n,id[x],id[ed[top[x]]]);
	return max(ans.a[0][0],ans.a[1][0]);
}
char buf[233];
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%s",&n,&m,buf);ll sum=0;
	for (int i=1;i<=n;i++)scanf("%lld",&w[i]),sum+=w[i];
	for (int i=1,x,y;i<=n-1;i++)scanf("%d%d",&x,&y),addedge(x,y);
	dfs1(1,0,1),dfs2(1,1),T.build(1,1,n);
	for (int i=1;i<=m;i++){
		int x,y,v1,v2;scanf("%d%d%d%d",&x,&v1,&y,&v2);
		if (!v1&&!v2&&(fa[x]==y||fa[y]==x)){puts("-1");continue;}
		modify(x,v1?-INF:INF),modify(y,v2?-INF:INF);
		sum+=(v1==0?INF:0)+(v2==0?INF:0);
		ll ret=sum-query(1);
		sum-=(v1==0?INF:0)+(v2==0?INF:0);
		modify(x,v1?INF:-INF),modify(y,v2?INF:-INF);
		printf("%lld\n",ret);
	}
	return 0;
}
