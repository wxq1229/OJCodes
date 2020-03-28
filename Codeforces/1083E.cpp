#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;++i)
#define per(i,a,n) for (int i=n-1;i>=a;--i)
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

const int N=1e6+10;
ll f[N];
int n;
struct node {
	ll x,y,w;
	bool operator<(node o)const {return x<o.x;}
	inline void debug() {
		cout<<x<<" "<<y<<" "<<w<<endl;
	}
}a[N];

#define X(i) (a[i].x)
#define Y(i) (f[i])
inline db slope(int i,int j) {
	return 1.0*(Y(j)-Y(i))/(X(j)-X(i));
}
int q[N];

int get(int ql,int qr,int k) {
	int l=ql,r=qr-1,ans=-1;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (slope(q[mid],q[mid+1])>k) l=mid+1;
		else r=mid-1,ans=mid;
	}
	return ans==-1?qr:ans;
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%lld%lld%lld",&a[i].x,&a[i].y,&a[i].w);
	sort(a+1,a+n+1);
	// rep(i,1,n+1) a[i].debug();
	int l=1,r=1; q[1]=0;
	ll ans=-1e18;
	rep(i,1,n+1) {
		int j=q[get(l,r,a[i].y)];
		// cout<<j<<"--->"<<i<<endl;
		f[i]=f[j]+a[i].x*a[i].y-a[i].y*a[j].x-a[i].w;
		ans=max(ans,f[i]);
		while (l<r&&slope(q[r-1],i)>=slope(q[r-1],q[r])) --r;
		q[++r]=i;
	}
	// rep(i,1,n+1) cout<<f[i]<<" "; cout<<endl;
	printf("%lld\n",ans);
	return 0;
}