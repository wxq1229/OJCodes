#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef double db;
const int MAXN=200010;
int n;
struct point{
	db x,y;
}s[MAXN];
db dist(int a,int b){
	return (s[a].x-s[b].x)*(s[a].x-s[b].x)+(s[a].y-s[b].y)*(s[a].y-s[b].y);
}
db U[MAXN],D[MAXN],L[MAXN],R[MAXN];
int d[MAXN],lc[MAXN],rc[MAXN];
int cmp1(point a,point b){return a.x<b.x;}
int cmp2(point a,point b){return a.y<b.y;}
void pushup(int x){
	L[x]=R[x]=s[x].x,U[x]=D[x]=s[x].y;
	if (lc[x]){
		L[x]=min(L[x],L[lc[x]]),R[x]=max(R[x],R[lc[x]]);
		D[x]=min(D[x],D[lc[x]]),U[x]=max(U[x],U[lc[x]]);
	}
	if (rc[x]){
		L[x]=min(L[x],L[rc[x]]),R[x]=max(R[x],R[rc[x]]);
		D[x]=min(D[x],D[rc[x]]),U[x]=max(U[x],U[rc[x]]);
	}
}
int build(int l,int r){
	if (l>r) return 0;
	int mid=(l+r)>>1;
	db midx=0,midy=0;
	rep (i,l,r) midx+=s[i].x,midy+=s[i].y;
	midx/=(r-l+1),midy/=(r-l+1);
	if (midx>=midy)
		d[mid]=1,nth_element(s+l,s+mid,s+r+1,cmp1);
	else d[mid]=2,nth_element(s+l,s+mid,s+r+1,cmp2);
	lc[mid]=build(l,mid-1),rc[mid]=build(mid+1,r);
	return pushup(mid),mid;
}
db f(int a,int b){
	db res=0;
	if (s[a].x<L[b])res+=(L[b]-s[a].x)*(L[b]-s[a].x);
	if (s[a].y<D[b])res+=(D[b]-s[a].y)*(D[b]-s[a].y);
	if (R[b]<s[a].x)res+=(s[a].x-R[b])*(s[a].x-R[b]);
	if (U[b]<s[a].y)res+=(s[a].y-U[b])*(s[a].y-U[b]);
	return res;
}
db ans=2e18;
void query(int l,int r,int x){
	if (l>r) return;
	int mid=(l+r)>>1;
	if (mid!=x)ans=min(ans,dist(mid,x));
	if (l==r)return;
	db dl=f(x,lc[mid]),dr=f(x,rc[mid]);
	if (dl<ans&&dr<ans){
		if (dl<dr){
			query(l,mid-1,x);
			if (dr<ans) query(mid+1,r,x);
		}else{
			query(mid+1,r,x);
			if (dl<ans) query(l,mid-1,x);
		}
	}else{
		if (dl<ans)query(l,mid-1,x);
		else if (dr<ans) query(mid+1,r,x);
	}
}
int main(){
	scanf("%d",&n);
	rep (i,1,n)scanf("%lf%lf",&s[i].x,&s[i].y);
	build(1,n);
	rep (i,1,n)query(1,n,i);
	printf("%.4f\n",sqrt(ans));
	return 0;
}
/*
3
1 1
1 2
2 2
*/

