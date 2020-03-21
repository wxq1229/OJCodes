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

const int N=533;
db f[N][N],pw[N][N],p[N],g[N];
int d[N],n,r;

void solve() {
	memset(f,0,sizeof(f));
	memset(pw,0,sizeof(pw));
	memset(p,0,sizeof(p));
	memset(g,0,sizeof(g));
	memset(d,0,sizeof(d));
	scanf("%d%d",&n,&r);
	rep(i,1,n+1) scanf("%lf%d",&p[i],&d[i]);
	rep(i,1,n+1) {
		pw[i][0]=1;
		rep(j,1,r+1) pw[i][j]=pw[i][j-1]*(1-p[i]);
	}
	f[1][0]=pw[1][r],f[1][1]=1-pw[1][r];
	g[1]=1-pw[1][r];
	rep(i,2,n+1) rep(j,0,min(i,r)+1) {
		f[i][j]=f[i-1][j]*pw[i][r-j];
		if (j) f[i][j]+=f[i-1][j-1]*(1-pw[i][r-j+1]);
	}
	rep(i,2,n+1) rep(j,0,min(i,r)+1) 
		g[i]+=f[i-1][j]*(1-pw[i][r-j]);
	db ans=0;
	rep(i,1,n+1) ans+=g[i]*d[i];
	printf("%.10f\n",ans);
}

int _;
int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	for (scanf("%d",&_);_;_--) solve();
	return 0;
}