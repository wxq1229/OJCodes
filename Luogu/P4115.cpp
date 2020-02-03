#include <bits/stdc++.h>
using namespace std;
const int N=233333;
const int INF=0x3f3f3f3f;
int head[N],cnt=0;
struct edge{int to,nxt,w;}e[N*2];
void adde(int x,int y,int w){e[++cnt]=(edge){y,head[x],w},head[x]=cnt;}
void addedge(int x,int y,int w){adde(x,y,w),adde(y,x,w);}
struct LCA{
	int dis[N],dep[N],fa[N],size[N],son[N],top[N];
	#define v e[i].to
	void dfs1(int x,int prev,int d,int deep){
		dis[x]=d,dep[x]=deep,size[x]=1,size[son[x]=0]=-1,fa[x]=prev;
		for (int i=head[x];i;i=e[i].nxt) if (v!=fa[x])
		dfs1(v,x,d+e[i].w,deep+1),size[x]+=size[v],son[x]=size[v]>size[son[x]]?v:son[x];
	}
	void dfs2(int x,int topf){
		top[x]=topf;if (!son[x])return;dfs2(son[x],topf);
		for (int i=head[x];i;i=e[i].nxt) if (v!=fa[x]&&v!=son[x])dfs2(v,v);
	}
	#undef v
	void init(int r=1){dfs1(r,0,0,1),dfs2(r,r);}
	int getlca(int x,int y){
		while (top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	int dist(int x,int y){return dis[x]+dis[y]-2*dis[getlca(x,y)];}
}G;
struct Heap{
	priority_queue<int>heap,delt;
	Heap(){init();}
	void init(){while (heap.size())heap.pop();while (delt.size())delt.pop();}
	void update(){while (delt.size()&&heap.top()==delt.top())heap.pop(),delt.pop();}
	void del(int x){delt.push(x);}
	void add(int x){heap.push(x);}
	inline int size(){return heap.size()-delt.size();}
	inline int top(){update();return size()?heap.top():-INF;}
	inline int top2(){int x=top(),y;del(x),y=top(),add(x);return y;}
	int getans(){
		if (size()>=2)return top()+top2();
		else if (size()==1)return max(top(),0);
		else return -INF;
	}
}ans,dis[N],disfa[N];
int col[N],n,m;
struct PDV{
	void add(Heap &hp){if (hp.size()>=2)ans.add(hp.getans());}
	void del(Heap &hp){if (hp.size()>=2)ans.del(hp.getans());}
	int vis[N],fa[N],size[N],mx[N],rt,all;
	#define v e[i].to
	void getrt(int x,int prev){
		mx[x]=0,size[x]=1;
		for (int i=head[x];i;i=e[i].nxt) if (v!=prev&&!vis[v])
			getrt(v,x),size[x]+=size[v],mx[x]=max(mx[x],size[v]);
		mx[x]=max(mx[x],all-size[x]);if (mx[x]<mx[rt])rt=x;
	}
	void getd(int x,int prev,int d,Heap &hp){
		hp.add(d);for (int i=head[x];i;i=e[i].nxt)
			if (!vis[v]&&v!=prev)getd(v,x,d+e[i].w,hp);
	}
	void dfs(int x){
		vis[x]=1;for (int i=head[x];i;i=e[i].nxt) if (!vis[v]){
			mx[rt=0]=INF,all=size[v],getrt(v,x);
			fa[rt]=x,getd(v,x,e[i].w,disfa[rt]);
			dis[x].add(disfa[rt].top()),dfs(rt);
		}
		dis[x].add(0),add(dis[x]);
	}
	#undef v
	void init(){cnt=n,mx[rt=0]=INF,all=n,getrt(1,0),dfs(rt);}
	int cnt;
	int query(){
		if (cnt==1)return 0;
		else if (cnt==0)return -INF;
		else if (cnt>=2)return max(ans.top(),0);
	}
	void modify(int x){
		if (!col[x])--cnt;else ++cnt;
		col[x]^=1;
		if (col[x])del(dis[x]),dis[x].del(0),add(dis[x]);
		else del(dis[x]),dis[x].add(0),add(dis[x]);
		for (int nw=x;fa[nw];nw=fa[nw]){
			int nxt=fa[nw],d=G.dist(x,nxt);
			if (!col[x]){
				del(dis[nxt]);
				if (dis[nxt].size())dis[nxt].del(disfa[nw].top());
				disfa[nw].add(d);
				dis[nxt].add(disfa[nw].top());
				add(dis[nxt]);
			}else{
				del(dis[nxt]);
				if (dis[nxt].size())dis[nxt].del(disfa[nw].top());
				if (disfa[nw].size())disfa[nw].del(d);
				dis[nxt].add(disfa[nw].top());
				add(dis[nxt]);
			}
		}
	}
}Solver;
int main(){
	scanf("%d",&n);
	for (int i=1,x,y,w;i<n;i++)scanf("%d%d%d",&x,&y,&w),addedge(x,y,w);
	G.init(),Solver.init();
	scanf("%d",&m);for (int ret,i=1,x;i<=m;i++){
		char ch=getchar();while (isspace(ch))ch=getchar();
		if (ch=='A'){
			ret=Solver.query();
			if (ret<=-INF)puts("They have disappeared.");
			else printf("%d\n",ret);
		}
		else scanf("%d",&x),Solver.modify(x);
	}
	return 0;
}









