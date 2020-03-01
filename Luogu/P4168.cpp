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

const int N=4e4+10;
struct node {
    int v,x,id;
}a[N];
int n,m,tn,tb,tot;

int bel[N],cc[300][N],ansv[300][300],ansc[300][300];
int lb[300],rb[300];
void init() {
    tn=(int)(pow(n/2.0,0.5)+0.5);
    rep(i,1,n+1) {
        bel[i]=(i-1)/tn+1,tb=bel[i];
        lb[bel[i]]=lb[bel[i]]==0?i:lb[bel[i]];
        rb[bel[i]]=i;
    }
    rep(i,1,tb+1) rep(j,lb[i],rb[i]+1) cc[i][a[j].x]++;
    rep(i,1,tb+1) rep(j,1,tot+1) cc[i][j]+=cc[i-1][j];
    rep(i,1,tb+1) {
        static int cnt[N];
        int mxc=0,mxv=0;
        rep(j,i,tb+1) {
            rep(k,lb[j],rb[j]+1) {
                ++cnt[a[k].x];
                if(cnt[a[k].x]>mxc||(cnt[a[k].x]==mxc&&a[k].v<mxv))
                    mxv=a[k].v,mxc=cnt[a[k].x];
            }
            ansv[i][j]=mxv,ansc[i][j]=mxc;
        }
        rep(j,i,tb+1) rep(k,lb[j],rb[j]+1) --cnt[a[k].x];
    }
}

#define getcc(l,r,k) (cc[r][k]-cc[l-1][k])

int query(int l,int r) {
    int bbl=bel[l],bbr=bel[r];
    int l0=1,r0=0,l1=1,r1=0;
    if(lb[bbl]!=l) l0=l,r0=rb[bbl],++bbl;
    if(rb[bbr]!=r) l1=lb[bbr],r1=r,--bbr;
    int ans1=ansv[bbl][bbr],ans2=ansc[bbl][bbr];
    static int cnt[N];
    rep(i,l0,r0+1) {
        ++cnt[a[i].x];
        int tmpc=cnt[a[i].x]+getcc(bbl,bbr,a[i].x);
        if(tmpc>ans2||(tmpc==ans2&&a[i].v<ans1))
            ans1=a[i].v,ans2=tmpc;
    }
    rep(i,l1,r1+1) {
        ++cnt[a[i].x];
        int tmpc=cnt[a[i].x]+getcc(bbl,bbr,a[i].x);
        if(tmpc>ans2||(tmpc==ans2&&a[i].v<ans1))
            ans1=a[i].v,ans2=tmpc;
    }
    rep(i,l0,r0+1) --cnt[a[i].x];
    rep(i,l1,r1+1) --cnt[a[i].x];
    return ans1;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
#endif
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) {
        scanf("%d",&a[i].v);
        a[i].id=i;
    }
    sort(a+1,a+n+1,[](node a,node b) {
        return a.v<b.v;
    });
    rep(i,1,n+1) a[i].x=a[i].v==a[i-1].v?a[i-1].x:++tot;
    sort(a+1,a+n+1,[](node a,node b) {return a.id<b.id;});
    init();
    int lstans=0; while(m--) {
        int l,r; scanf("%d%d",&l,&r);
        l=(l+lstans-1)%n+1,r=(r+lstans-1)%n+1;
        if(l>r) swap(l,r);
        printf("%d\n",lstans=query(l,r));
    }
    return 0;
}