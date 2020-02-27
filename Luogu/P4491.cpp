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

const int NN=1e7+10,N=3e5+10,P=1004535809;
inline int add(int x,int y) {return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+P:x;}
inline int normal(int x) {return x<0?x+P:x;}
inline int fpow(int x,int y) {
    int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
        if(y&1) ret=1ll*ret*x%P;
    return ret;
}
const int gn=3,ign=fpow(gn,P-2);

int fac[NN],ifac[NN],inv[NN];
inline int getC(int n,int r) {return 1ll*fac[n]*ifac[n-r]%P*ifac[r]%P;}

namespace Poly {
    int rev[N];
    inline void init(int n) {
        rep(i,0,n) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
    }

    void ntt(int *f,int n,int flg) {
        rep(i,0,n) if(rev[i]<i) swap(f[i],f[rev[i]]);
        for(int len=2,k=1;len<=n;len<<=1,k<<=1) {
            int wn=fpow(flg==1?gn:ign,(P-1)/len);
            for(int i=0;i<n;i+=len)
                for(int j=i,w=1;j<i+k;j++,w=1ll*w*wn%P) {
                    int tmp=1ll*w*f[j+k]%P;
                    f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
                }
        }
        if(flg==-1) {
            int invn=fpow(n,P-2);
            rep(i,0,n+1) f[i]=1ll*f[i]*invn%P;
        }
    }
}
using Poly::ntt;

void init(int n) {
    ifac[0]=ifac[1]=fac[0]=fac[1]=inv[1]=1;
    rep(i,2,n+1) {
        inv[i]=1ll*inv[P%i]*(P-P/i)%P;
        ifac[i]=1ll*ifac[i-1]*inv[i]%P;
        fac[i]=1ll*fac[i-1]*i%P;
    }
}

int A[N],B[N],W[N];

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    int n,m,s; scanf("%d%d%d",&n,&m,&s);
    rep(i,0,m+1) scanf("%d",&W[i]);
    init(max(max(n,m),s));
    int lim=min(m,n/s);
    rep(i,0,lim+1) {
        A[i]=1ll*fac[i]*getC(m,i)%P*fac[n]%P*fpow(ifac[s],i)%P
                *ifac[n-i*s]%P*fpow(m-i,n-i*s)%P;
        B[i]=(i&1)?P-ifac[i]:ifac[i];
    }
    reverse(B,B+lim+1);
    int limit=1; while(limit<=2*lim) limit<<=1; Poly::init(limit);
    ntt(A,limit,1),ntt(B,limit,1);
    rep(i,0,limit) A[i]=1ll*A[i]*B[i]%P;
    ntt(A,limit,-1);
    int ans=0;
    rep(i,0,m+1) ans=add(ans,1ll*W[i]*A[i+lim]%P*ifac[i]%P);
    printf("%d\n",ans);
    return 0;
}