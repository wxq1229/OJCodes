#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+10;
struct edge{
	int to,w,nxt;
}e[MAXN];
int head[MAXN],cnt=0;
void adde(int x,int y,int w){e[++cnt]=(edge){y,w,head[x]},head[x]=cnt;}
int son[MAXN],dep[MAXN],pre[MAXN],size[MAXN];
int id[MAXN],node[MAXN],idx=0;
void dfs(int x,int S,int deep){
	size[x]=1;
	dep[x]=deep;
	pre[x]=S;
	id[x]=++idx;
	node[id[x]]=x;
	int maxson=-1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		dfs(v,pre[x]^(1<<e[i].w),deep+1);
		size[x]+=size[v];
		if (size[v]>maxson){
			maxson=size[v];
			son[x]=v;
		}
	}
}
int ans[MAXN],maxdep[1<<23];
void solve(int x,int keep){
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==son[x]) continue;
		solve(v,0),ans[x]=max(ans[x],ans[v]);
	}
	if (son[x]) solve(son[x],1),ans[x]=max(ans[x],ans[son[x]]);
	if (maxdep[pre[x]])ans[x]=max(ans[x],maxdep[pre[x]]-dep[x]);
	for (int i=0;i<22;i++)
		if (maxdep[pre[x]^(1<<i)])ans[x]=max(ans[x],maxdep[pre[x]^(1<<i)]-dep[x]);
	maxdep[pre[x]]=max(maxdep[pre[x]],dep[x]);
	for (int ei=head[x];ei;ei=e[ei].nxt){
		int v=e[ei].to;
		if (v==son[x]) continue;
		for (int i=id[v];i<=id[v]+size[v]-1;i++){
			int y=node[i];
			if (maxdep[pre[y]])ans[x]=max(ans[x],maxdep[pre[y]]+dep[y]-dep[x]*2);
			for (int j=0;j<22;j++)
				if (maxdep[pre[y]^(1<<j)])ans[x]=max(ans[x],maxdep[pre[y]^(1<<j)]+dep[y]-dep[x]*2);
		}
		for (int i=id[v];i<=id[v]+size[v]-1;i++)
			maxdep[pre[node[i]]]=max(maxdep[pre[node[i]]],dep[node[i]]);
	}
	if (!keep){
		for (int i=id[x];i<=id[x]+size[x]-1;i++)
			maxdep[pre[node[i]]]=0;
	}
}
int main(){
	int n;scanf("%d",&n);
	for (int i=2;i<=n;i++){
		int fa;scanf("%d",&fa);
		char ch=getchar();while (!islower(ch))ch=getchar();
		adde(fa,i,ch-'a');
	}
	dfs(1,0,1);
	solve(1,1);
	for (int i=1;i<=n;i++)
		printf("%d ",ans[i]);	
	return 0;
}










