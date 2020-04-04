#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=1e5+10;

struct node {
	int l,r;
	int mx; ll sum;
}t[N<<2];

inline void pushup(int x) {
	int lc=x<<1,rc=x<<1|1;
	t[x].mx=max(t[lc].mx,t[rc].mx);
	t[x].sum=t[lc].sum+t[rc].sum;
}

void upd(int x,int ql,int qr,int mod) {
	if (t[x].mx<mod) return;
	int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
	if (l==r) {t[x].mx%=mod,t[x].sum%=mod;return;}
	if (ql<=mid) upd(x<<1,ql,qr,mod);
	if (mid<qr) upd(x<<1|1,ql,qr,mod);
	pushup(x);
}

ll qry(int x,int ql,int qr) {
	int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
	if (ql<=l&&r<=qr) return t[x].sum;
	ll ans=0;
	if (ql<=mid) ans+=qry(x<<1,ql,qr);
	if (mid<qr) ans+=qry(x<<1|1,ql,qr);
	return ans;
}

void mdf(int x,int p,int v) {
	int l=t[x].l,r=t[x].r,mid=(l+r)>>1;
	if (l==r) {t[x].mx=t[x].sum=v;return;}
	if (p<=mid) mdf(x<<1,p,v);
	else mdf(x<<1|1,p,v);
	pushup(x);
}

int a[N],n,m;
void build(int x,int l,int r) {
	t[x].l=l,t[x].r=r;
	if (l==r) {t[x].sum=t[x].mx=a[l];return;}
	int mid=(l+r)>>1;
	build(x<<1,l,mid),build(x<<1|1,mid+1,r);
	pushup(x);
}

int main() {
	scanf("%d%d",&n,&m);
	rep(i,1,n+1) scanf("%d",&a[i]);
	build(1,1,n);
	while (m--) {
		int opt,u,v,w;
		scanf("%d%d%d",&opt,&u,&v);
		if (opt==1) printf("%lld\n",qry(1,u,v));
		else if (opt==2) scanf("%d",&w),upd(1,u,v,w);
		else mdf(1,u,v);
	}
	return 0;
}