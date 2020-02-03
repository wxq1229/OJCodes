#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int MAXN=100010;
struct edge{int from,to,nxt;}e[MAXN<<1];
int head[MAXN],val[MAXN],cnt=0;
inline void add(int x,int y){e[++cnt].to=y;e[cnt].from=x;e[cnt].nxt=head[x];head[x]=cnt;}
int dfn[MAXN],ins[MAXN],low[MAXN],c[MAXN],sum[MAXN],idx=0,scc_cnt=0;
stack<int>S;
void tarjan(int x){
	dfn[x]=low[x]=++idx;
	S.push(x),ins[x]=1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (!dfn[v]){
			tarjan(v);
			low[x]=min(low[x],low[v]);
		}
		else if (ins[v]) low[x]=min(low[x],dfn[v]);
	}
	if (dfn[x]==low[x]){
		int y;++scc_cnt;
		do{
			y=S.top();S.pop();
			ins[y]=0;c[y]=scc_cnt;
			sum[scc_cnt]+=val[y];
		}while (y!=x);
	}
}
int inq[MAXN],d[MAXN];
int spfa(int s){
	queue<int>q;
	memset(inq,0,sizeof(inq));
	memset(d,0xcf,sizeof(d));
	d[s]=sum[s];
	q.push(s);inq[s]=1;
	while (q.size()){
		int x=q.front();
		q.pop();
//		debug("%d\n",x);
		inq[x]=0;
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if (d[v]<d[x]+sum[v]){
				d[v]=d[x]+sum[v];
				if (!inq[v]){
					q.push(v);
					inq[v]=1;
				}
			}
		}
	}
	int ret=0;
	rep (i,1,scc_cnt)
		ret=max(ret,d[i]);
	return ret;
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	rep (i,1,n) scanf("%d",&val[i]);
	rep (i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);
	}
	rep (i,1,n)
		if (!dfn[i]) tarjan(i);
	memset(head,0,sizeof(head));
	rep (i,1,m){
		int x=e[i].from,y=e[i].to;
		if (c[x]==c[y])continue;
		add(c[x],c[y]);
	}
	int ans=0;
	rep (i,1,scc_cnt)
		ans=max(ans,spfa(i));
	printf("%d\n",ans);
	return 0;
}
/*
2 2
1 1
1 2
2 1






*/

