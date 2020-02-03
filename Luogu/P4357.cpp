#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
const int MAXN=100010;
typedef long long ll;
priority_queue<ll,vector<ll>,greater<ll> >q;
struct point{
	ll x,y;
}s[MAXN];
ll sq(ll x){return x*x;}
ll dist(int a,int b){return sq(s[a].x-s[b].x)+sq(s[a].y-s[b].y);}
ll L[MAXN],R[MAXN],U[MAXN],D[MAXN];
int lc[MAXN],rc[MAXN],cmptype;
int cmp(point a,point b){
	if (cmptype==0) return a.x<b.x||(a.x==b.x&&a.y<b.y);
	else return a.y<b.y||(a.y==b.y&&a.x<b.x);
}
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
int build(int l,int r,int type){
	if (l>r) return 0;
	cmptype=type;
	int mid=(l+r)>>1;
	nth_element(s+l,s+mid,s+r+1,cmp);
	lc[mid]=build(l,mid-1,type^1);
	rc[mid]=build(mid+1,r,type^1);
	return pushup(mid),mid;
}
ll f(int a,int b){
	return max(sq(s[a].x-L[b]),sq(s[a].x-R[b]))
			+max(sq(s[a].y-U[b]),sq(s[a].y-D[b]));
}
void query(int l,int r,int x){
	if (l>r) return;
	int mid=(l+r)>>1;
	ll t=dist(x,mid);
//	cerr<<t<<endl;
	if (t>q.top())q.pop(),q.push(t);
	ll dl=f(x,lc[mid]),dr=f(x,rc[mid]);
	if (dl>q.top()&&dr>q.top()){
		if (dl>dr){
			query(l,mid-1,x);
			if (dr>q.top())query(mid+1,r,x);
		}
		else{
			query(mid+1,r,x);
			if (dl>q.top())query(l,mid-1,x);
		}
	}else{
		if (dl>q.top())query(l,mid-1,x);
		if (dr>q.top())query(mid+1,r,x);
	}
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	k*=2;
	rep (i,1,k)q.push(0);
	rep (i,1,n)scanf("%lld%lld",&s[i].x,&s[i].y);
	build(1,n,0);
	rep (i,1,n)query(1,n,i);//,cerr<<q.top()<<endl;
	printf("%lld\n",q.top());
	return 0;
}
/*
10 5
0 0
0 1
1 0
1 1
2 0
2 1
1 2
0 2
3 0
3 1
*/

