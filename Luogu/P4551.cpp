#include <bits/stdc++.h>
using namespace std;
const int N=233333*40;
struct edge{int to,nxt,w;}e[N*2];
int head[N],cnt=0;
void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
int ch[N][2],sz=1;
void ins(int v){
	int x=1;
	for(int i=31;i>=1;i--){
		bool k1=v&(1<<(i-1));
		if(!ch[x][k1])ch[x][k1]=++sz;
		x=ch[x][k1];
	}
}
int qry(int v){
	int x=1,ans=0;
	for(int i=31;i>=1;i--){
		bool k1=v&(1<<(i-1));
		if(!ch[x][k1^1])x=ch[x][k1],ans=ans<<1;
		else x=ch[x][k1^1],ans=ans<<1|1;
	}
	return ans;
}
int d[N];
void dfs(int x,int prev,int xr){
	ins(d[x]=xr);
	for(int i=head[x];i;i=e[i].nxt){int v=e[i].to; if(v!=prev)dfs(v,x,xr^e[i].w);}
}
int main(){
	int n;scanf("%d",&n);
	for(int i=1,x,y,w;i<=n-1;i++)scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	dfs(1,0,0);
	int ans=0;
	for(int i=1;i<=n;i++)ans=max(ans,qry(d[i]));
	printf("%d\n",ans);
	return 0;
}
