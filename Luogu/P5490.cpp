#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=233333;
struct scanline{
	ll x,y1,y2;int flg;
	bool operator < (scanline l1)const{return x<l1.x;}
}L[N*2];int nwL;
ll yval[N*2];int tot;
struct node{
	ll l,r,len;int vis;
}t[N*8];
void pushup(int x){
	if (t[x].vis)t[x].len=t[x].r-t[x].l;
	else t[x].len=t[x*2].len+t[x*2+1].len;
}
void build(int x,int l,int r){
	t[x].vis=0,t[x].l=yval[l],t[x].r=yval[r];
	if (l==r-1)return;
	int mid=(l+r)>>1;
	build(x*2,l,mid),build(x*2+1,mid,r);
	pushup(x);
}
void update(int x,ll ql,ll qr,int v){
	ll l=t[x].l,r=t[x].r;
	if (ql<=l&&r<=qr){
		t[x].vis+=v,pushup(x);
		return;
	}
	if (t[x*2].r>ql)update(x*2,ql,qr,v);
	if (t[x*2+1].l<qr)update(x*2+1,ql,qr,v);
	pushup(x);
}
int n;
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		ll x1,y1,x2,y2;scanf("%lld%lld%lld%lld",&x1,&y1,&x2,&y2);
		yval[++tot]=y1,yval[++tot]=y2;
		L[++nwL]=(scanline){x1,y1,y2,1},L[++nwL]=(scanline){x2,y1,y2,-1};
	}
	sort(yval+1,yval+tot+1),sort(L+1,L+nwL+1),build(1,1,tot);
	ll ans=0;update(1,L[1].y1,L[1].y2,L[1].flg);
	for (int i=2;i<=nwL;i++){
		ans+=t[1].len*(L[i].x-L[i-1].x);
		update(1,L[i].y1,L[i].y2,L[i].flg);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
2
100 100 200 200
150 150 250 255

*/









