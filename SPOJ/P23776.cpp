#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
struct Segtree
{
    int sum[N*40],rc[N*40],lc[N*40],cnt;
    void ins(int pre,int &x,int l,int r,int p)
    {
        sum[x=++cnt]=sum[pre]+1,lc[x]=lc[pre],rc[x]=rc[pre];
        if(l==r) return; int mid=(l+r)>>1;
        if(p<=mid) ins(lc[pre],lc[x],l,mid,p);
        else ins(rc[pre],rc[x],mid+1,r,p);
    }
    int qry(int x,int y,int l,int r,int ql,int qr)
    {
        if(ql<=l&&r<=qr) return sum[y]-sum[x];
        int mid=(l+r)>>1,ret=0;
        if(ql<=mid) ret+=qry(lc[x],lc[y],l,mid,ql,qr);
        if(mid<qr) ret+=qry(rc[x],rc[y],mid+1,r,ql,qr);
        return ret;
    }
    void build(int &x,int l,int r)
    {
        sum[x=++cnt]=lc[x]=rc[x]=0;
        if(l==r) return; int mid=(l+r)>>1;
        build(lc[x],l,mid),build(rc[x],mid+1,r);
    }
}T;
int val[N],tot,n,Q,a[N],rt[N];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]),val[i]=a[i];
    sort(val+1,val+n+1),tot=unique(val+1,val+n+1)-val-1;
    T.build(rt[0],1,tot);
    for(int i=1;i<=n;i++) 
        T.ins(rt[i-1],rt[i],1,tot,lower_bound(val+1,val+tot+1,a[i])-val);
    scanf("%d",&Q);int lstans=0;while(Q--)
    {
        int l,r,k; scanf("%d%d%d",&l,&r,&k);
        l^=lstans,r^=lstans,k^=lstans;
        l=max(1,l),r=min(n,r);
        if(l>r){printf("%d\n",lstans=0);continue;}
        int p=upper_bound(val+1,val+tot+1,k)-val;
        if(p==tot+1){lstans=0;puts("0");continue;}
        printf("%d\n",lstans=T.qry(rt[l-1],rt[r],1,tot,p,tot));
    }
    return 0;
}