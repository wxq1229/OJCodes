#include <bits/stdc++.h>
using namespace std;
struct Dijkstra{
	struct edge{int to,nxt,w;}e[233333*23];
	int head[233333*23],cnt=0;
	void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
	void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
	int d[233333*23],vis[233333*23],pre[233333*23],prew[233333*23];
	struct node{
		int x,dis;
		bool operator < (const node &k1)const{return dis>k1.dis;}
	};
	priority_queue<node>q;
	void init(){
		memset(d,0x3f,sizeof(d)),memset(vis,0,sizeof(vis)),memset(pre,0,sizeof(pre));
		memset(head,0,sizeof(head)),cnt=0;
		while (q.size())q.pop();
	}
	void dijkstra(int s=1){
		q.push((node){s,d[s]=0});
		while (q.size()){
			int x=q.top().x;q.pop();
			if (vis[x])continue;vis[x]=1;
			for (int i=head[x];i;i=e[i].nxt){
				int v=e[i].to;
				if (d[x]+e[i].w<d[v])
					q.push((node){v,d[v]=d[x]+e[i].w}),pre[v]=x,prew[v]=e[i].w;
				else if (d[x]+e[i].w==d[v]&&x<pre[v])
					pre[v]=x,prew[v]=e[i].w;
			}
		}
	}
}dj;
int n,m,K;
struct edge{int to,nxt,w;}e[233333*23];
int head[233333*23],cnt=0;
void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
void init(){
	for (int i=1;i<=n;i++)
		if (dj.pre[i])addedge(dj.pre[i],i,dj.prew[i]);
}
int size[233333*23],mx[233333*23],sum,root,vis[233333*23];
void getroot(int x,int prev){
	mx[x]=0,size[x]=1;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (!vis[v]&&v!=prev)
			getroot(v,x),size[x]+=size[v],mx[x]=max(mx[x],size[v]);
	}
	if ((mx[x]=max(mx[x],sum-size[x]))<mx[root])
		root=x;
}
int dis[233333*23],dep[233333*23],maxdis[233333*23],tot=0,id[233333*23],maxcnt[233333*23];
void getD(int x,int prev,int d,int deep){
	dis[++tot]=d,dep[tot]=deep,id[tot]=x;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (v!=prev&&!vis[v])getD(v,x,d+e[i].w,deep+1);
	}
}
int ans=0,ans_cnt=0;
void solve(int x){
	vis[x]=1,tot=0;
//	printf("For %d\n",x);
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v])continue;
		int lst=tot+1,now;
		getD(v,x,e[i].w,2),now=tot;
		for (int j=lst;j<=now;j++){
			if (K-dep[j]+1>=0&&maxdis[K-dep[j]+1]){
				if (dis[j]+maxdis[K-dep[j]+1]>ans)
					ans=dis[j]+maxdis[K-dep[j]+1],ans_cnt=1;
				else if (dis[j]+maxdis[K-dep[j]+1]==ans)
					ans_cnt+=maxcnt[K-dep[j]+1];
			}
		}
		for (int j=lst;j<=now;j++)
			if (dis[j]>maxdis[dep[j]])maxcnt[dep[j]]=1,maxdis[dep[j]]=dis[j];
			else if (dis[j]==maxdis[dep[j]])maxcnt[dep[j]]++;
	}
//	for (int i=1;i<=tot;i++)printf("%d %d %d\n",id[i],dep[i],dis[i]);
	for (int i=1;i<=tot;i++)
		if (dep[i]==K){
			if (dis[i]>ans)ans=dis[i],ans_cnt=1;
			else if (dis[i]==ans)ans_cnt++;
		}
	for (int i=1;i<=tot;i++)maxdis[dep[i]]=0;
	for (int i=head[x];i;i=e[i].nxt){
		int v=e[i].to;
		if (vis[v])continue;
		sum=size[v],mx[root=0]=23333333;
		getroot(v,x),solve(root);
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&K);
	dj.init();for (int i=1;i<=m;i++){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		dj.addedge(x,y,w);
	}
	dj.dijkstra(),init();
	sum=n,mx[root=0]=23333333;
	getroot(1,0),solve(root);
	printf("%d %d\n",ans,ans_cnt);
	return 0;
}










