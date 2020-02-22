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

const int maxn=1e7,N=maxn+10,P=20101009;
inline int add(int x,int y) {return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+P:x;}
inline int normal(int x) {return x<0?x+P:x;}
inline int sqr(int x) {return 1ll*x*x%P;}
inline int fpow(int x,int y) {
	int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
		if(y&1) ret=1ll*ret*x%P;
	return ret;
}
const int i2=(P+1)/2,i6=fpow(6,P-2);

int mu[N],sum[N],vis[N],p[N],pn;

void init(int n) {
	mu[1]=1;
	rep(i,2,n+1) {
		if(!vis[i]) {p[pn++]=i;mu[i]=-1;}
		for(int j=0;j<pn&&p[j]*i<=n;j++) {
			vis[i*p[j]]=1;
			if(i%p[j]==0) {mu[i*p[j]]=0;break;}
			else mu[i*p[j]]=mu[i]*mu[p[j]];
		}
	}
	rep(i,1,n+1) mu[i]=normal(mu[i]);
	rep(i,1,n+1) sum[i]=add(sum[i-1],1ll*mu[i]*sqr(i)%P);
}

inline int s1(int l,int r) {return 1ll*(r-l+1)*(l+r)%P*i2%P;}
inline int ss(int l,int r) {return sub(sum[r],sum[l-1]);}

int S(int n,int m) {
	int tn=min(n,m),ans=0;
	for(int l=1,r=0;l<=tn;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		ans=add(ans,1ll*ss(l,r)*s1(1,n/l)%P*s1(1,m/l)%P);
	}
	return ans;
}

int solve(int n,int m) {
	int ans=0,tn=min(n,m);
	for(int l=1,r=0;l<=tn;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		ans=add(ans,1ll*s1(l,r)*S(n/l,m/l)%P);
	}
	return ans;
}

int main() {
	init(maxn);
	int n,m;scanf("%d%d",&n,&m);
	printf("%d\n",solve(n,m));
	return 0;
}