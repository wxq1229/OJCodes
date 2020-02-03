#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
inline char nxtch(){
	char ch=getchar();while(isspace(ch))ch=getchar();
	return ch;
}
const int N=233333*3;
int n,m,A[N];
void add(int k1,int v){
	for (;k1<=n;k1+=k1&(-k1))A[k1]+=v;
}
int qry(int k1){
	int ret=0;
	for (;k1;k1-=k1&(-k1))ret+=A[k1];
	return ret;
}
struct Query{
	int x,y,v,k1,flg,id;
}q[N],q1[N],q2[N];
int ans[N];
void solve(int l,int r,int ql,int qr){
	if(ql>qr||l>r)return;
//	cout<<l<<" "<<r<<" "<<ql<<" "<<qr<<endl;
	if(l==r){
		rep(i,ql,qr)ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	rep(i,ql,qr){
		if(q[i].flg==0){
			if(q[i].v<=mid){
				add(q[i].x,q[i].k1);
				q1[++cnt1]=q[i];
			}
			else q2[++cnt2]=q[i];
		}else{
			int tmp=qry(q[i].y)-qry(q[i].x-1);
			if(q[i].k1<=tmp)q1[++cnt1]=q[i];
			else{q[i].k1-=tmp;q2[++cnt2]=q[i];}
		}
	}
	rep(i,1,cnt1)if(q1[i].flg==0)add(q1[i].x,-q1[i].k1);
	rep(i,1,cnt1)q[ql+i-1]=q1[i];
	rep(i,1,cnt2)q[ql+cnt1+i-1]=q2[i];
	solve(l,mid,ql,ql+cnt1-1);
	solve(mid+1,r,ql+cnt1,qr);
}
int a[N];
int main(){
	scanf("%d%d",&n,&m);
	int tot=0,qcnt=0;
	rep(i,1,n){
		scanf("%d",&a[i]);
		q[++tot]=(Query){i,0,a[i],1,0,0};
	}
	rep(i,1,m){
		char ch=nxtch();
		if(ch=='Q'){
			int l,r,k;scanf("%d%d%d",&l,&r,&k);
			q[++tot]=(Query){l,r,0,k,1,++qcnt};
		}else{
			int x,v;scanf("%d%d",&x,&v);
			q[++tot]=(Query){x,0,a[x],-1,0,0};
			q[++tot]=(Query){x,0,a[x]=v,1,0,0};
		}
	}
	solve(-1e9,1e9,1,tot);
	rep(i,1,qcnt)printf("%d\n",ans[i]);
	return 0;
}
