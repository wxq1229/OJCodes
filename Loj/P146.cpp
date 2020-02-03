#include <bits/stdc++.h>
using namespace std;
template<class T> inline void read(T &x){
	x=0;T f=1;char ch=getchar();
	for (;!isdigit(ch);ch=getchar()) if (ch=='-') f=-f;
	for (;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
	x*=f;
}
typedef long long ll;
int n,m,r;
ll bit[2][2333333],val[2333333];
inline int lowbit(int x){return x&-x;}
void add(int i,int x,ll v){
	if (!x)return;
	for (;x<=n;x+=lowbit(x))bit[i][x]+=v;
}
ll query(int i,int x){
	ll ret=0;
	for (;x;x-=lowbit(x))ret+=bit[i][x];
	return ret;
}
struct edge{int to,nxt;}e[2333333];
int head[2333333],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
int size[2333333],son[2333333],top[2333333],L[2333333],R[2333333],dep[2333333],fa[2333333],idx=0;
void dfs1(int x,int prev,int deep){
	L[x]=++idx,dep[x]=deep,fa[x]=prev,size[x]=1;
	for (int maxson=-1,v,i=head[x];i;i=e[i].nxt){
		if ((v=e[i].to)!=prev){
			dfs1(v,x,deep+1),size[x]+=size[v];
			if (size[v]>maxson) maxson=size[v],son[x]=v;
		}
	}
	R[x]=idx;
}
void dfs2(int x,int topf){
	top[x]=topf;
	if (!son[x])return;
	dfs2(son[x],topf);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v!=fa[x]&&v!=son[x])dfs2(v,v);
	}
}
int getlca(int x,int y){
	while (top[x]!=top[y]) dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
	return dep[x]<dep[y]?x:y;
}
void update(int x,int y,ll v){
	int lca=getlca(x,y),falca=fa[lca];
	add(0,L[x],v),add(0,L[y],v),add(0,L[lca],-v),add(0,L[falca],-v);
	add(1,L[x],v*dep[x]),add(1,L[y],v*dep[y]),add(1,L[lca],-v*dep[lca]),add(1,L[falca],-v*dep[falca]);
}
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	read(n),read(m),read(r);
	for (int i=1;i<=n;i++)read(val[i]);
	for (int x,y,i=1;i<n;i++)read(x),read(y),addedge(x,y);
	dfs1(r,0,1),dfs2(r,r);
	for (int i=1;i<=n;i++)update(i,i,val[i]);
	while (m--){
		int opt,x,y;ll v;
		read(opt),read(x);
		if (opt==1)read(y),read(v),update(x,y,v);
		else if (opt==2) printf("%lld\n",query(0,R[x])-query(0,L[x]-1));
		else if (opt==3) printf("%lld\n",query(1,R[x])-query(1,L[x]-1)-(dep[x]-1)*(query(0,R[x])-query(0,L[x]-1)));
	}
	return 0;
}
