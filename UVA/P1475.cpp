#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
typedef double db;
const db eps=1e-9;
struct point{
	db x,y;
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	db angle(){return atan2(y,x);}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
inline db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
inline db dot(point k1,point k2){return k1.x*k2.x+k1.y*k2.y;}
struct line{
	point p,v;
	db ang;
	line(point s,point v){
		p=s;this->v=v;
		ang=v.angle();
	}
	line(){}
	bool operator < (const line& l1)const{return ang<l1.ang;}
};
point intersect(line l1,line l2){
	point k1=l1.p,k2=l2.p;
	point v=l1.v,w=l2.v;
	db x=cross(w,k1-k2)/cross(v,w);
	return k1+v*x;
}
int onLeft(line l1,point k1){
	return cross(l1.v,k1-l1.p)>0;
}
int n;
point P[100010],p[100010];
line q[100010],L[100010];
void init(int k1){
	rep (i,0,n-1) L[i]=line(P[i],P[i]-P[(i+k1+1)%n]);
}
int check(int k1){
	init(k1);
	sort(L,L+n);
	int l,r;q[l=r=0]=L[0];
	rep (i,1,n-1){
		while (l<r&&!onLeft(L[i],p[r-1])) --r;
		while (l<r&&!onLeft(L[i],p[l]))++l;
		q[++r]=L[i];
		if (fabs(cross(q[r].v,q[r-1].v))<eps){
			--r;
			if (onLeft(q[r],L[i].p))q[r]=L[i];
		}
		if (l<r) p[r-1]=intersect(q[r],q[r-1]);
	}
	while (l<r&&!onLeft(q[l],p[r-1])) --r;
	return r-l>1;
}
int main(){
	while(scanf("%d",&n)==1){
		rep (i,0,n-1)P[i].scan();
		int l=1,r=n,ans=0;
		while (l<=r){
			int mid=(l+r)>>1;
			if (check(mid)) l=mid+1;
			else r=mid-1,ans=mid;
		}
		printf("%d\n",ans);
	}
	return 0;
}










