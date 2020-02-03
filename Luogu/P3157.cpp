#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=200010;
namespace BIT{
	ll bit[N];int n;
	inline void init(int sz=0){n=sz;}
	inline int lowbit(int x){return x&-x;}
	void add(int x,int v){for (;x<=n;x+=lowbit(x))bit[x]+=v;}
	int sum(int x){int res=0;for (;x;x-=lowbit(x))res+=bit[x];return res;}
}
struct node{
	int t,p,v,w,id;
}a[N];
int cmp(node k1,node k2){return k1.p<k2.p||(k1.p==k2.p&&k1.v<k2.v);}
int pos[N],n,m,tot;
ll ans[N];
void cdq(int l,int r){
	if (l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp);
	sort(a+mid+1,a+r+1,cmp);
	int i,j;
	for (i=l,j=mid+1;j<=r;j++){
		while (a[i].p<=a[j].p&&i<=mid)BIT::add(a[i].v,a[i].w),i++;
		ans[a[j].id]+=a[j].w*(BIT::sum(n)-BIT::sum(a[j].v));
	}
	for (j=l;j<i;j++)BIT::add(a[j].v,-a[j].w);
	for (j=r,i=mid;j>mid;j--){
		while (a[i].p>=a[j].p&&i>=l)BIT::add(a[i].v,a[i].w),i--;
		ans[a[j].id]+=a[j].w*BIT::sum(a[j].v-1);
	}
	for (j=mid;j>i;j--)BIT::add(a[j].v,-a[j].w);
}
int main(){
	scanf("%d%d",&n,&m);
	BIT::init(n);
	for (int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		a[++tot]=(node){tot,pos[x]=i,x,1,0};
	}
	for (int i=1;i<=m;i++){
		int x;scanf("%d",&x);
		a[++tot]=(node){tot,pos[x],x,-1,i};
	}
	cdq(1,tot);
	for (int i=1;i<=m;i++) ans[i]+=ans[i-1];
	for (int i=0;i<m;i++)printf("%lld\n",ans[i]);
	return 0;
}
