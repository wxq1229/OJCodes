#include <bits/stdc++.h>
using namespace std;
#define sq(x) ((x)*(x))
typedef long long ll;
const ll INF=1e18;
const int MAXN=200010;
struct point{
	ll x,y;
}p[MAXN];
ll dist(int i,int j){return sq(p[i].x-p[j].x)+sq(p[i].y-p[j].y);}
struct node{
	point lp,rp;
	int id,lc,rc;
}t[MAXN];
int cnt=0;
void pushup(int x){
	t[x].lp=t[x].rp=p[t[x].id];
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
int cmptype,pos[MAXN];
int cmp(int i,int j){
	if (cmptype==0) return p[i].x<p[j].x;
	else return p[i].y<p[j].y;
}
int build(int l,int r,int type){
	if (l>r) return 0;
	cmptype=type;
	int mid=(l+r)>>1;
	int x=++cnt;
	nth_element(pos+l,pos+mid,pos+r+1,cmp);
	t[x].id=pos[mid];
	t[x].lc=build(l,mid-1,type^1);
	t[x].rc=build(mid+1,r,type^1);
	return pushup(x),x;
}
ll exp(int i,int j){
	return max(sq(p[i].x-t[j].lp.x),sq(p[i].x-t[j].rp.x))+
			max(sq(p[i].y-t[j].lp.y),sq(p[i].y-t[j].rp.y));
}
struct qnode{
	ll dis;
	int id;
	bool operator < (const qnode& k1)const{
		return dis>k1.dis;
	}
};
priority_queue<qnode>q;
void query(int x,int v){
	ll d=dist(t[x].id,v);
	if (d>q.top().dis||(d==q.top().dis&&t[x].id<q.top().id))
		q.pop(),q.push((qnode){d,t[x].id});
	ll dl=t[x].lc?exp(v,t[x].lc):-INF,dr=t[x].rc?exp(v,t[x].rc):-INF;
	if (dl>dr){
		if (dl>=q.top().dis)query(t[x].lc,v);
		if (dr>=q.top().dis)query(t[x].rc,v);
	}else{
		if (dr>=q.top().dis)query(t[x].rc,v);
		if (dl>=q.top().dis)query(t[x].lc,v);
	}
}
int main(){
	int n,m;scanf("%d",&n);
	for (int i=1;i<=n;i++){
		pos[i]=i;
		scanf("%lld%lld",&p[i].x,&p[i].y);
	}
	int root=build(1,n,0);
	scanf("%d",&m);
	for (int i=1;i<=m;i++){
		ll x,y;scanf("%lld%lld",&x,&y);
		p[i+n]=(point){x,y};
		while (q.size())q.pop();
		int k;scanf("%d",&k);
		for (int j=1;j<=k;j++)q.push((qnode){0,0x3f3f3f3f});
		query(root,i+n);
		printf("%d\n",q.top().id);
	}
	return 0;
}











