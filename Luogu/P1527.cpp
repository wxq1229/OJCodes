#include <bits/stdc++.h>
using namespace std;
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int MAXN=510;
const int MAXQ=600010;
const int INF=1e9;
namespace BIT{
	int n,m;
	int bit[MAXN][MAXN];
	inline int lowbit(int x){return x&-x;}
	void init(int R,int C){
		n=R,m=C;
		memset(bit,0,sizeof(bit));
	}
	void add(int r,int c,int v){
		for (int i=r;i<=n;i+=lowbit(i))
			for (int j=c;j<=m;j+=lowbit(j))
				bit[i][j]+=v;
	}
	int query(int r,int c){
		int res=0;
		for (int i=r;i;i-=lowbit(i))
			for (int j=c;j;j-=lowbit(j))
				res+=bit[i][j];
		return res;
	}
	int query(int x1,int y1,int x2,int y2){
		return query(x2,y2)-query(x1-1,y2)-query(x2,y1-1)+query(x1-1,y1-1);
	}
}
int n,Q,ans[MAXQ];
struct event{
	int opt,x1,y1,x2,y2,k,id;
}q[MAXQ],q1[MAXQ],q2[MAXQ];
void solve(int l,int r,int ql,int qr){
	if (l>r||ql>qr) return;
//	debug("%d %d\n",l,r);
	if (l==r){
		for (int i=ql;i<=qr;i++)
			if (q[i].opt==2)ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	for (int i=ql;i<=qr;i++){
		if (q[i].opt==1){
			if (q[i].k<=mid){
//				debug("add (%d,%d)\n",q[i].x1,q[i].y1);
				BIT::add(q[i].x1,q[i].y1,1);
				q1[++cnt1]=q[i];
			}
			else q2[++cnt2]=q[i];
		}else{
			int tmp=BIT::query(q[i].x1,q[i].y1,q[i].x2,q[i].y2);
			if (q[i].k<=tmp)
				q1[++cnt1]=q[i];
			else{
				q[i].k-=tmp;
				q2[++cnt2]=q[i];
			}
		}
	}
	for (int i=1;i<=cnt1;i++)
		if (q1[i].opt==1) BIT::add(q1[i].x1,q1[i].y1,-1);
	for (int i=ql;i<=ql+cnt1-1;i++)
		q[i]=q1[i-ql+1];
	for (int i=ql+cnt1;i<=qr;i++)
		q[i]=q2[i-ql-cnt1+1];
	solve(l,mid,ql,ql+cnt1-1);
	solve(mid+1,r,ql+cnt1,qr);
}
int main(){
	scanf("%d%d",&n,&Q);
	BIT::init(n,n);
	int tot=0;
	for (int i=1;i<=n;i++)
		for (int j=1;j<=n;j++){
			int x;scanf("%d",&x);
			q[++tot]=(event){1,i,j,0,0,x,0};
		}
	for (int i=1;i<=Q;i++){
		int x1,x2,y1,y2,k;
		scanf("%d%d%d%d%d",&x1,&y1,&x2,&y2,&k);
		q[++tot]=(event){2,x1,y1,x2,y2,k,i};
	}
	solve(0,INF,1,tot);
	for (int i=1;i<=Q;i++)
		printf("%d\n",ans[i]);
	return 0;
}
/*
2 2
2 1
3 4
1 2 1 2 1
1 1 2 2 3
*/

