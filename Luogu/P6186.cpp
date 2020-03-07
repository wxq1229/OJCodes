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

const int N=2e5+10;

struct BIT {
    ll c[N]; int n;

    void init(int sz) {n=sz;rep(i,0,n+1) c[i]=0;}

    ll qwq(int x) {
        ll ans=0; for(;x;x-=x&-x) ans+=c[x];
        return ans;
    }
    ll qry(int l,int r) {return qwq(r)-qwq(l-1);}
    void upd(int x,ll v=1) {if(x!=0) for(;x<=n;x+=x&-x) c[x]+=v;}
}bt[2];

void upd(int x,int v=1) {bt[0].upd(x,v),bt[1].upd(x,v*x);}
void qry(int l,int r,ll &c1,ll &c2) {c1=bt[0].qry(l,r),c2=bt[1].qry(l,r);}

int n,m,a[N],cc[N];

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) scanf("%d",&a[i]);
    bt[0].init(n);
    rep(i,1,n+1) {
        cc[i]=i-bt[0].qwq(a[i])-1;
        bt[0].upd(a[i]);
    }
    bt[0].init(n),bt[1].init(n);
    rep(i,1,n+1) upd(cc[i]);
    while(m--) {
        int opt,x; scanf("%d%d",&opt,&x);
        if(opt==2) {
            if(x>=n) {puts("0");continue;}
            ll t1,t2;
            qry(x+1,n,t1,t2);
            printf("%lld\n",t2-x*t1);
        } else {
            upd(cc[x],-1),upd(cc[x+1],-1);
            if(a[x]>a[x+1]) --cc[x+1]; else ++cc[x];
            swap(cc[x],cc[x+1]),swap(a[x],a[x+1]);
            upd(cc[x],1),upd(cc[x+1],1);
        }
    }
    return 0;
}