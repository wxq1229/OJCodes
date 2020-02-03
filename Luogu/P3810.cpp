#include <bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
const int N=200010;
struct node{
	int a,b,c,w,ans;
	void print(){printf("(%d,%d,%d): %d\n",a,b,c,w);}
	bool operator != (const node& k1)const{return a!=k1.a||b!=k1.b||c!=k1.c;}
}a[N],b[N];
int cmp1(node k1,node k2){
	return k1.a<k2.a||(k1.a==k2.a&&(k1.b<k2.b||(k1.b==k2.b&&k1.c<k2.c)));
}
int cmp2(node k1,node k2){
	return k1.b<k2.b||(k1.b==k2.b&&k1.c<k2.c);
}
namespace BIT{
	int n,bit[N];
	void init(int sz=0){n=sz;}
	inline int lowbit(int x){return x&-x;}
	void add(int x,int v){for (;x<=n;x+=lowbit(x))bit[x]+=v;}
	int sum(int x){int res=0;for (;x;x-=lowbit(x))res+=bit[x];return res;}
}
int ans[N];
void cdq(int l,int r){
	if (l==r)return;
	int mid=(l+r)>>1;
	cdq(l,mid);cdq(mid+1,r);
	sort(a+l,a+mid+1,cmp2);
	sort(a+mid+1,a+r+1,cmp2);
	int i,j;
	for (i=l,j=mid+1;j<=r;j++){
		while (a[i].b<=a[j].b&&i<=mid)
			BIT::add(a[i].c,a[i].w),i++;
		a[j].ans+=BIT::sum(a[j].c);
	}
	for (j=l;j<i;j++){ // (*) if all of right is in front of left
		debug("%d %d\n",a[j].c,a[j].w);
		BIT::add(a[j].c,-a[j].w);
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	BIT::init(m);
	for (int i=1;i<=n;i++)
		scanf("%d%d%d",&b[i].a,&b[i].b,&b[i].c),b[i].ans=0;
	sort(b+1,b+n+1,cmp1);
	int nn=0;
	for (int tot=0,i=1;i<=n;i++){
		tot++;
		if (b[i]!=b[i+1])
			a[++nn]=b[i],a[nn].w=tot,tot=0;
	}
	cdq(1,nn);
	for (int i=1;i<=nn;i++)
		ans[a[i].w-1+a[i].ans]+=a[i].w;
	for (int i=0;i<n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
/*
10 3
3 3 3
2 3 3
2 3 1
3 1 1
3 1 2
1 3 1
1 1 2
1 2 2
1 3 2
1 2 1
*/
