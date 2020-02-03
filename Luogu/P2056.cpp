#include <bits/stdc++.h>
using namespace std;
const int N=233333;
const int INF=0x3f3f3f3f;
struct edge{int to,nxt;}e[N*23];
int head[N],cnt=0;
void adde(int x,int y){e[++cnt]=(edge){y,head[x]},head[x]=cnt;}
void addedge(int x,int y){adde(x,y),adde(y,x);}
struct LCA{
	int dep[N],fa[N],son[N],size[N],top[N];
	void dfs1(int x,int prev,int deep){
		dep[x]=deep,fa[x]=prev,size[son[x]=0]=-1,size[x]=1;
		for (int v,i=head[x];i;i=e[i].nxt) if (e[i].to!=fa[x])
			dfs1(v=e[i].to,x,deep+1),size[x]+=size[v],son[x]=size[v]>size[son[x]]?v:son[x];
	}
	void dfs2(int x,int topf){
		top[x]=topf; if (!son[x])return;
		dfs2(son[x],topf);for (int v,i=head[x];i;i=e[i].nxt)
			if ((v=e[i].to)!=fa[x]&&v!=son[x])dfs2(v,v);
	}
	void init(int r=1){dfs1(r,0,1),dfs2(r,r);}
	int getlca(int x,int y){
		while (top[x]!=top[y])dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	int query(int x,int y){return dep[x]+dep[y]-2*dep[getlca(x,y)];}
}g;
struct Heap{
	priority_queue<int>heap,delt;
	int size(){return heap.size()-delt.size();}
	void update(){while (delt.size()&&heap.top()==delt.top())heap.pop(),delt.pop();}
	int top(){return update(),heap.top();}
	void pop(){update(),heap.pop();}
	int top2(){int t1,t2;t1=top(),pop(),t2=top(),ins(t1);return t2;}
	void ins(int x){heap.push(x);}
	void del(int x){delt.push(x);}
}ans,ch[N],disfa[N];
void add(Heap &hp){
	if (hp.size()>=2)ans.ins(hp.top()+hp.top2());
}
void del(Heap &hp){
	if (hp.size()>=2)ans.del(hp.top()+hp.top2());
}
int sum,vis[N],fa[N],size[N],mx[N],rt;
void getrt(int x,int prev){
	size[x]=1,mx[x]=0;
	for (int i=head[x],v;i;i=e[i].nxt)if (!vis[v=e[i].to]&&v!=prev)
		getrt(v,x),size[x]+=size[v],mx[x]=max(mx[x],size[v]);
	mx[x]=max(mx[x],sum-size[x]);
	if (mx[x]<mx[rt])rt=x;
}
void getd(int x,int prev,int deep,Heap &hp){
	hp.ins(deep);
	for (int i=head[x],v;i;i=e[i].nxt)
		if (!vis[v=e[i].to]&&v!=prev)getd(v,x,deep+1,hp);
}
void solve(int x){
	vis[x]=1;
	for (int i=head[x],v;i;i=e[i].nxt)if (!vis[v=e[i].to]){
		sum=size[v],mx[rt=0]=INF,getrt(v,x);
		fa[rt]=x,getd(v,x,1,disfa[rt]),ch[x].ins(disfa[rt].top());
		solve(rt);
	}
	ch[x].ins(0),add(ch[x]);
}
void modify(int x,int c){
	if (c){
		del(ch[x]),ch[x].del(0),add(ch[x]);
		for (int now=x;fa[now];now=fa[now]){
			int d=g.query(x,fa[now]);
			del(ch[fa[now]]);
			if (disfa[now].size())ch[fa[now]].del(disfa[now].top());
			disfa[now].del(d);
			if (disfa[now].size())ch[fa[now]].ins(disfa[now].top());
			add(ch[fa[now]]);
		}
	}else{
		del(ch[x]),ch[x].ins(0),add(ch[x]);
		for (int now=x;fa[now];now=fa[now]){
			int d=g.query(x,fa[now]);
			del(ch[fa[now]]);
			if (disfa[now].size())ch[fa[now]].del(disfa[now].top());
			disfa[now].ins(d);
			if (disfa[now].size())ch[fa[now]].ins(disfa[now].top());
			add(ch[fa[now]]);
		}
	}
}
int col[N];
int main(){
	int n,m;scanf("%d",&n);for (int i=1;i<n;i++){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	g.init(),sum=n,mx[rt=0]=INF,getrt(1,0),solve(rt);
	scanf("%d",&m);for (int i=1,cnt=n;i<=m;i++){
		char ch=getchar();while (ch!='C'&&ch!='G')ch=getchar();
		if (ch=='G'){
			if (cnt>=2)printf("%d\n",ans.top());
			else if (cnt==1)puts("0");
			else puts("-1");
			continue;
		}
		int x;scanf("%d",&x);
		if (col[x])++cnt;else --cnt;
		modify(x,col[x]^=1);
	}
	return 0;
}









