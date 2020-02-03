#include <bits/stdc++.h>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define NONE (2147483647)
#define MAXN 400010
#define getc() (p1==p2&&(p2=(p1=ibuf)+fread(ibuf,1,486,stdin),p1==p2)?EOF:*p1++)
using namespace std;
char ibuf[486],*p1,*p2;
template<class T> inline void read(T& x){
    x=0; T f=1; char ch=getc();
    for(;ch<'0'||ch>'9';ch=getc())if(ch=='-')f*=-1;
    for(;ch>='0'&&ch<='9';ch=getc())x=(x<<1)+(x<<3)+(ch^48);
    x*=f;
}
namespace Treap{
    int size[MAXN<<2],val[MAXN<<2],cnt[MAXN<<2],ch[MAXN<<2][2],pri[MAXN<<2],tot=0;
    inline int newNode(int v){
        int x=++tot;
        val[x]=v; size[x]=cnt[x]=1;
        ch[x][0]=ch[x][1]=0;
        pri[x]=rand();
        return x;
    }
    inline void pushup(int x){
        if(!x) return;
        size[x]=size[ch[x][0]]+size[ch[x][1]]+cnt[x];
    }
    inline void rotate(int& x,int k){
        int y=ch[x][k^1]; ch[x][k^1]=ch[y][k]; ch[y][k]=x;
        pushup(x);pushup(y); x=y;
    }
    void insert(int& x,int v){
//		debug("%d\n",x);
        if(!x) x=newNode(v);
        else{
            if(val[x]==v){
                cnt[x]++;
                pushup(x);
                return;
            }
            int k=v>val[x];
//			debug("%d %d",ch[x][0],ch[x][1]);		
//			assert(false);
            insert(ch[x][k],v);
            if(pri[ch[x][k]]>pri[x]) rotate(x,k^1);
        }
        pushup(x);
    }
    void remove(int& x,int v){
        if(!x) return;
        if(val[x]==v){
            if(cnt[x]>1){cnt[x]--;pushup(x);return;}
            if(ch[x][0]&&ch[x][1]){
                int k=pri[ch[x][0]]<pri[ch[x][1]];
                rotate(x,k^1); remove(ch[x][k^1],v);
            }
            else{if(ch[x][0])x=ch[x][0]; else x=ch[x][1];}
        }
        else remove(ch[x][v>val[x]],v);
        pushup(x);
    }
    int kth(int x,int k){
        if(!x) return 0;
        int s=size[ch[x][0]];
        if(k<=s) return kth(ch[x][0],k);
        else if(k<=s+cnt[x]) return x;
        else return kth(ch[x][1],k-s-cnt[x]);
    }
    int rank(int x,int v){
        if(!x) return 0;
        int s=size[ch[x][0]];
        if(val[x]==v) return s;
        else if(v<val[x]) return rank(ch[x][0],v);
        else return rank(ch[x][1],v)+s+cnt[x];
    }
    int findpre(int x,int v){
        int res=-NONE;
        while(x){
            if(v==val[x]){
                if(ch[x][0]){
                    x=ch[x][0];
                    while(ch[x][1]) x=ch[x][1];
                    res=val[x];
                }
                break;
            }
            if(val[x]<v&&val[x]>res) res=val[x];
            x=ch[x][v>val[x]];
        }	
        return res;
    }
    int findnext(int x,int v){
        int res=NONE;
        while(x){
            if(v==val[x]){
                if(ch[x][1]){
                    x=ch[x][1];
                    while(ch[x][0]) x=ch[x][0];
                    res=val[x];
                }
                break;
            }
            if(val[x]>v&&val[x]<res) res=val[x];
            x=ch[x][v>val[x]];
        }
        return res;
    }
    void print(int x){
        if(ch[x][0]) print(ch[x][0]);
        debug("%d ",val[x]);
        if(ch[x][1]) print(ch[x][1]);
    }
    void output(int x){
        print(x);
        putchar('\n');
    }
}
int a[MAXN];
struct seg{
    int l,r;
    int root;
}tree[MAXN<<2];
void build(int x,int l,int r){
//	debug("building\n");
//	debug("[%d,%d]: ",l,r);
    tree[x].l=l; tree[x].r=r;
    for(int i=l;i<=r;i++)
        Treap::insert(tree[x].root,a[i]);
//	Treap::output(tree[x].root);
    if(l<r){
        int mid=(l+r)>>1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
    }
}
void modify(int x,int p,int v){
    Treap::remove(tree[x].root,a[p]);
    Treap::insert(tree[x].root,v);
    if(tree[x].l==tree[x].r)
        return;
    int mid=(tree[x].l+tree[x].r)>>1;
    if(p<=mid) modify(x<<1,p,v);
    else modify(x<<1|1,p,v);
}
int getpre(int x,int ql,int qr,int v){
    if(ql<=tree[x].l&&tree[x].r<=qr){
        return Treap::findpre(tree[x].root,v);
    }
    int res=-NONE;
    int mid=(tree[x].l+tree[x].r)>>1;
    if(ql<=mid) res=max(res,getpre(x<<1,ql,qr,v));
    if(mid<qr) res=max(res,getpre(x<<1|1,ql,qr,v));
    return res;
}
int getnext(int x,int ql,int qr,int v){
    if(ql<=tree[x].l&&tree[x].r<=qr){
        return Treap::findnext(tree[x].root,v);
    }
    int res=NONE;
    int mid=(tree[x].l+tree[x].r)>>1;
    if(ql<=mid) res=min(res,getnext(x<<1,ql,qr,v));
    if(mid<qr) res=min(res,getnext(x<<1|1,ql,qr,v));
    return res;
}
int getrank(int x,int ql,int qr,int v){
    if(ql<=tree[x].l&&tree[x].r<=qr){
//		debug("%d\n",Treap::rank(tree[x].root,v));
        return Treap::rank(tree[x].root,v);
    }
    int res=0;
    int mid=(tree[x].l+tree[x].r)>>1;
    if(ql<=mid) res+=getrank(x<<1,ql,qr,v);
    if(mid<qr) res+=getrank(x<<1|1,ql,qr,v);
    return res;
}
int getkth(int x,int ql,int qr,int k){
    int l=0,r=1e8+1;
    while(l+1<r){
        int mid=(l+r)>>1;
        if(getrank(1,ql,qr,mid)+1<=k) l=mid;
        else r=mid;
    }
    return l;
}
int main(){
#ifdef LOCAL
//	freopen("input.txt","r",stdin);
//	freopen("output.txt","w",stdout);
#endif
    int n,m;
    read(n),read(m);
    for(int i=1;i<=n;i++) read(a[i]);
    build(1,1,n);
    for(int i=1;i<=m;i++){
        int opt,x,y,v,k;
        read(opt);
        if(opt==1){
            read(x),read(y),read(k);
//		debug("%d %d %d\n",x,y,k);
            printf("%d\n",getrank(1,x,y,k)+1);
        }
        else if(opt==2){
            read(x),read(y),read(k);
//		debug("%d %d %d\n",x,y,k);
            printf("%d\n",getkth(1,x,y,k));	
        }
        else if(opt==3){
            read(x),read(v);
            modify(1,x,v);
            a[x]=v;
        }
        else if(opt==4){
            read(x),read(y),read(k);
//		debug("%d %d %d\n",x,y,k);
            printf("%d\n",getpre(1,x,y,k));
        }
        else if(opt==5){
            read(x),read(y),read(k);
//		debug("%d %d %d\n",x,y,k);
            printf("%d\n",getnext(1,x,y,k));
        }
    }
    return 0;
}
