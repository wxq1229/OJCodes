#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
const int N=200010;
int A[N*2],n,m;
inline int lowbit(int x){return x&-x;}
inline void add(int k1,int v){
	for (;k1<=n;k1+=lowbit(k1))A[k1]+=v;
}
inline int qry(int k1){
	int ret=0;
	for (;k1;k1-=lowbit(k1))ret+=A[k1];
	return ret;
}
struct Query{
	int x,y,k1,flg,id;
}q[N*2],lq[N*2],rq[N*2];
int ans[N];
void solve(int l,int r,int ql,int qr){
	if (ql>qr||l>r)return;
	if (l==r){	
		rep(i,ql,qr)if (q[i].flg)ans[q[i].id]=l;
		return;
	}
	int cnt1=0,cnt2=0,mid=(l+r)>>1;
	rep (i,ql,qr){
		if (q[i].flg==0){
			if (q[i].k1<=mid){
				add(q[i].x,1);
				lq[++cnt1]=q[i];
			}
			else rq[++cnt2]=q[i];
		}else if (q[i].flg){
			int tmp=qry(q[i].y)-qry(q[i].x-1);
			if (tmp>=q[i].k1)lq[++cnt1]=q[i];
			else{
				q[i].k1-=tmp;
				rq[++cnt2]=q[i];
			}
		}
	}
	rep (i,1,cnt1)q[ql+i-1]=lq[i];
	rep (i,1,cnt2)q[ql+cnt1+i-1]=rq[i];
	rep (i,1,cnt1)if (lq[i].flg==0)add(lq[i].x,-1);
	solve(l,mid,ql,ql+cnt1-1);
	solve(mid+1,r,ql+cnt1,qr);
}
int main(){
	int tot=0;scanf("%d%d",&n,&m);
	rep (i,1,n){
		int x;scanf("%d",&x);
		q[++tot]=(Query){i,0,x,0,0};
	}
	rep (i,1,m){
		int l,r,k;scanf("%d%d%d",&l,&r,&k);
		q[++tot]=(Query){l,r,k,1,i};
	}
	solve(-1e9,1e9,1,tot);
	rep (i,1,m)printf("%d\n",ans[i]);
	return 0;
}
