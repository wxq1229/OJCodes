#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
const int MAXN=1e6+10;
const int INF=0x3f3f3f3f;
int ans=INF;
struct edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],ecur=0;
void addedge(int x,int y,int w){
	e[++ecur]=(edge){y,w,head[x]},head[x]=ecur;
	e[++ecur]=(edge){x,w,head[y]},head[y]=ecur;
}
int size[MAXN],fa[MAXN],son[MAXN];
int dep[MAXN],dis[MAXN];
int id[MAXN],nodeOf[MAXN],cnt=0;
map<ll,int>mindep;
void dfs1(int x,int prev){
	size[x]=1,fa[x]=prev;
	id[x]=++cnt;
	nodeOf[id[x]]=x;
	int maxson=-1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa[x])continue;
		dis[v]=dis[x]+e[i].w,dep[v]=dep[x]+1;
		dfs1(v,x);
		size[x]+=size[v];
		if (size[v]>maxson){
			maxson=size[v];
			son[x]=v;
		}
	}
}
int n,K;
void update(int x,int k1){
	if (k1==-1)mindep[dis[x]]=0;
	else{
		if (mindep[dis[x]]==0) mindep[dis[x]]=dep[x];
		else mindep[dis[x]]=min(mindep[dis[x]],dep[x]);
	}
}
void dfs2(int x,int keep){
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa[x]||v==son[x])continue;
		dfs2(v,0);
	}
	if (son[x]) dfs2(son[x],1);
	for (int ei=head[x];ei;ei=e[ei].nxt){
		int v=e[ei].to;
		if (v==fa[x]||v==son[x])continue;
		for (int i=0;i<size[v];i++){
			int need=K-dis[nodeOf[id[v]+i]]+dis[x]*2;
//			cerr<<mindep[need]+dep[nodeOf[id[v]+i]]-dep[x]*2<<endl;
			if (mindep[need]) ans=min(ans,mindep[need]+dep[nodeOf[id[v]+i]]-dep[x]*2);
		}
		for (int i=0;i<size[v];i++)
			update(nodeOf[id[v]+i],1);
	}
	update(x,1);
	int need=dis[x]+K;
//	assert(mindep[need] > dep[x]);
//	cerr << need << ": " << mindep[need] << " " << dep[x] << endl;
	if (mindep[need]) ans=min(ans,mindep[need]-dep[x]);
//	cerr << ans << endl;
	if (!keep){
		for (int i=0;i<size[x];i++)
			update(nodeOf[id[x]+i],-1);
	}
}
int main(){
	scanf("%d%d",&n,&K);
	rep (i,1,n-1){
		int x,y,w;
		scanf("%d%d%d",&x,&y,&w);
		x++,y++;addedge(x,y,w);
	}
	dep[1]=1;
	dfs1(1,0),dfs2(1,0);
	printf("%d\n",ans>=INF?-1:ans);
	return 0;
}
/*
4 3
0 1 1
1 2 2
1 3 4
*/







