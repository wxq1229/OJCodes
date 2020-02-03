#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1000010;
namespace BIT{
	ll bit[N],n;
	void init(int sz=0){n=sz;}
	inline int lowbit(int x){return x&-x;}
	void add(int x,ll v){for (;x<=n;x+=lowbit(x))bit[x]+=v;}
	ll sum(int x){ll res=0;for (;x;x-=lowbit(x))res+=bit[x];return res;}
}
struct node{
	int t,p,v,w,id;
	bool operator < (const node& k1)const{return p<k1.p;}
}q[N];
ll a[N],b[N];
ll ans[N];
void cdq(int l,int r){
	if (l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(q+l,q+mid+1);sort(q+mid+1,q+r+1);
	int i,j;
	for (i=l,j=mid+1;j<=r;j++){
		while (q[i].p<=q[j].p&&i<=mid)
			BIT::add(q[i].v,q[i].w),i++;
		ans[q[j].id]+=q[j].w*(BIT::sum(BIT::n)-BIT::sum(q[j].v));
	}
	for (j=l;j<i;j++)BIT::add(q[j].v,-q[j].w);
	for (i=mid,j=r;j>mid;j--){
		while (q[i].p>=q[j].p&&i>=l)
			BIT::add(q[i].v,q[i].w),i--;
		ans[q[j].id]+=q[j].w*BIT::sum(q[j].v-1);
	}
	for (j=mid;j>i;j--)BIT::add(q[j].v,-q[j].w);
}

int main(){
	int n,Q;scanf("%d%d",&n,&Q);
	for (int i=1;i<=n;i++)
		scanf("%lld",&a[i]),b[i]=a[i];
	sort(b+1,b+n+1);
	int m=unique(b+1,b+n+1)-b-1;
	BIT::init(m);
	for (int i=1;i<=n;i++) a[i]=lower_bound(b+1,b+m+1,a[i])-b;
	int tot=0;
	for (int i=1;i<=n;i++)
		q[++tot]=(node){tot,i,a[i],1,0};
	for (int i=1;i<=Q;i++){
		int x;scanf("%d",&x);
		q[++tot]=(node){tot,x,a[x],-1,i};
	}
	cdq(1,tot);
	for (int i=1;i<=Q;i++)ans[i]+=ans[i-1];
	for (int i=0;i<=Q;i++)printf("%lld ",ans[i]);
	return 0;
}
