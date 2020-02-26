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

const int P=1e9+7,maxn=3e6,N=maxn+10;
inline int add(int x,int y) {return (x+=y)>=P?x-P:x;}
inline int sub(int x,int y) {return (x-=y)<0?x+P:x;}
inline int fpow(int x,int y) {
    int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
        if(y&1) ret=1ll*ret*x%P;
    return ret;
}
inline int normal(int x) {return x<0?x+P:x;}

bitset<N> vis;
int p[N],pn,mu[N];

void init(int n) {
    mu[1]=1;
    rep(i,2,n+1) {
        if(!vis[i]) {
            p[pn++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<pn&&i*p[j]<=n;j++) {
            vis[i*p[j]]=1;
            if(i%p[j]==0) {mu[i*p[j]]=0;break;}
            else mu[i*p[j]]=-mu[i];
        }
    }
    rep(i,1,n+1) mu[i]+=mu[i-1];
    rep(i,1,n+1) mu[i]=normal(mu[i]);
}

map<int,int> musum;
int Smu(int n) {
    if(n<=maxn) return mu[n];
    if(musum.count(n)) return musum[n];
    int ans=1;
    for(int l=2,r=0;l<=n;l=r+1) {
        r=n/(n/l);
        ans=sub(ans,1ll*(r-l+1)*Smu(n/l)%P);
    }
    return musum[n]=ans;
}

int S(int L,int R,int n) {
    int tn=R,ans=0; --L;
    for(int l=1,r=0;l<=tn;l=r+1) {
        if(L/l>0) r=min(L/(L/l),R/(R/l));
        else r=R/(R/l);
        ans=add(ans,1ll*sub(Smu(r),Smu(l-1))*fpow(R/l-L/l,n)%P);
    }
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    init(maxn);
    int n,k,l,r;
    scanf("%d%d%d%d",&n,&k,&l,&r);
    printf("%d\n",S(l/k+(l%k!=0),r/k,n));
    return 0;
}