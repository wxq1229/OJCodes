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

const int N=5e5+10;
int a[N],val[N],tot,n,m;

int f[777][777],tn,bel[N],pos[N],tb;
int lb[777],rb[777],cnt[N];
VI vec[N];

void init() {
    rep(i,1,n+1) val[i]=a[i]; sort(val+1,val+n+1);
    tot=unique(val+1,val+n+1)-val-1;
    rep(i,1,n+1) a[i]=lower_bound(val+1,val+tot+1,a[i])-val;
    rep(i,1,n+1) {
        vec[a[i]].pb(i);
        pos[i]=SZ(vec[a[i]])-1;
    }
    tn=(int)(sqrt(n));
    rep(i,1,n+1) {
        bel[i]=(i-1)/tn+1,tb=bel[i];
        lb[bel[i]]=lb[bel[i]]==0?i:lb[bel[i]],rb[bel[i]]=i;
    }
    rep(i,1,tb+1) {
        rep(j,i,tb+1) {
            f[i][j]=f[i][j-1];
            rep(k,lb[j],rb[j]+1) f[i][j]=max(f[i][j],++cnt[a[k]]);
        }
        rep(j,i,tb+1) rep(k,lb[j],rb[j]+1) --cnt[a[k]];
    }
}

int query(int l,int r) {
    int bl=bel[l],br=bel[r];
    if(bl==br) {
        int ans=0;
        rep(i,l,r+1) ans=max(ans,++cnt[a[i]]);
        rep(i,l,r+1) --cnt[a[i]];
        return ans; 
    }
    int r0=0,l1=2333333,ans=0;
    if(lb[bl]!=l) r0=rb[bl],++bl;
    if(rb[br]!=r) l1=lb[br],--br;
    ans=f[bl][br];
    rep(i,l,r0+1) {
        int at=pos[i];
        while(at+ans<SZ(vec[a[i]])&&vec[a[i]][at+ans]<=r) ++ans;
    }
    rep(i,l1,r+1) {
        int at=pos[i];
        while(at-ans>=0&&vec[a[i]][at-ans]>=l) ++ans;
    }
    return ans;
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d%d",&n,&m);
    rep(i,1,n+1) scanf("%d",&a[i]);
    init(); int lstans=0;
    while(m--) {
        int l,r; scanf("%d%d",&l,&r);
        l^=lstans,r^=lstans;
        printf("%d\n",lstans=query(l,r));
    }
    return 0;
}