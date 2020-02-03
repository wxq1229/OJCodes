#include <bits/stdc++.h>
using namespace std;

const int N=300010;
int val[N],fa[N],ch[N][2],sx[N],rev[N];
void setr(int x){swap(ch[x][0],ch[x][1]);rev[x]^=1;}
void pushup(int x){sx[x]=sx[ch[x][0]]^sx[ch[x][1]]^val[x];}
void pushdown(int x){
	if (rev[x]){
		setr(ch[x][0]);
		setr(ch[x][1]);
		rev[x]=0;
	}
}
inline int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
inline int chk(int x){return ch[fa[x]][1]==x;}
void rotate(int x){
	int y=fa[x],z=fa[y];
	int k=chk(x),k1=chk(y);
	int w=ch[x][k^1];
	ch[y][k]=w;if (w)fa[w]=y;
	if (!isroot(y))ch[z][k1]=x;fa[x]=z;
	ch[x][k^1]=y;fa[y]=x;
	pushup(y),pushup(x);
}
void pushall(int x){
	if (!isroot(x))pushall(fa[x]);
	pushdown(x);
}
void splay(int x){
	pushall(x);
	while (!isroot(x)){
		int y=fa[x];
		if (!isroot(y))
			rotate(chk(x)^chk(y)?x:y);
		rotate(x);
	}
}
void access(int x){
	for (int y=0;x;x=fa[y=x])
		splay(x),ch[x][1]=y,pushup(x);
}
void makeroot(int x){access(x);splay(x);setr(x);}
int findroot(int x){
	access(x);splay(x);pushdown(x);
	while (ch[x][0])pushdown(x=ch[x][0]);
	return splay(x),x;
}
void link(int x,int y){
	makeroot(x);
	if (findroot(y)!=x)
		fa[x]=y;
}
void split(int x,int y){makeroot(x);access(y);splay(y);}
void cut(int x,int y){
	split(x,y);
	if (ch[y][0]==x&&!ch[x][1])
		ch[y][0]=fa[x]=0,pushup(y);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)scanf("%d",&val[i]);
	for (int i=1;i<=m;i++){
		int opt,x,y;
		scanf("%d%d%d",&opt,&x,&y);
		if (opt==0) split(x,y),printf("%d\n",sx[y]);
		else if (opt==1) link(x,y);
		else if (opt==2) cut(x,y);
		else if (opt==3) val[x]=y,splay(x);

	}
	return 0;
}
