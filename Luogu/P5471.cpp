#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
const int INF=0x3f3f3f3f;
#define NONE (INF)
const int MAXN=400010;
struct point{int x,y;}p[MAXN];
int cmptype;
int cmp(point a,point b){
	if (cmptype==0) return a.x<b.x;
	else return a.y<b.y;
}
int cmpi(int a,int b){return cmp(p[a],p[b]);}
point max(point a,point b){return (point){max(a.x,b.x),max(a.y,b.y)};}
point min(point a,point b){return (point){min(a.x,b.x),min(a.y,b.y)};}
struct node{
	point p,lp,rp;
	int d,lc,rc,id;
	int vis,tag,minv,maxv,val;
}t[MAXN];
int size=0;
#define newnode() (++size)
void update(int x){
	if (t[x].vis)t[x].maxv=-INF,t[x].minv=INF;
	else t[x].maxv=t[x].minv=t[x].val;
	int l=t[x].lc,r=t[x].rc;
	if (l){
		t[x].maxv=max(t[x].maxv,t[l].maxv);
		t[x].minv=min(t[x].minv,t[l].minv);
	}
	if (r){
		t[x].maxv=max(t[x].maxv,t[r].maxv);
		t[x].minv=min(t[x].minv,t[r].minv);
	}
}
void pushup(int x){
	if (t[x].vis) t[x].lp=(point){INF,INF},t[x].rp=(point){-INF,-INF};
	else t[x].lp=t[x].rp=t[x].p;
	int l=t[x].lc,r=t[x].rc;
	if (l){
		t[x].lp=min(t[x].lp,t[l].lp);
		t[x].rp=max(t[x].rp,t[l].rp);
	}
	if (r){
		t[x].lp=min(t[x].lp,t[r].lp);
		t[x].rp=max(t[x].rp,t[r].rp);
	}
}
int order[MAXN];
int build(int l,int r,int d){
	if (l>r) return 0;
	cmptype=d;
	int mid=(l+r)>>1;
	nth_element(order+l,order+mid,order+r+1,cmpi);
	int x=newnode();
	t[x].val=INF,t[x].id=order[mid];
	t[x].tag=NONE,t[x].vis=0;
	t[x].p=p[order[mid]],t[x].d=d;
	if (t[x].id==1) t[x].val=0;
	t[x].lc=build(l,mid-1,d^1);
	t[x].rc=build(mid+1,r,d^1);
	pushup(x),update(x);
	return x;
}
void addtag(int x,int val){
	if (!x) return;
	if (val<t[x].maxv&&val<t[x].tag){
		t[x].tag=val;
		t[x].maxv=val;
		t[x].minv=min(t[x].minv,val);
		if (t[x].vis==0)t[x].val=min(t[x].val,val);
	}
}
void pushdown(int x){
	if (t[x].tag==NONE) return;
	addtag(t[x].lc,t[x].tag);
	addtag(t[x].rc,t[x].tag);
	t[x].tag=NONE;
}
int find(int x,int val){
	pushdown(x);
	if (t[x].val==val&&t[x].vis==0){
		t[x].vis=1;
		pushup(x),update(x);
		return x;
	}
	int l=t[x].lc,r=t[x].rc;
	if (l&&val==t[l].minv){
		int ans=find(l,val);
		pushup(x),update(x);
		return ans;
	}else{
		assert(val==t[t[x].rc].minv&&r);
		int ans=find(r,val);
		pushup(x),update(x);
		return ans;
	}
}
void modify(int x,point ql,point qr,int val){
	pushdown(x);
	if (val>=t[x].maxv) return;
	if (ql.x>t[x].rp.x||ql.y>t[x].rp.y||qr.x<t[x].lp.x||qr.y<t[x].lp.y)
		return;
	if (ql.x<=t[x].lp.x&&t[x].rp.x<=qr.x&&ql.y<=t[x].lp.y&&t[x].rp.y<=qr.y){
		addtag(x,val);
		return;
	}
	if (t[x].vis==0&&ql.x<=t[x].p.x&&t[x].p.x<=qr.x&&ql.y<=t[x].p.y&&t[x].p.y<=qr.y)
		t[x].val=min(t[x].val,val);
	if (t[x].lc)modify(t[x].lc,ql,qr,val);
	if (t[x].rc)modify(t[x].rc,ql,qr,val);
	pushup(x),update(x);
}
int ans[MAXN],root;
struct edge{
	point lp,rp;
	int dis;
};
vector<edge> e[MAXN];
int main(){
	int n,m,w,h;scanf("%d%d%d%d",&n,&m,&w,&h);
	rep (i,1,n) scanf("%d%d",&p[i].x,&p[i].y),order[i]=i;
	rep (i,1,m){
		int at;scanf("%d",&at);
		int x1,x2,y1,y2,len;
		scanf("%d%d%d%d%d",&len,&x1,&x2,&y1,&y2);
		e[at].push_back((edge){(point){x1,y1},(point){x2,y2},len});
	}
	root=build(1,n,0);
	ans[1]=0;
	rep (it,1,n){
		int at=find(root,t[root].minv);
		int now=t[at].id;
//		cerr<<now<<endl;
		ans[now]=t[at].val;
		rep (i,0,e[now].size()-1){
			int val=ans[now]+e[now][i].dis;
//			cerr<<val<<endl;
			modify(root,e[now][i].lp,e[now][i].rp,val);
		}
	}
	rep (i,2,n)printf("%d\n",ans[i]);
	return 0;
}










