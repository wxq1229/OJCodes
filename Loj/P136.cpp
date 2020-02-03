#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
const int N=100010;
int val[N],mx[N],fa[N],rev[N],ch[N][2];
inline void pushup(int x){
	int l=ch[x][0],r=ch[x][1];
	mx[x]=max(val[x],max(mx[l],mx[r]));
}
inline void setr(int x){rev[x]^=1;swap(ch[x][1],ch[x][0]);}
void pushdown(int x){
	if (rev[x]){
		setr(ch[x][0]);
		setr(ch[x][1]);
		rev[x]=0;
	}
}
inline int isroot(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
inline int chk(int x){return ch[fa[x]][1]==x;}
void pushall(int x){
	if (!isroot(x))pushall(fa[x]);
	pushdown(x);
}
void rotate(int x){
	int y=fa[x],z=fa[y],k=chk(x),k1=chk(y),w=ch[x][k^1];
	ch[y][k]=w; if (w)fa[w]=y;
	if (!isroot(y))ch[z][k1]=x; fa[x]=z;
	ch[x][k^1]=y; fa[y]=x;
	pushup(y),pushup(x);
}
void splay(int x){
	pushall(x);
	while (!isroot(x)){
		int y=fa[x];
		if (!isroot(y))rotate(chk(x)^chk(y)?x:y);
		rotate(x);
	}
}
void access(int x){
	for (int y=0;x;x=fa[y=x])
		splay(x),ch[x][1]=y,pushup(x);

}
void makeroot(int x){access(x);splay(x);setr(x);}
void link(int x,int y){
	makeroot(x);
	fa[x]=y;
}
void split(int x,int y){makeroot(x);access(y);splay(y);}
struct edge{
	int u,v,w;
	bool operator < (const edge& k1)const{return w<k1.w;}
}e[N<<1];
int pa[N];
int findpa(int x){return x==pa[x]?x:pa[x]=findpa(pa[x]);}
int main(){
	int n,m,Q;
	scanf("%d%d%d",&n,&m,&Q);
	rep (i,1,m)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	sort(e+1,e+m+1);
	rep (i,1,n)pa[i]=i;
	rep (i,1,m)val[i+n]=mx[i+n]=e[i].w;
	int cnt=1;
	rep (i,1,m){
		int x=findpa(e[i].u),y=findpa(e[i].v);
		if (x==y)continue;
		cnt++;pa[y]=x;
		link(e[i].u,i+n);link(i+n,e[i].v);
	}
	while (Q--){
		int x,y;scanf("%d%d",&x,&y);
		if (findpa(x)!=findpa(y)){puts("-1");continue;}
		split(x,y);
		printf("%d\n",mx[y]);
	}
	return 0;
}










