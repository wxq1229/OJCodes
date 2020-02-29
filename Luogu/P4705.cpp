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

const int N=3e5+10,P=998244353,gn=3,ign=332748118;

inline int add(int x,int y) {return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+P:x;}
inline int fpow(int x,int y) {
    int ret=1; for (;y;y>>=1,x=1ll*x*x%P) 
        if (y&1) ret=1ll*ret*x%P; 
    return ret;
}

namespace Poly {
    int rev[N];
    void init(int n) {rep(i,0,n) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);}

    void ntt(int *f,int n,int flg) {
        rep(i,0,n) if (rev[i]<i) swap(f[i],f[rev[i]]);
        for (int len=2,k=1;len<=n;len<<=1,k<<=1) {
            int wn=fpow(flg==1?gn:ign,(P-1)/len);
            for (int i=0;i<n;i+=len)
                for (int j=i,w=1;j<i+k;j++,w=1ll*w*wn%P) {
                    int tmp=1ll*f[j+k]*w%P;
                    f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
                }
        }
        if (flg==-1) {
            int inv=fpow(n,P-2);
            rep(i,0,n) f[i]=1ll*f[i]*inv%P;
        }
    }

    void dao(int *f,int n,int *g) {
        static int F[N]; rep(i,0,n) F[i]=f[i];
        rep(i,1,n) g[i-1]=1ll*F[i]*i%P;g[n]=0;
    }
    void jifen(int *f,int n,int *g) {
        static int F[N]; rep(i,0,n) F[i]=f[i];
        rep(i,0,n) g[i+1]=1ll*F[i]*fpow(i+1,P-2)%P;g[0]=0;
    }

    void getinv(int *f,int n,int *G) {
        if (n==1) {G[0]=fpow(f[0],P-2);return;}
        getinv(f,(n+1)>>1,G);
        static int F[N]; int limit=1;
        while(limit<=2*(n-1)) limit<<=1; init(limit);
        rep(i,0,limit) F[i]=i>=n?0:f[i],G[i]=i>=n?0:G[i];
        ntt(F,limit,1),ntt(G,limit,1);
        rep(i,0,limit) G[i]=1ll*G[i]*sub(2,1ll*F[i]*G[i]%P)%P;
        ntt(G,limit,-1);
        rep(i,n,limit) G[i]=0;
    }

    void getln(int *f,int n,int *G) {
        static int derv[N],inv[N];
        getinv(f,n,inv),dao(f,n,derv);
        int limit=1; while(limit<=2*(n-1)) limit<<=1; init(limit);
        rep(i,n,limit) derv[i]=inv[i]=0;
        ntt(derv,limit,1),ntt(inv,limit,1);
        rep(i,0,limit) G[i]=1ll*derv[i]*inv[i]%P;
        ntt(G,limit,-1);
        jifen(G,n,G);
        rep(i,n,limit) G[i]=0;
    }
}
using Poly::ntt;
using Poly::getinv;
using Poly::getln;
using Poly::dao;

int tn,ifac[N],fac[N],inv[N];

void init(int n) {
    ifac[0]=ifac[1]=fac[0]=fac[1]=inv[1]=1;
    rep(i,2,n+1) {
        inv[i]=1ll*inv[P%i]*(P-P/i)%P;
        ifac[i]=1ll*ifac[i-1]*inv[i]%P;
        fac[i]=1ll*fac[i-1]*i%P;
    }
}

void fff(int *a,int l,int r,int *F) {
    if (l==r) {F[0]=1,F[1]=(P-a[l])%P;return;}
    int mid=(l+r)>>1;
    int Fl[N],Fr[N];
    fff(a,l,mid,Fl),fff(a,mid+1,r,Fr);
    int limit=1; while(limit<=r-l+1) limit<<=1; Poly::init(limit);
    rep(i,mid-l+2,limit) Fl[i]=0;
    rep(i,r-mid+1,limit) Fr[i]=0;
    ntt(Fl,limit,1),ntt(Fr,limit,1);
    rep(i,0,limit) F[i]=1ll*Fl[i]*Fr[i]%P;    
    ntt(F,limit,-1);
    rep(i,r-l+2,limit) F[i]=0;
}

void getF(int *a,int n,int *F) {
    fff(a,1,n,F); static int G[N];
    getln(F,tn+1,G);
    dao(G,tn+1,F);
    per(i,tn+1,1) F[i]=P-F[i-1];
    F[0]=n;
    rep(i,0,tn+1) F[i]=1ll*F[i]*ifac[i]%P; 
}

int n,m,K,a[N],b[N],A[N],B[N];
int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) scanf("%d",&a[i]);
    rep(i,1,m+1) scanf("%d",&b[i]);
    scanf("%d",&K); init(tn=max(max(n,m),K));
    getF(a,n,A),getF(b,m,B);
    int limit=1; while(limit<=2*tn) limit<<=1; Poly::init(limit);
    ntt(A,limit,1),ntt(B,limit,1);
    rep(i,0,limit) A[i]=1ll*A[i]*B[i]%P;
    ntt(A,limit,-1); int iv=fpow(1ll*n*m%P,P-2);
    rep(i,1,K+1) printf("%d\n",1ll*iv*fac[i]%P*A[i]%P);
    return 0;
}