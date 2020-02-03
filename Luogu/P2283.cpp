#include <bits/stdc++.h>
using namespace std;
typedef double db;

const db eps=1e-9;
inline int sign(db k1){
	if(k1<-eps) return -1; else if(k1>eps) return 1; else return 0;
}
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
	line(){}
	line(point k1,point k2){
		p=k1,v=k2;
		ang=k2.angle();
	}
	bool operator < (const line& l1)const{
		return ang<l1.ang;
	}
};
point intersect(line l1,line l2){
	point k1=l1.p,k2=l2.p;
	point v=l1.v,w=l2.v;
	db x=cross(w,k1-k2)/cross(v,w);
	return k1+v*x;
}
int onLeft(line l1,point p1){
	return sign(cross(l1.v,p1-l1.p))>0;
}
db polygonArea(point* P,int n){
	db area=0.0;
	for (int i=1;i<n-1;i++)
		area+=cross(P[i]-P[0],P[i+1]-P[0]);
	return area/2.0;
}
line q[10010];
point p[10010];
int getHalfplaneIntersection(line* L,int n,point* poly){
	sort(L,L+n);
	int l,r,m;
	q[l=r=0]=L[0];
	for (int i=1;i<n;i++){
		while (l<r&&!onLeft(L[i],p[r-1]))r--;
		while (l<r&&!onLeft(L[i],p[l]))l++;
		q[++r]=L[i];
		if (sign(cross(q[r].v,q[r-1].v))==0){
			r--;
			if (onLeft(q[r],L[i].p))q[r]=L[i];
		}	
		if (l<r)p[r-1]=intersect(q[r-1],q[r]);
	}
	while (l<r&&!onLeft(q[l],p[r-1]))r--;
	if (r-l<=1) return 0;
	p[r]=intersect(q[l],q[r]);
	m=0;
	for (int i=l;i<=r;i++)
		poly[m++]=p[i];
	return m;
}

line L[1510];
point P[1510],poly[1510];
int main(){
	int n;scanf("%d",&n);
	for (int i=0;i<n;i++)
		P[i].scan();
	P[n]=P[0];
	for (int i=0;i<n;i++)
		L[i]=line(P[i],P[i+1]-P[i]);
	int m=getHalfplaneIntersection(L,n,poly);
	db area1=polygonArea(poly,m);
	reverse(P,P+n);
	P[n]=P[0];
	for (int i=0;i<n;i++)
		L[i]=line(P[i],P[i+1]-P[i]);
	m=getHalfplaneIntersection(L,n,poly);
	db area2=polygonArea(poly,m);
	printf("%.2f\n",max(area1,area2));
	return 0;
}
