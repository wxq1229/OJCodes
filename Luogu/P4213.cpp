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
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int maxn=2e6,N=maxn+10;
int p[N],pn;
ll mu[N],phi[N],smu[N],sphi[N];
bitset<N> vis;

inline ll s1(ll l,ll r) {return 1ll*(r-l+1)*(l+r)/2;}

void init(int n) {
    mu[1]=1,phi[1]=1;
    rep(i,2,n+1) {
        if(!vis[i]) {
            mu[i]=-1,phi[i]=i-1;
            p[pn++]=i;
        }
        for(int j=0;j<pn&&i*p[j]<=n;j++) {
            vis[i*p[j]]=1;
            if(i%p[j]==0) {
                mu[i*p[j]]=0;
                phi[i*p[j]]=phi[i]*p[j];
                break;
            }
            else mu[i*p[j]]=-mu[i],phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
    rep(i,1,n+1) smu[i]=smu[i-1]+mu[i],sphi[i]=sphi[i-1]+phi[i];
}

map<int,ll> phisum,musum;
ll Sphi(int n) {
    if(n<=maxn) return sphi[n];
    if(phisum.count(n)) return phisum[n];
    ll ans=s1(1,n);
    for(ll l=2,r=0;l<=n;l=r+1) {
        r=n/(n/l);
        ans-=Sphi(n/l)*(r-l+1);
    }
    return phisum[n]=ans;
}
ll Smu(int n) {
    if(n<=maxn) return smu[n];
    if(musum.count(n)) return musum[n];
    ll ans=1;
    for(ll l=2,r=0;l<=n;l=r+1) {
        r=n/(n/l);
        ans-=Smu(n/l)*(r-l+1);
    }
    return musum[n]=ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    init(maxn);
    int _,n; for(scanf("%d",&_);_;_--) {
        scanf("%d",&n);
        printf("%lld %lld\n",Sphi(n),Smu(n));
    }
    return 0;
}