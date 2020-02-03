#include <bits/stdc++.h>
using namespace std;
#define debug(...) fprintf(stderr,__VA_ARGS__)
typedef long long ll;
const int MAXN=200010;
const ll INF=2e18;
struct seg{
	int l,r;
	ll add,sum;
}t[MAXN<<2];
void pushup(int x){
	t[x].sum=t[x<<1].sum+t[x<<1|1].sum;
}
void pushdown(int x){
	if (!t[x].add) return;
	int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
	t[x<<1].add+=t[x].add;
	t[x<<1|1].add+=t[x].add;
	t[x<<1].sum+=t[x].add*(mid-l+1);
	t[x<<1|1].sum+=t[x].add*(r-mid);
	t[x].add=0;
}
void build(int x,int l,int r){
	t[x]=(seg){l,r,0,0};
	if (l==r)
		return;
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build(x<<1|1,mid+1,r);
	pushup(x);
}
void update(int x,int ql,int qr,ll v){
	int l=t[x].l,r=t[x].r;
	if (ql<=l&&r<=qr){
		t[x].add+=v;
		t[x].sum+=v*(r-l+1);
		return;
	}
	pushdown(x);
	int mid=(l+r)>>1;
	if (ql<=mid) update(x<<1,ql,qr,v);
	if (mid<qr) update(x<<1|1,ql,qr,v);
	pushup(x);
}
ll query(int x,int ql,int qr){
	int l=t[x].l,r=t[x].r;
	if (ql<=l&&r<=qr) return t[x].sum;
	pushdown(x);
	int mid=(l+r)>>1;ll res=0;
	if (ql<=mid) res+=query(x<<1,ql,qr);
	if (mid<qr) res+=query(x<<1|1,ql,qr);
	return res;
}
ll ans[MAXN];
int n,m;
struct event{
	int opt,x,y;ll v;int id;
	void print(){
		debug("%d %d %d %lld\n",opt,x,y,v);
	}
}q[MAXN],q1[MAXN],q2[MAXN];
void solve(ll l,ll r,int ql,int qr){
	if (ql>qr||l>r) return;
//	cerr<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
//	debug("for range[%lld,%lld]:\n",l,r);
//	for (int i=ql;i<=qr;i++)
//		q[i].print();
//	debug("\n");
//	t[1].tag=1;
	if (l==r){
		for (int i=ql;i<=qr;i++)
			if (q[i].opt==2) ans[q[i].id]=l;
		return;
	}
	ll mid=(l+r)>>1;
	int cnt1=0,cnt2=0;
	for (int i=ql;i<=qr;i++){
		if (q[i].opt==1){
			if (q[i].v>mid){
				update(1,q[i].x,q[i].y,1);
				q1[++cnt1]=q[i];
			}else
				q2[++cnt2]=q[i];
		}else{
			ll tmp=query(1,q[i].x,q[i].y);
			if (tmp>=q[i].v)
				q1[++cnt1]=q[i];
			else{
				q[i].v-=tmp;
				q2[++cnt2]=q[i];
			}
		}
	}
	for (int i=1;i<=cnt1;i++)
		if (q1[i].opt==1&&q1[i].v>mid) update(1,q1[i].x,q1[i].y,-1);
//	for (int i=1;i<=n;i++)assert(query(1,i,i)==0);
	for (int i=ql;i<ql+cnt1;i++)
		q[i]=q1[i-ql+1];
	for (int i=ql+cnt1;i<=qr;i++)
		q[i]=q2[i-ql-cnt1+1];
	solve(mid+1,r,ql,ql+cnt1-1);
	solve(l,mid,ql+cnt1,qr);
}
int main(){
	scanf("%d%d",&n,&m);
	build(1,1,n);
	int tot=0;
	for (int i=1;i<=m;i++){
		int opt,a,b;ll c;
		scanf("%d%d%d%lld",&opt,&a,&b,&c);
		q[i]=(event){opt,a,b,c,opt==2?++tot:0};
	}
	solve(-n,n,1,m);
	for (int i=1;i<=tot;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
/*
2 5
1 1 2 1
1 1 2 2
2 1 1 2
2 1 1 1
2 1 2 3
*/

