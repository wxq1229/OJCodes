#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<(b);++i)
#define per(i,a,b) for (int i=(a)-1;i>=(b);--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;
namespace FakeIO {
	const int SZ=100010;
	char buf[SZ],*p1=buf,*p2=buf;
	inline char nc() {return p1==p2&&(p2=(p1=buf)+fread(buf,1,SZ,stdin),p1==p2)?EOF:*p1++;}
	inline int gi() {
		char ch=nc(); int x=0,f=1;
		while(!isdigit(ch))f=ch=='-'?-f:f,ch=nc();
		while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=nc();
		return x*f;
	}
}
using FakeIO::gi;

const int N=1e6+10;

inline ll s1(int l,int r) {return 1ll*(r-l+1)*(l+r)/2;}

struct Segtree {
	int lc[N*23],rc[N*23],siz[N*23],cnt;
	ll sum[N*23];

	void ins(int pre,int &x,int l,int r,int p) {
		x=++cnt,siz[x]=siz[pre]+1,sum[x]=sum[pre]+p;
		lc[x]=lc[pre],rc[x]=rc[pre];
		if(l==r) return; int mid=(l+r)>>1;
		if(p<=mid) ins(lc[pre],lc[x],l,mid,p);
		else ins(rc[pre],rc[x],mid+1,r,p);
	}

	ll qry(int x,int y,int l,int r,int ql,int qr) {
		ll sn=sum[y]-sum[x];
		int mid=(l+r)>>1,ss=siz[lc[y]]-siz[lc[x]];
		if(sn==0||l>r||ql>qr) return 0;
		if(r<=ql) return s1(ql,qr)-sn;
		if(qr<=l) return sn-s1(ql,qr);
		return qry(lc[x],lc[y],l,mid,ql,ql+ss-1)
			+qry(rc[x],rc[y],mid+1,r,ql+ss,qr);
	}

	void build(int &x,int l,int r) {
		x=++cnt,siz[x]=sum[x]=lc[x]=rc[x]=0;
		if(l==r) return; int mid=(l+r)>>1;
		build(lc[x],l,mid),build(rc[x],mid+1,r);
	}
}T;
int rt[N],a[N],n,m;

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	n=gi(),m=gi();
	int mx=0;
	rep(i,1,n+1) a[i]=gi(),mx=max(mx,a[i]);
	T.build(rt[0],1,mx);
	rep(i,1,n+1) T.ins(rt[i-1],rt[i],1,mx,a[i]);
	while(m--) {
		int x=gi(),y=gi(),k=gi();
		printf("%lld\n",T.qry(rt[x-1],rt[y],1,mx,k,k+y-x));
	}
	return 0;
}