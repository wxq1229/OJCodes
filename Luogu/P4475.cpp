#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=5e5+10;
struct point{
	int x,y,val;
}p[MAXN];
int cmptype;
bool cmp(point k1,point k2){
	if (cmptype==0) return k1.x<k2.x;
	else return k1.y<k2.y;
}
struct node{
	point p,lp,rp;
	int lc,rc;
	ll sum,val;
}t[MAXN];
int cnt=0;
void pushup(int x){
	t[x].sum=t[t[x].lc].sum+t[t[x].rc].sum+t[x].val;
	t[x].lp=t[x].rp=t[x].p;
	if (t[x].lc){
		t[x].lp.x=min(t[x].lp.x,t[t[x].lc].lp.x);
		t[x].lp.y=min(t[x].lp.y,t[t[x].lc].lp.y);
		t[x].rp.x=max(t[x].rp.x,t[t[x].lc].rp.x);
		t[x].rp.y=max(t[x].rp.y,t[t[x].lc].rp.y);
	}
	if (t[x].rc){
		t[x].lp.x=min(t[x].lp.x,t[t[x].rc].lp.x);
		t[x].lp.y=min(t[x].lp.y,t[t[x].rc].lp.y);
		t[x].rp.x=max(t[x].rp.x,t[t[x].rc].rp.x);
		t[x].rp.y=max(t[x].rp.y,t[t[x].rc].rp.y);
	}
}
void build(int& x,int l,int r,int type){
	if (l>r) return (void)(x=0);
	int mid=(l+r)>>1;
	cmptype=type;
	nth_element(p+l,p+mid,p+r+1,cmp);
	t[x=++cnt].p=p[mid];
	t[x].sum=t[x].val=p[mid].val;
	build(t[x].lc,l,mid-1,type^1);
	build(t[x].rc,mid+1,r,type^1);
	pushup(x);
}
ll a,b,c;
int chk(ll x,ll y){return a*x+b*y<c;}
ll query(int x){
	if (!x) return 0;
	int tmp=chk(t[x].lp.x,t[x].lp.y)+chk(t[x].lp.x,t[x].rp.y)+
			chk(t[x].rp.x,t[x].lp.y)+chk(t[x].rp.x,t[x].rp.y);
	if (tmp==4) return t[x].sum;
	if (!tmp) return 0;
	ll ans=0;
	if (chk(t[x].p.x,t[x].p.y))ans=t[x].val;
	return ans+query(t[x].lc)+query(t[x].rc);
}
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d",&p[i].x,&p[i].y,&p[i].val);
	int root=0;build(root,1,n,0);
	for (int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&a,&b,&c);
		printf("%lld\n",query(root));
	}
	return 0;
}










