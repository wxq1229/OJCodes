#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
const int N=6e5+10;
typedef long long ll;
int n,m,K;
ll bit[N];
inline int lowbit(int x){return x&-x;}
void add(int x,ll v){
	for (;x<=m;x+=lowbit(x))
		bit[x]+=v;
}
ll sum(int x){
	ll res=0;
	for (;x;x-=lowbit(x))
		res+=bit[x];
	return res;
}
vector<int>pos[N];
struct event{
	int opt,x,y;ll v;int id;
}q[N],q1[N],q2[N];
int ans[N];
void solve(int l,int r,int ql,int qr){
	if (l>r||ql>qr) return;
	if (l==r){
		rep (i,ql,qr)
			if (q[i].opt==2)ans[q[i].id]=l;
		return;
	}
//	printf("%d %d:\n",l,r);
	int mid=(l+r)>>1,cnt1=0,cnt2=0;
	rep (i,ql,qr){
		if (q[i].opt==1){
			if (q[i].id<=mid){
				q1[++cnt1]=q[i];
				if (q[i].x<=q[i].y)
					add(q[i].x,q[i].v),add(q[i].y+1,-q[i].v);
				else
					add(q[i].x,q[i].v),add(1,q[i].v),add(q[i].y+1,-q[i].v);
//				printf("after add [%d,%d] %d:\n",q[i].x,q[i].y,q[i].v);
//				rep (j,1,m)printf("%lld ",sum(j));
//				puts("");
			}
			else q2[++cnt2]=q[i];
		}else{
			ll tmp=0;
			rep (j,0,pos[q[i].id].size()-1){
				int x=pos[q[i].id][j];
				tmp+=sum(x);
				if (tmp>=q[i].v)break;
			}
			if (tmp>=q[i].v)
				q1[++cnt1]=q[i];
			else
				q[i].v-=tmp,q2[++cnt2]=q[i];
		}
	}
	rep (i,1,cnt1){ 
		if (q1[i].opt==2)continue;
		if (q1[i].x<=q1[i].y)
			add(q1[i].x,-q1[i].v),add(q1[i].y+1,q1[i].v);
		else
			add(q1[i].x,-q1[i].v),add(1,-q1[i].v),add(q1[i].y+1,q1[i].v);
	}
//	puts("");
	rep (i,ql,ql+cnt1-1) q[i]=q1[i-ql+1];
	rep (i,ql+cnt1,qr) q[i]=q2[i-ql-cnt1+1];
	solve(l,mid,ql,ql+cnt1-1);
	solve(mid+1,r,ql+cnt1,qr);
}
int main(){
	scanf("%d%d",&n,&m);
	int t1=0,t2=0,tot=0;
	rep (i,1,m){
		int x;scanf("%d",&x);
		pos[x].push_back(i);
	}	
	rep (i,1,n){
		ll need;scanf("%lld",&need);
		q2[++t2]=(event){2,i,0,need,i};
	}
	scanf("%d",&K);
	rep (i,1,K){
		int l,r;ll v;
		scanf("%d%d%lld",&l,&r,&v);
		q1[++t1]=(event){1,l,r,v,i};
	}
	q1[++t1]=(event){1,1,m,(ll)1e9,K+1};
	rep (i,1,t1)q[++tot]=q1[i];
	rep (i,1,t2)q[++tot]=q2[i];
	solve(1,K+1,1,tot);
	rep (i,1,n)
		if (ans[i]==K+1) puts("NIE");
		else printf("%d\n",ans[i]);
	return 0;
}










