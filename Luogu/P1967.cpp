#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
const int MAXN=500010;
const int INF=0x3f3f3f3f;
int mn[MAXN],fa[MAXN],rev[MAXN],ch[MAXN][2],val[MAXN];
void pushup(int x){
	int l=ch[x][0],r=ch[x][1];
	mn[x]=min(val[x],min(mn[l],mn[r]));
}
void setr(int x){
	swap(ch[x][0],ch[x][1]);
	rev[x]^=1;
}
void pushdown(int x){
	if (rev[x]){
		setr(ch[x][0]);
		setr(ch[x][1]);
		rev[x]=0;
	}
}
int isroot(int x){return ch[fa[x]][1]!=x&&ch[fa[x]][0]!=x;}
int chk(int x){return ch[fa[x]][1]==x;}
void rotate(int x){
	int y=fa[x],z=fa[y];
	int k=chk(x),k1=chk(y),w=ch[x][k^1];
	ch[y][k]=w; if (w)fa[w]=y;
	if (!isroot(y)) ch[z][k1]=x; fa[x]=z;
	ch[x][k^1]=y; fa[y]=x;
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
void split(int x,int y){makeroot(x);access(y);splay(y);}
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
struct edge{
	int x,y,w;
	bool operator < (const edge &k1) const{
		return w>k1.w;
	}
}e[MAXN];
int pa[MAXN];
int findpa(int x){
	return pa[x]==x?x:pa[x]=findpa(pa[x]);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	rep (i,0,n) val[i]=mn[i]=INF;
	rep (i,1,m){
		int x,y,w;scanf("%d%d%d",&x,&y,&w);
		e[i]=(edge){x,y,w};
	}
	sort(e+1,e+m+1);
	rep (i,1,n) pa[i]=i;
	rep (i,1,m) mn[i+n]=val[i+n]=e[i].w;
	int cnt=n;
	rep (i,1,m){
		int x=findpa(e[i].x),y=findpa(e[i].y);
		if (x==y) continue;
		cnt--,pa[y]=x;
		link(x,i+n),link(i+n,y);
		if (cnt==1) break;
	}
	int Q;scanf("%d",&Q);while (Q--){
		int x,y;scanf("%d%d",&x,&y);
		split(x,y),printf("%d\n",findpa(x)==findpa(y)?mn[y]:-1);
	}
	return 0;
}










