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

const int maxn=5e6,N=maxn+10;
int mod,i2,i6;
inline int add(int x,int y) {return (x+=y)>=mod?x-mod:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+mod:x;}
inline int normal(ll x) {return x<0?x+mod:x;}
inline int fpow(int x,int y) {
    int ret=1; for(;y;y>>=1,x=1ll*x*x%mod)
        if(y&1) ret=1ll*ret*x%mod;
    return ret;
}
inline int sqr(int x) {return 1ll*x*x%mod;}
inline void initmod(int P) {
    mod=P;
    i2=fpow(2,mod-2),i6=fpow(6,mod-2);
}

inline int ss1(ll n) {n%=mod;return 1ll*n*(n+1)%mod*i2%mod;}
inline int ss2(ll n) {n%=mod;return 1ll*n*(n+1)%mod*(2*n+1)%mod*i6%mod;}
inline int s1(ll l,ll r) {return sub(ss1(r),ss1(l-1));}
inline int s2(ll l,ll r) {return sub(ss2(r),ss2(l-1));}

int p[N],pn,phi[N];
bool vis[N];

void sieve(int n) {
    phi[1]=1;
    rep(i,2,n+1) {
        if(!vis[i]) {phi[i]=i-1;p[pn++]=i;}
        for(int j=0;j<pn&&i*p[j]<=n;j++) {
            vis[i*p[j]]=1;
            if(i%p[j]==0) {phi[i*p[j]]=phi[i]*p[j];break;}
            else phi[i*p[j]]=phi[i]*phi[p[j]];
        }
    }
    rep(i,1,n+1) phi[i]=add(phi[i-1],1ll*i*i%mod*phi[i]%mod);
}

map<ll,int> fsum;
int Sf(ll n) {
    if(n<=maxn) return phi[n];
    if(fsum.count(n)) return fsum[n];
    int ans=sqr(normal(ss1(n)));
    for(ll l=2,r=0;l<=n;l=r+1) {
        r=n/(n/l);
        ans=sub(ans,1ll*s2(l,r)*Sf(n/l)%mod);
    }
    return fsum[n]=ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    int p; ll n; scanf("%d%lld",&p,&n);
    initmod(p),sieve(maxn);
    int ans=0;
    for(ll l=1,r=0;l<=n;l=r+1) {
        r=n/(n/l);
        ans=add(ans,1ll*sub(Sf(r),Sf(l-1))*sqr(ss1(n/l))%mod);
    }
    printf("%d\n",ans);
    return 0;
}