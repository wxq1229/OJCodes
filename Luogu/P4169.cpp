#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db alpha=0.725;
const int MAXN=600010;
struct point{
	int x,y;
}p[MAXN];
int dist(int i,int j){
	return abs(p[i].x-p[j].x)+abs(p[i].y-p[j].y);
}
struct node{
	point p,lp,rp;
	int d,lc,rc,id,size;
}t[MAXN];
int cnt=0;
queue<int> freenodes;
int newnode(){
	int x;
	if (freenodes.size()) x=freenodes.front(),freenodes.pop();
	else x=++cnt;
	return x;
}
int pos[MAXN],size=0;
void print(int x){
	if (t[x].lc)print(t[x].lc);
	pos[++size]=t[x].id;
	freenodes.push(x);
	if (t[x].rc)print(t[x].rc);
}
int cmptype;
int cmp(int i,int j){
	if (cmptype==0) return p[i].x<p[j].x;
	else return p[i].y<p[j].y;
}
void pushup(int x){
	t[x].lp=t[x].rp=t[x].p;
	int l=t[x].lc,r=t[x].rc;
	t[x].size=t[l].size+t[r].size+1;
	if (l){
		t[x].lp.x=min(t[x].lp.x,t[l].lp.x),t[x].lp.y=min(t[x].lp.y,t[l].lp.y);
		t[x].rp.x=max(t[x].rp.x,t[l].rp.x),t[x].rp.y=max(t[x].rp.y,t[l].rp.y);
	}
	if (r){
		t[x].lp.x=min(t[x].lp.x,t[r].lp.x),t[x].lp.y=min(t[x].lp.y,t[r].lp.y);
		t[x].rp.x=max(t[x].rp.x,t[r].rp.x),t[x].rp.y=max(t[x].rp.y,t[r].rp.y);
	}
}
int build(int l,int r,int type){
	if (l>r) return 0;
	int mid=(l+r)>>1;
	cmptype=type;
	nth_element(pos+l,pos+mid,pos+r+1,cmp);
	int x=newnode();
	t[x].p=p[pos[mid]],t[x].id=pos[mid];
	t[x].d=type;
	t[x].lc=build(l,mid-1,type^1);
	t[x].rc=build(mid+1,r,type^1);
	pushup(x);
	return x;
}
void rebuild(int& x){
	size=0,print(x);
	x=build(1,size,0);
}
int isbad(int x){return alpha*t[x].size<(db)max(t[t[x].lc].size,t[t[x].rc].size);}
void insert(int& x,int v){
	if (!x){
		x=newnode();
		t[x].size=1;
		t[x].p=p[v],t[x].id=v;
		t[x].d=rand()%2,pushup(x);
		return;
	}
	cmptype=t[x].d;
	if (cmp(v,t[x].id))insert(t[x].lc,v);
	else insert(t[x].rc,v);
	pushup(x);
	if (isbad(x))rebuild(x);
}
int exp(int i,int j){
	int ans=0;
	if (p[i].x<t[j].lp.x)ans+=t[j].lp.x-p[i].x;
	if (p[i].y<t[j].lp.y)ans+=t[j].lp.y-p[i].y;
	if (t[j].rp.x<p[i].x)ans+=p[i].x-t[j].rp.x;
	if (t[j].rp.y<p[i].y)ans+=p[i].y-t[j].rp.y;
	return ans;
}
int Min;
void query(int x,int v){
	if (v!=t[x].id)Min=min(Min,abs(p[v].x-t[x].p.x)+abs(p[v].y-t[x].p.y));
	int dl=t[x].lc?exp(v,t[x].lc):2e9,dr=t[x].rc?exp(v,t[x].rc):2e9;
	if (dl<dr){
		if (dl<Min)query(t[x].lc,v);
		if (dr<Min)query(t[x].rc,v);
	}
	else{
		if (dr<Min)query(t[x].rc,v);
		if (dl<Min)query(t[x].lc,v);
	}
}
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int n,Q;scanf("%d%d",&n,&Q);
	int now=n;
	for (int i=1;i<=n;i++)scanf("%d%d",&p[i].x,&p[i].y);
	for (int i=1;i<=n;i++)pos[i]=i;
	int root=build(1,n,0);
	for (int i=1;i<=Q;i++){
		int x,y,opt;
		scanf("%d%d%d",&opt,&x,&y);
		p[++now]=(point){x,y};
		if (opt==1)insert(root,now);
		else{
			Min=2e9;query(root,now);
			printf("%d\n",Min);
		}
	}
	return 0;
}
/*
2 3 
1 1 
2 3 
2 1 2 
1 3 3 
2 4 2
*/

