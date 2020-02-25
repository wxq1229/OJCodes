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

const int maxn=1e7,N=maxn+10;
int vis[N],p[N],pn,mu[N],sum[N];

#define ss(l,r) (sum[r]-sum[l-1])

void init(int n) {
    mu[1]=1;
    rep(i,2,n+1) {
        if(!vis[i]) {p[pn++]=i;mu[i]=-1;}
        for(int j=0;j<pn&&i*p[j]<=n;j++) {
            vis[i*p[j]]=1;
            if(i%p[j]==0) {mu[i*p[j]]=0;break;}
            else mu[i*p[j]]=-mu[i];
        }
    }
    rep(i,0,pn) for(int j=p[i];j<=n;j+=p[i])
        sum[j]+=mu[j/p[i]];
    rep(i,1,n+1) sum[i]+=sum[i-1];
}

ll solve(int n,int m) {
    int tn=min(n,m); ll ans=0;
    for(int l=1,r=0;l<=tn;l=r+1) {
        r=min(n/(n/l),m/(m/l));
        ans+=1ll*(n/l)*(m/l)*ss(l,r);
    }
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    init(maxn);
    int _,n,m;for(scanf("%d",&_);_;_--) {
        scanf("%d%d",&n,&m);
        printf("%lld\n",solve(n,m));
    }
    return 0;
}