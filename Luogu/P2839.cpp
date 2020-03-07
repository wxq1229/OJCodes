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

const int N=1e5+10;
struct info {
    int sum,lmx,rmx;
};
info operator+(info a,info b) {
    return (info){a.sum+b.sum,max(a.lmx,a.sum+b.lmx),max(b.rmx,b.sum+a.rmx)};
}

struct node {
    int lc,rc;
    info res;
    inline void clear(){lc=rc=0,res=(info){0,0,0};}
}t[N*44];
int cnt,rt[N];

void pushup(int x) {t[x].res=t[t[x].lc].res+t[t[x].rc].res;}

info qry(int x,int l,int r,int ql,int qr) {
    if(ql>qr) return {0,0,0};
    if(ql<=l&&r<=qr) return t[x].res;
    int mid=(l+r)>>1;
    if(qr<=mid) return qry(t[x].lc,l,mid,ql,qr);
    else if(mid<ql) return qry(t[x].rc,mid+1,r,ql,qr);
    else return qry(t[x].lc,l,mid,ql,qr)+qry(t[x].rc,mid+1,r,ql,qr);
}

void build(int &x,int l,int r) {
    x=++cnt,t[x].clear();
    if(l==r) {t[x].res=(info){1,1,1};return;} 
    int mid=(l+r)>>1;
    build(t[x].lc,l,mid),build(t[x].rc,mid+1,r);
    pushup(x);
}

void mdf(int pre,int &x,int l,int r,int p,int v) {
    x=++cnt,t[x].lc=t[pre].lc,t[x].rc=t[pre].rc,t[x].res=t[pre].res;
    if(l==r) {
        t[x].res=(info){v,v,v};
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) mdf(t[pre].lc,t[x].lc,l,mid,p,v);
    else mdf(t[pre].rc,t[x].rc,mid+1,r,p,v);
    pushup(x);
}

int a[N],n,m,ord[N];

int solve(int a,int b,int c,int d) {   
    auto check=[&](int k1) {
        info md=qry(rt[k1],1,n,b+1,c-1);
        info lft=qry(rt[k1],1,n,a,b);
        info rgt=qry(rt[k1],1,n,c,d);
        return md.sum+lft.rmx+rgt.lmx>=0;
    };
    int l=1,r=n,ans=-1;
    while (l<=r) {
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1,ans=mid;
        else r=mid-1;
    }
    return ::a[ord[ans]];
}

int main() {
#ifdef LOCAL
    freopen("a.in","r",stdin);
#endif
    scanf("%d",&n);
    rep(i,1,n+1) scanf("%d",&a[i]),ord[i]=i;
    sort(ord+1,ord+n+1,[](int i,int j) {return a[i]<a[j];});
    build(rt[1],1,n);
    rep(i,2,n+1) mdf(rt[i-1],rt[i],1,n,ord[i-1],-1);
    int lstans=0;
    for (scanf("%d",&m);m;m--) {
        int p[4]; scanf("%d%d%d%d",p,p+1,p+2,p+3);
        p[0]=(p[0]+lstans)%n,p[1]=(p[1]+lstans)%n;
        p[2]=(p[2]+lstans)%n,p[3]=(p[3]+lstans)%n;
        sort(p,p+4); printf("%d\n",lstans=solve(p[0]+1,p[1]+1,p[2]+1,p[3]+1));
    }
    return 0;
}