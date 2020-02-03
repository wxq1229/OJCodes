#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
typedef double db;
const db eps=1e-9;
inline int sign(db k1){
	if (k1<-eps) return -1; else if (k1>eps) return 1; else return 0;
}
struct point{
	db x,y;
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	bool operator == (const point& k1)const{return sign(x-k1.x)==0&&sign(y-k1.y)==0;}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	point operator / (const db& k1)const{return (point){x/k1,y/k1};}
	db angle(){return atan2(y,x);}
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	point normal(){return (point){-y/abs(),x/abs()};}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
inline db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
inline db dot(point k1,point k2){return k1.x*k2.x+k1.y*k2.y;}
struct line{
	point s,t;
	db ang;
	line(){}
	line(point s,point t):s(s),t(t){
		ang=(t-s).angle();
	}
	bool operator < (const line& l1){
		if (sign(ang-l1.ang)==0) return cross(l1.t-l1.s,t-l1.s)<=0;
		else return ang<l1.ang;
	}
	void print(){
		printf("from (");s.print();
		printf(") to (");t.print();
		printf(") angle = %.7f\n",ang);
	}
};
point intersect(line l1,line l2){
	point k1=l1.s,k2=l2.s;
	point v=l1.t-l1.s,w=l2.t-l2.s;
	db x=cross(w,k1-k2)/cross(v,w);
	return k1+v*x;
}
int onRight(point p,line l1){
	return cross(l1.t-l1.s,p-l1.s)<0;
}
vector<line>Lbuf;
line q[100010];
void getHalfPlaneIntersect(vector<line>L,vector<point>&sol){
	int n=L.size(),l=1,r=0;
	sort(L.begin(),L.end());
	Lbuf.clear();sol.clear();
	rep (i,0,n-2){
		if (sign(L[i].ang-L[i+1].ang)==0)continue;
		Lbuf.push_back(L[i]);
	}
	Lbuf.push_back(L[n-1]);L.clear();
	n=Lbuf.size();
	rep (i,0,n-1)L.push_back(Lbuf[i]);
//	rep (i,0,n-1)L[i].print();
	rep (i,0,n-1){
		while (l<r&&onRight(intersect(q[r],q[r-1]),L[i])) r--;
		while (l<r&&onRight(intersect(q[l],q[l+1]),L[i])) l++;
		q[++r]=L[i];
	}
	while (l<r&&onRight(intersect(q[r],q[r-1]),q[l])) r--;
	while (l<r&&onRight(intersect(q[l],q[l+1]),q[r])) l++;
	rep (i,l,r-1)
		sol.push_back(intersect(q[i],q[i+1]));
	sol.push_back(intersect(q[l],q[r]));
}
vector<point>P,hpi,V;
vector<line>L;
int main(){
	int n;
	while (scanf("%d",&n)==1&&n){
		P=vector<point>(n+1);V=vector<point>(n);
		L=vector<line>(n);
		rep (i,0,n-1)P[i].scan();
		P[n]=P[0];
		rep (i,0,n-1)
			V[i]=P[i+1]-P[i];
		//rep (i,0,n-1)
		//	P[i].print(),putchar(' '),V[i].print(),putchar('\n');
		db left=0.0,right=20000.0;
		while (left+1e-6<right){
			db mid=(left+right)/2.0;
			rep (i,0,n-1) L[i]=line(P[i]+V[i].normal()*mid,P[i]+V[i].normal()*mid+V[i]);
			//rep (i,0,n-1) L[i].print();
			getHalfPlaneIntersect(L,hpi);
			//printf("%d\n",hpi.size());
			if (hpi.size()<=2) right=mid;
			else left=mid;
		}
		printf("%.6f\n",left);
	}
	return 0;
}
/*
4
0 0
10000 0
10000 10000
0 10000
3
0 0
10000 0
7000 1000
6
0 40
100 20
250 40
250 70
100 90
0 70
3
0 0
10000 10000
5000 5001
0



*/
