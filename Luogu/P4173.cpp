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

const db PI=acos(-1.0),eps=1e-7;
const int N=2e6+10;

inline int sign(db a) {return a<-eps?-1:a>eps;}

struct cpl {
    db x,y;
    cpl(db _x=0,db _y=0):x(_x),y(_y) {}
};

cpl operator+(cpl A,cpl B) {return cpl(A.x+B.x,A.y+B.y);}
cpl operator-(cpl A,cpl B) {return cpl(A.x-B.x,A.y-B.y);}
cpl operator*(cpl A,cpl B) {return cpl(A.x*B.x-A.y*B.y,A.x*B.y+A.y*B.x);}

int rev[N];
inline void init(int n) {rep(i,0,n) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);}

void fft(cpl *f,int n,int flg) {
    rep(i,0,n) if(rev[i]<i) swap(f[i],f[rev[i]]);
    for(int len=2,k=1;len<=n;len<<=1,k<<=1) {
        cpl wn(cos(2*PI/len),flg*sin(2*PI/len));
        for(int i=0;i<n;i+=len) {
            cpl w(1,0);
            for(int j=i;j<i+k;j++,w=w*wn) {
                cpl tmp=f[j+k]*w;
                f[j+k]=f[j]-tmp,f[j]=f[j]+tmp;
            }
        }
    }
}

int A[N],B[N],n,m;
cpl F[N],G[N],D[N];
VI ans;

inline char nc() {char ch=getchar();while(isspace(ch))ch=getchar();return ch;}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d",&n,&m);
    per(i,n,0) {char ch=nc();A[i]=ch=='*'?0:ch-'a'+1;}
    rep(i,0,m) {char ch=nc();B[i]=ch=='*'?0:ch-'a'+1;}
    int lim=1; while(lim<=n+m) lim<<=1; init(lim);
    
    rep(i,0,lim) D[i]=F[i]=G[i]=cpl(0,0);
    rep(i,0,n) F[i]=cpl(1.0*A[i]*A[i]*A[i],0); rep(i,0,m) G[i]=cpl(B[i],0);
    fft(F,lim,1),fft(G,lim,1);
    rep(i,0,lim) D[i]=D[i]+F[i]*G[i];
    
    rep(i,0,lim) F[i]=G[i]=cpl(0,0);
    rep(i,0,n) F[i]=cpl(1.0*A[i]*A[i],0); rep(i,0,m) G[i]=cpl(1.0*B[i]*B[i],0);
    fft(F,lim,1),fft(G,lim,1);
    rep(i,0,lim) D[i]=D[i]-cpl(2,0)*F[i]*G[i];

    rep(i,0,lim) F[i]=G[i]=cpl(0,0);
    rep(i,0,n) F[i]=cpl(A[i],0); rep(i,0,m) G[i]=cpl(1.0*B[i]*B[i]*B[i],0);
    fft(F,lim,1),fft(G,lim,1);
    rep(i,0,lim) D[i]=D[i]+F[i]*G[i];

    fft(D,lim,-1);
    rep(i,n-1,m) if((ll)(D[i].x/lim+0.5)==0) ans.pb(i-n+1);
    printf("%d\n",SZ(ans));
    for(auto i:ans) printf("%d ",i+1);
    return 0;   
}