#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db alpha=0.7;
const int MAXN=200010;
struct point{
	int x,y,val;
}p[MAXN];
int pos[MAXN],cmptype=0,tot=0;
bool cmp(int i,int j){
	if (cmptype==0) return p[i].x<p[j].x;
	else return p[i].y<p[j].y;
}
struct node{
	point lp,rp;
	int d,id,val,lc,rc,sum,size;
}t[MAXN];
queue<int>q;
int size;
int newnode(){
	int x;
	if (q.size()) x=q.front(),q.pop();
	else x=++size;
	return x;
}
void pushup(int x){
	t[x].size=t[t[x].lc].size+t[t[x].rc].size+1;
	t[x].sum=t[t[x].lc].sum+t[t[x].rc].sum+t[x].val;
	t[x].lp=t[x].rp=p[t[x].id];
	if (t[x].lc){
		t[x].lp.x=min(t[x].lp.x,t[t[x].lc].lp.x);
		t[x].lp.y=min(t[x].lp.y,t[t[x].lc].lp.y);
		t[x].rp.x=max(t[x].rp.x,t[t[x].lc].rp.x);
		t[x].rp.y=max(t[x].rp.y,t[t[x].lc].rp.y);
	}
	if (t[x].rc){
		t[x].lp.x=min(t[x].lp.x,t[t[x].rc].lp.x);
		t[x].lp.y=min(t[x].lp.y,t[t[x].rc].lp.y);
		t[x].rp.x=max(t[x].rp.x,t[t[x].rc].rp.x);
		t[x].rp.y=max(t[x].rp.y,t[t[x].rc].rp.y);
	}
}
int build(int l,int r,int type){
	if (l>r) return 0;
	cmptype=type;
	int mid=(l+r)>>1;
	nth_element(pos+l,pos+mid,pos+r+1,cmp);
	int x=newnode();
	t[x].id=pos[mid],t[x].d=type;
	t[x].val=p[pos[mid]].val;
	t[x].size=1,t[x].sum=t[x].val;
	t[x].lc=build(l,mid-1,type^1);
	t[x].rc=build(mid+1,r,type^1);
	return pushup(x),x;
}
int isbad(int x){return alpha*t[x].size<(db)max(t[t[x].lc].size,t[t[x].rc].size);}
void print(int x){
	if (t[x].lc)print(t[x].lc);
	pos[++tot]=t[x].id;
	q.push(x);
	if (t[x].rc)print(t[x].rc);
}
void rebuild(int& x){
	tot=0,print(x);
	x=build(1,tot,rand()%2);
}
void insert(int& x,int v){
	if (!x){
		x=newnode();
		t[x].id=v,t[x].lc=t[x].rc=0;
		t[x].size=1,t[x].d=rand()%2;
		t[x].val=t[x].sum=p[v].val;
		pushup(x);return;
	}
	cmptype=t[x].d;
	if (cmp(v,t[x].d))insert(t[x].lc,v);
	else insert(t[x].rc,v);
	pushup(x);
	if (isbad(x))rebuild(x);
}
int query(int x,point ql,point qr){
	if (!x||qr.x<t[x].lp.x||qr.y<t[x].lp.y||t[x].rp.x<ql.x||t[x].rp.y<ql.y)return 0;
	if (ql.x<=t[x].lp.x&&t[x].rp.x<=qr.x&&ql.y<=t[x].lp.y&&t[x].rp.y<=qr.y)return t[x].sum;
	int ans=0;
	if (ql.x<=p[t[x].id].x&&p[t[x].id].x<=qr.x&&ql.y<=p[t[x].id].y&&p[t[x].id].y<=qr.y)
		ans=t[x].val;
	return ans+query(t[x].lc,ql,qr)+query(t[x].rc,ql,qr);
}
int main(){
	int opt,x,y,x1,y1,cur=0,root=0;
	scanf("%d%d",&x,&y);
	while (scanf("%d",&opt)==1&&opt!=3){
		scanf("%d%d%d",&x,&y,&x1);
		if (opt==1)p[++cur]=(point){x,y,x1},insert(root,cur);
		else{
			scanf("%d",&y1);
			printf("%d\n",query(root,(point){x,y},(point){x1,y1}));
		}
	}
	return 0;
}










