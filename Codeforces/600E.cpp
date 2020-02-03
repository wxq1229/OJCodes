#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+10;
typedef long long ll;
int head[MAXN],cnt=0;
struct edge{int to,nxt;}e[MAXN<<1];
void add(int x,int y){e[++cnt].to=y,e[cnt].nxt=head[x],head[x]=cnt;}
void addedge(int x,int y){add(x,y),add(y,x);}
ll sum[MAXN],num[MAXN],c[MAXN],max_cnt;
ll vis[MAXN],size[MAXN],fa[MAXN],son[MAXN];
void dfs1(int x,int prev){
	size[x]=1;
	fa[x]=prev;
	int maxson=-1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa[x]||vis[v])continue;
		dfs1(v,x);
		size[x]+=size[v];
		if (size[v]>maxson){
			maxson=size[v];
			son[x]=v;
		}
	}
}
void update(int x,int k1){
	sum[num[c[x]]]-=c[x];
	num[c[x]]+=k1;
	sum[num[c[x]]]+=c[x];
	if (sum[max_cnt+1])max_cnt++;
	if (!sum[max_cnt])max_cnt--;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v]||v==fa[x])continue;
		update(v,k1);
	}
}
ll ans[MAXN];
void dfs2(int x,int keep){
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==fa[x]||v==son[x])continue;
		dfs2(v,0);
	}
	if (son[x])
		dfs2(son[x],1),vis[son[x]]=1;
	update(x,1),vis[son[x]]=0;
	ans[x]=sum[max_cnt];
	if (!keep) update(x,-1);
}
int main(){
	int n;scanf("%d",&n);
	for (int i=1;i<=n;i++)scanf("%d",&c[i]);
	for (int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	dfs1(1,0),dfs2(1,0);
	for (int i=1;i<=n;i++)
		printf("%lld ",ans[i]);
	return 0;
}
/*
4
1 2 3 4
1 2
2 3
2 4
*/
/*
15
1 2 3 1 2 3 3 1 1 3 2 2 1 2 3
1 2
1 3
1 4
1 14
1 15
2 5
2 6
2 7
3 8
3 9
3 10
4 11
4 12
4 13
*/

