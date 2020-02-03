#include <bits/stdc++.h>
using namespace std;
const int MAXN=100010;
struct edge{int to,nxt;}e[MAXN<<1];
int head[MAXN],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
int color[MAXN],size[MAXN],id[MAXN],node[MAXN],idx=0;
void dfs(int x,int prev){
	size[x]=1;
	node[id[x]=++idx]=x;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v==prev) continue;	
		dfs(v,x);
		size[x]+=size[v];
	}
}
int n,Q,belong[MAXN];
struct Query{
	int l,r,k,id;
	bool operator < (Query& k1) const {
		if (belong[l]==belong[k1.l]) return r<k1.r;
		else return belong[l]<belong[k1.l]; 
	}
}q[MAXN];
int ans[MAXN],num[MAXN],val[MAXN];
void add(int i){
	val[color[node[i]]]++;
	num[val[color[node[i]]]]++;
}
void del(int i){
	num[val[color[node[i]]]]--;
	val[color[node[i]]]--;
}
void solve(){
	sort(q+1,q+Q+1);
	int nowl=1,nowr=0;
	for (int i=1;i<=Q;i++){
		int l=q[i].l,r=q[i].r;
		while (nowl>l) add(--nowl);
		while (nowr<r) add(++nowr);
		while (nowl<l) del(nowl++);
		while (nowr>r) del(nowr--);
		ans[q[i].id]=num[q[i].k];
	}
}
int main(){
	scanf("%d%d",&n,&Q);
	int block=sqrt(n);
	for (int i=1;i<=n;i++) belong[i]=(i-1)/block+1; 
	for (int i=1;i<=n;i++)scanf("%d",&color[i]);
	for (int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	dfs(1,0);
	for (int i=1;i<=Q;i++){
		int x,k;scanf("%d%d",&x,&k);
		q[i]=(Query){id[x],id[x]+size[x]-1,k,i};
	}
	solve();
	for (int i=1;i<=Q;i++)printf("%d\n",ans[i]);
	return 0;
}
/*
8 5
1 2 2 3 3 2 3 3
1 2
1 5
2 3
2 4
5 6
5 7
5 8
1 2
1 3
1 4
2 3
5 3
*/
/*
4 1
1 2 3 4
1 2
2 3
3 4
1 1
*/








