#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define debug(...) fprintf(stderr,__VA_ARGS__)
typedef long long ll;
typedef pair<int,int> pii;
typedef double db;

const int MAXN=400010;
int size[MAXN],ch[MAXN][2],id[MAXN],val[MAXN],fa[MAXN],tot,pos[MAXN];
queue<int> q;
inline void pushup(int x){
	size[x]=size[ch[x][0]]+size[ch[x][1]]+1;
}
inline int newnode(int v,int idx){
	int x;
	if(q.size()) x=q.front(),q.pop();
	else x=++tot;
	id[x]=idx;
	val[x]=v;size[x]=1;
	fa[x]=ch[x][0]=ch[x][1]=0;
	return x;
}
inline int chk(int x){return ch[fa[x]][1]==x;}
void rotate(int x){
	int y=fa[x],z=fa[y],k=chk(x),k1=chk(y),w=ch[x][k^1];
	ch[y][k]=w;if(w)fa[w]=y;
	ch[z][k1]=x;fa[x]=z;
	ch[x][k^1]=y;fa[y]=x;
	pushup(y),pushup(x);
}
void splay(int x,int goal=0){
	while(fa[x]!=goal){
		int y=fa[x],z=fa[y];
		if(z!=goal)
			rotate(chk(x)^chk(y)?x:y);
		rotate(x);	
	}
}
void insert(int v,int id,int x){
	int pre=0,k=-1;
	while(x)
		pre=x,k=v>val[pre],x=ch[pre][k];
	//debug("ch[%d][%d]\n",pre,k);
	pos[id]=x=newnode(v,id);
	ch[pre][k]=x;fa[x]=pre;
	splay(x);
}
int kth(int k,int rt){
	int x=rt;
	if(k<1||k>size[x]) return -1;
	while(233){
		if(k<=size[ch[x][0]])
			x=ch[x][0];
		else if(k==size[ch[x][0]]+1)
			return x;
		else k-=size[ch[x][0]]+1,x=ch[x][1];
	}
}
void recycle(int x){
	//debug("%d\n",__LINE__);
	if(ch[x][0]) recycle(ch[x][0]);
	if(ch[x][1]) recycle(ch[x][1]);
	q.push(x);
}
void dfs(int x,int y){
	//debug("%d\n",x);
	insert(val[x],id[x],y);
	if(ch[x][0]) dfs(ch[x][0],y);
	if(ch[x][1]) dfs(ch[x][1],y);
}

int pa[MAXN];
inline int findpa(int x){return x==pa[x]?x:pa[x]=findpa(pa[x]);}
void merge(int u,int v){
	int x=findpa(u),y=findpa(v);
	if(x==y)return;
	if(size[pos[x]]<size[pos[y]]) swap(x,y);
	pa[x]=y;
	splay(pos[x]),splay(pos[y]);
	int backup=pos[y];
	dfs(pos[y],pos[x]);
	recycle(backup);
}

int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	rep(i,1,n){
		int v;scanf("%d",&v);
		pos[i]=newnode(v,i);
		pa[i]=i;
	}
	rep(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		merge(x,y);
	}
	int Q;
	for(scanf("%d",&Q);Q;Q--){
		char ch=getchar();while(ch!='Q'&&ch!='B')ch=getchar();
		int x,y;
		scanf("%d%d",&x,&y);
		if(ch=='Q'){
			int now=pos[findpa(x)];
			splay(now);
			int ans=kth(y,now);
			printf("%d\n",ans==-1?-1:id[ans]);
		}else{
			merge(x,y);		
		}
	}
	return 0;
}

