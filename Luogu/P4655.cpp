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

const int N=2e5+10;
const ll INF=1e18;
int n;
ll s[N],h[N],f[N];

inline ll sqr(ll x) {return x*x;}
inline ll X(int i) {return h[i];}
inline ll Y(int i) {return f[i]-s[i]+sqr(h[i]);}
inline db slope(int i,int j) {
	if (X(i)==X(j)) return Y(i)>Y(j)?INF:-INF;
	else return 1.0*(Y(i)-Y(j))/(X(i)-X(j));
}

int p[N],q[N];
void cdq(int l,int r) {
	if (l==r) {return;}
	int mid=(l+r)>>1,t1=l-1,t2=mid;
	static int tmp[N];
	rep(i,l,r+1) {
		if (p[i]<=mid) tmp[++t1]=p[i];
		else tmp[++t2]=p[i];
	}
	rep(i,l,r+1) p[i]=tmp[i];
	cdq(l,mid);
	t1=1,t2=0;
	rep(i,l,mid+1) {
		while (t1<t2&&slope(p[i],q[t2-1])<=slope(q[t2],q[t2-1])) --t2;
		q[++t2]=p[i];
	}
	rep(i,mid+1,r+1) {
		while (t1<t2&&2.0*h[p[i]]>=slope(q[t1+1],q[t1])) ++t1;
		int k1=p[i],k2=q[t1];
		// cout<<k1<<" <- "<<k2<<endl;
		f[k1]=min(f[k1],f[k2]+s[k1-1]-s[k2]+sqr(h[k1]-h[k2]));
	}
	cdq(mid+1,r);
	t1=l,t2=mid+1;
	rep(i,l,r+1) {
		if (t2>r||(t1<=mid&&h[p[t1]]<h[p[t2]])) tmp[i]=p[t1++];
		else tmp[i]=p[t2++];
	}
	rep(i,l,r+1) p[i]=tmp[i];
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n);
	rep(i,1,n+1) scanf("%lld",&h[i]),p[i]=i,f[i]=INF;
	f[1]=0;
	rep(i,1,n+1) {
		ll w; scanf("%lld",&w);
		s[i]=s[i-1]+w;
	}
	sort(p+1,p+n+1,[](int i,int j){return h[i]<h[j];});
	cdq(1,n);
	printf("%lld\n",f[n]);
	return 0;
}