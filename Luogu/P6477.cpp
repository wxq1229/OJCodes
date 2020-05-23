#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10,MOD=1e9+7;
int arr[N];
struct node
{
	int l,r,add; ll s[3];
	void clr() {s[0]=s[1]=s[2]=add=l=r=0;}
}t[N<<2];
template<typename T> void updmod(T& x) {while(x>=MOD) x-=MOD;}
void pushup(int x)
{
	int lc=x<<1,rc=x<<1|1;
	for(int i=1;i<=2;i++) updmod(t[x].s[i]=t[lc].s[i]+t[rc].s[i]);
}
void padd(int x,ll v)
{
	int l=t[x].l,r=t[x].r;
	updmod(t[x].add+=v);
	updmod(t[x].s[2]+=2ll*v*t[x].s[1]%MOD+1ll*v*v%MOD*(r-l+1)%MOD);
	updmod(t[x].s[1]+=1ll*v*(r-l+1)%MOD);
}
void pushdown(int x)
{
	if(t[x].add==0) return;
	padd(x<<1,t[x].add),padd(x<<1|1,t[x].add);
	t[x].add=0;
}
void build(int x,int l,int r)
{
	t[x].clr(); t[x].l=l,t[x].r=r;
	if(l==r)
	{
		t[x].s[1]=arr[l];
		t[x].s[2]=1ll*arr[l]*arr[l]%MOD;
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	pushup(x);
}
void upd(int x,int ql,int qr,int v)
{
	if(ql>qr) return;
	int l=t[x].l,r=t[x].r;
	if(ql<=l&&r<=qr) {padd(x,v);return;}
	int mid=(l+r)>>1; pushdown(x);
	if(ql<=mid) upd(x<<1,ql,qr,v);
	if(mid<qr) upd(x<<1|1,ql,qr,v);
	pushup(x);
}
int qry(int x,int ql,int qr,int k=2)
{
	if(ql>qr) return 0;
	int l=t[x].l,r=t[x].r;
	if(ql<=l&&r<=qr) return t[x].s[k];
	pushdown(x); int mid=(l+r)>>1,ans=0;
	if(ql<=mid) updmod(ans+=qry(x<<1,ql,qr,k));
	if(mid<qr) updmod(ans+=qry(x<<1|1,ql,qr,k));
	return ans;
}
namespace disc
{
	int vl[N],tot;
	void init(int *a,int n)
	{
		for(int i=1;i<=n;i++) vl[i]=a[i];
		sort(vl+1,vl+n+1);
		tot=unique(vl+1,vl+n+1)-vl-1;
	}
	int id(int v) {return lower_bound(vl+1,vl+tot+1,v)-vl-1;}
}
using disc::id;
int n,a[N],lst[N],r1[N],l1[N];
int main()
{
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	disc::init(a,n);
	for(int i=1;i<=n;i++) a[i]=id(a[i]);
	for(int i=n;i>=1;i--)
		r1[i]=lst[a[i]],lst[a[i]]=i;
	memset(lst,0,sizeof(lst));
	for(int i=1;i<=n;i++)
	{
		arr[i]=arr[i-1]+(!lst[a[i]]);
		lst[a[i]]=i;
	}
	build(1,1,n);
	int ans=t[1].s[2];
//	for(int i=1;i<=n;i++) printf("%d%c",qry(1,i,i)," \n"[i==n]);
	for(int i=1;i<n;i++)
	{
		int r=r1[i]==0?n:r1[i]-1;
		upd(1,i,r,MOD-1),updmod(ans+=t[1].s[2]);
//		printf("%d: \n",t[1].s[2]);
//		for(int j=1;j<=n;j++) printf("%d%c",qry(1,j,j)," \n"[j==n]);
	}
	printf("%d\n",ans);
	return 0;
}
/*
4
2 1 3 2
*/
