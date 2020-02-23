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

const int N=1e6+10,maxn=1e6,P=1e9+7;
inline int add(int x,int y) {return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+P:x;}
inline int fpow(int x,int y) {
	int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
		if(y&1) ret=1ll*ret*x%P;
	return ret;
}
inline int normal(int x) {return x<0?x+P:x;}

int vis[N],p[N],pn,mu[N];
void getmu(int n) {
	mu[1]=1;
	rep(i,2,n+1) {
		if(!vis[i]) {mu[i]=-1;p[pn++]=i;}
		for(int j=0;j<pn&&i*p[j]<=n;j++) {
			vis[i*p[j]]=1;
			if(i%p[j]==0) {mu[i*p[j]]=0;break;}
			else mu[i*p[j]]=-mu[i];
		}
	}
}

int fib[N],f[N],ifib[N];
void init(int n) {
	getmu(n);
	fib[0]=0,fib[1]=1;
	rep(i,2,n+1) fib[i]=add(fib[i-1],fib[i-2]);	
	rep(i,0,n+1) ifib[i]=fpow(fib[i],P-2),f[i]=1;
	rep(i,1,n+1) if(mu[i]!=0) {
		for(int j=i;j<=n;j+=i)
			f[j]=1ll*f[j]*(mu[i]==-1?ifib[j/i]:fib[j/i])%P;
	}
	rep(i,1,n+1) f[i]=1ll*f[i]*f[i-1]%P; 
}

int solve(int n,int m) {
	int tn=min(n,m),ans=1;
	for(int l=1,r=0;l<=tn;l=r+1) {
		r=min(n/(n/l),m/(m/l));
		ans=1ll*ans*fpow(1ll*f[r]*fpow(f[l-1],P-2)%P,1ll*(n/l)*(m/l)%(P-1))%P;
	}
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	init(maxn);
	int n,m,_; for(scanf("%d",&_);_;_--) {
		scanf("%d%d",&n,&m);
		printf("%d\n",solve(n,m));
	}
	return 0;
}