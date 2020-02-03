#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef double db;
const db alpha=0.7;
const int MAXN=500010;
struct point{
	int x,y,v;
}s[MAXN];
int d[MAXN],size[MAXN],sum[MAXN];
int L[MAXN],R[MAXN],U[MAXN],D[MAXN],lc[MAXN],rc[MAXN];
void pushup(int x){
	size[x]=size[lc[x]]+size[rc[x]]+1;
	sum[x]=sum[lc[x]]+sum[rc[x]]+s[x].v;
	L[x]=R[x]=s[x].x,D[x]=U[x]=s[x].y;
	if (lc[x]){
		L[x]=min(L[x],L[lc[x]]),R[x]=max(R[x],R[lc[x]]);
		D[x]=min(D[x],D[lc[x]]),U[x]=max(U[x],U[lc[x]]);
	}
	if (rc[x]){
		L[x]=min(L[x],L[rc[x]]),R[x]=max(R[x],R[rc[x]]);
		D[x]=min(D[x],D[rc[x]]),U[x]=max(U[x],U[rc[x]]);
	}
}
int st[MAXN],top;
void dfs(int x){
	if (lc[x])dfs(lc[x]);
	st[++top]=x;
	if (rc[x])dfs(rc[x]);
}
int cmptype;
int cmp(int i,int j){
	point k1=s[i],k2=s[j];
	if (cmptype==0)return k1.x<k2.x||(k1.x==k2.x&&k1.y<k2.y);
	else return k1.y<k2.y||(k1.y==k2.y&&k1.x<k2.x);
}
int build(int l,int r,int type){
	if (l>r) return 0;
	cmptype=type;
	int mid=(l+r)>>1;
	nth_element(st+l,st+mid,st+r+1,cmp);
	int x=st[mid];
	d[x]=type;
	lc[x]=build(l,mid-1,rand()%2);
	rc[x]=build(mid+1,r,rand()%2);
	return pushup(x),x;
}
void rebuild(int& x){
	top=0,dfs(x);
	x=build(1,top,rand()%2);
}
int isbad(int x){return alpha*size[x]<=(db)max(size[lc[x]],size[rc[x]]);}
void insert(int& x,int p){
	if (!x){x=p,pushup(x);return;}
	if (d[x]==0) insert(s[p].x<=s[x].x?lc[x]:rc[x],p);
	else insert(s[p].y<=s[x].y?lc[x]:rc[x],p);
	pushup(x);
	if (isbad(x))rebuild(x);
}
int query(int x,int lx,int rx,int ly,int ry){
	if (!x || R[x]<lx||L[x]>rx||U[x]<ly||D[x]>ry) return 0;
	if (lx<=L[x]&&R[x]<=rx&&ly<=D[x]&&U[x]<=ry) return sum[x];
	int res=(lx<=s[x].x&&s[x].x<=rx&&ly<=s[x].y&&s[x].y<=ry?s[x].v:0);
	return query(lc[x],lx,rx,ly,ry)+query(rc[x],lx,rx,ly,ry)+res;
}
int main(){
	srand(time(NULL));
	int n;scanf("%d",&n);
	int opt,x,y,x1,y1,v,cnt=0,lastans=0,root=0;
	while (scanf("%d",&opt)==1){
		if (opt==3)return 0;
		if (opt==1){
			scanf("%d%d%d",&x,&y,&v);
			s[++cnt]=(point){x^lastans,y^lastans,v^lastans};
			insert(root,cnt);
//			cerr<<L[root]<<" "<<R[root]<<" "<<D[root]<<" "<<U[root]<<endl;
		}else{
			scanf("%d%d%d%d",&x,&y,&x1,&y1);
			printf("%d\n",lastans=query(root,x^lastans,x1^lastans,y^lastans,y1^lastans));
		}
	}
	return 0;
}
/*
4
1 2 3 3
2 1 1 3 3
1 1 1 1
2 1 1 0 7
3
*/

