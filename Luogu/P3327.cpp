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

const int maxn=5e4,N=maxn+10;
int vis[N],p[N],pn,mu[N];
ll f[N];

void init(int n) {
    mu[1]=1;
    rep(i,2,n+1) {
        if(!vis[i]) {p[pn++]=i;mu[i]-=1;}
        for(int j=0;j<pn&&i*p[j]<=n;j++) {
            vis[i*p[j]]=1;
            if(i%p[j]==0) {mu[i*p[j]]=0;break;}
            else mu[i*p[j]]=-mu[i];
        }
    }
    rep(i,1,n+1) mu[i]+=mu[i-1];
    rep(i,1,n+1) for(int l=1,r=0;l<=i;l=r+1)
        r=i/(i/l),f[i]+=1ll*(i/l)*(r-l+1);
}

inline ll S(int n,int m) {return f[n]*f[m];}

ll solve(int n,int m) {
    int tn=min(n,m); ll ans=0;
    for(int l=1,r=0;l<=tn;l=r+1) {
        r=min(n/(n/l),m/(m/l));
        ans+=(mu[r]-mu[l-1])*S(n/l,m/l);
    }
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    init(maxn);
    int _,n,m; for(scanf("%d",&_);_;_--) {
        scanf("%d%d",&n,&m);
        printf("%lld\n",solve(n,m));
    }
    return 0;
}