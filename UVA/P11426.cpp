#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=(a);i<(b);i++)
#define per(i,a,b) for (int i=(a)-1;i>=(b);i--)
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

const int maxn=4e6,N=maxn+10;
ll f[N],phi[N],vis[N];
int p[N],pn;

void getphi(int n) {
	rep(i,2,n+1) {
		if(!vis[i]) {
			p[pn++]=i;
			phi[i]=i-1;
		}
		for(int j=0;j<pn&&i*p[j]<=n;j++) {
			vis[i*p[j]]=1;
			if(i%p[j]==0) {phi[i*p[j]]=phi[i]*p[j];break;}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}

void init() {
	getphi(maxn);
	rep(i,1,maxn+1) for(int j=i*2;j<=maxn;j+=i) 
		f[j]+=i*phi[j/i];
	rep(i,1,maxn+1) f[i]+=f[i-1];
}

int n;
int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	init();
	while(scanf("%d",&n)==1&&n) printf("%lld\n",f[n]);
	return 0;
}