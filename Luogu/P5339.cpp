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

const int N=1e5+10,P=998244353,gn=3,ign=(P+1)/gn;
inline int add(int x,int y) {return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+P:x;}
inline int fpow(int x,int y) {
    int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
        if(y&1) ret=1ll*ret*x%P;
    return ret;
}

namespace Poly {
    int rev[N];

    inline void init(int n) {rep(i,0,n) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);}

    void ntt(int *f,int n,int flg) {
        rep(i,0,n) if(rev[i]<i) swap(f[i],f[rev[i]]);
        for(int len=2,k=1;len<=n;len<<=1,k<<=1) {
            int wn=fpow(flg==1?gn:ign,(P-1)/len);
            for(int i=0;i<n;i+=len)
                for(int j=i,w=1;j<i+k;j++,w=1ll*w*wn%P) {
                    int tmp=1ll*f[j+k]*w%P;
                    f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
                }
        }
        if(flg==-1) {
            int inv=fpow(n,P-2);
            rep(i,0,n) f[i]=1ll*f[i]*inv%P;
        }
    }
}
using Poly::ntt;

int inv[N],fac[N],ifac[N];
void init(int n) {
    fac[0]=fac[1]=ifac[0]=ifac[1]=inv[1]=1;
    rep(i,2,n+1) {
        inv[i]=1ll*inv[P%i]*(P-P/i)%P;
        fac[i]=1ll*fac[i-1]*i%P;
        ifac[i]=1ll*ifac[i-1]*inv[i]%P;
    }
}
inline int getC(int n,int r) {return n<r?0:1ll*fac[n]*ifac[n-r]%P*ifac[r]%P;}

int F[4][N];
inline int getP(int n,int c1,int c2,int c3,int c4) {
    rep(i,0,c1+1) F[0][i]=ifac[i];
    rep(i,0,c2+1) F[1][i]=ifac[i];
    rep(i,0,c3+1) F[2][i]=ifac[i];
    rep(i,0,c4+1) F[3][i]=ifac[i];
    int limit=1; while(limit<=c1+c2+c3+c4) limit<<=1; Poly::init(limit);
    ntt(F[0],limit,1),ntt(F[1],limit,1),ntt(F[2],limit,1),ntt(F[3],limit,1);
    rep(i,0,limit) F[0][i]=1ll*F[0][i]*F[1][i]%P*F[2][i]%P*F[3][i]%P;
    ntt(F[0],limit,-1); 
    int ans=1ll*fac[n]*F[0][n]%P;
    rep(i,0,limit) F[0][i]=F[1][i]=F[2][i]=F[3][i]=0;
    return ans;
}

int n,c[4];
inline int getG(int k) {return 1ll*getC(n-3*k,k)*getP(n-4*k,c[0]-k,c[1]-k,c[2]-k,c[3]-k)%P;}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d%d%d%d",&n,c,c+1,c+2,c+3);
    init(max(n,c[0]+c[1]+c[2]+c[3])); int ans=0,lim=min(n/4,min(c[0],min(c[1],min(c[2],c[3]))));
    rep(i,0,lim+1) ans=add(ans,1ll*((i&1)?P-1:1)*getG(i)%P);
    printf("%d\n",ans);
    return 0;
}