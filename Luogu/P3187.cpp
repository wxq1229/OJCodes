#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
typedef double db;
const db eps=1e-8;
inline int sign(db k1){
	if (k1<-eps) return -1; else if (k1>eps) return 1; else return 0;
}
struct point{
	db x,y;
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	point operator / (const db& k1)const{return (point){x/k1,y/k1};}
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	bool operator == (const point& k1)const{}
	point turn90(){return (point){-y,x};}
	point unit(){return (point){x/abs(),y/abs()};}
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
inline db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
inline db dot(point k1,point k2){return k1.x*k2.x+k1.y*k2.y;}
point intersect(point k1,point v,point k2,point w){
	db x=cross(w,k1-k2)/cross(v,w);
	return k1+v*x;
}
point project(point p,point k1,point v){
	db x=dot(v,p-k1)/dot(v,v);
	return k1+v*x;
}
db distanceToLine(point p,point k1,point v){
	return fabs(cross(v,p-k1))/v.abs();
}
void getConvexhull(vector<point> P,vector<point> &sol){
	int n=P.size(),m=0,k=0;
	sort(P.begin(),P.end());
	rep (i,0,n-1){
		while (m>1&&sign(cross(sol[m-1]-sol[m-2],P[i]-sol[m-2]))<=0) m--,sol.pop_back();
		sol.push_back(P[i]),m++;
	}
	k=m;
	per (i,n-2,0){
		while (m>k&&sign(cross(sol[m-1]-sol[m-2],P[i]-sol[m-2]))<=0) m--,sol.pop_back();
		sol.push_back(P[i]),m++;
	}
	if (n>1) m--,sol.pop_back();
}
point Ans[4];
db area;
void getAns(vector<point> P){
	int n=P.size();P.push_back(P[0]);
//	rep (i,0,n-1)P[i].print(),puts("");
	area=1e18;
	int l=1,r=1,u=1;
	rep (i,0,n-1){
		if (i==0) l=n-1;
		while (dot(P[i+1]-P[i],P[l]-P[i])>dot(P[i+1]-P[i],P[l+1]-P[i]))
			l=(l+1)%n;
		while (dot(P[i+1]-P[i],P[r]-P[i])<dot(P[i+1]-P[i],P[r+1]-P[i]))
			r=(r+1)%n;
		while (cross(P[i+1]-P[i],P[u]-P[i])<cross(P[i+1]-P[i],P[u+1]-P[i]))
			u=(u+1)%n;
		point A=project(P[l],P[i],P[i+1]-P[i]),B=project(P[r],P[i],P[i+1]-P[i]);
		point v=(P[i+1]-P[i]).turn90().unit();	
		db w=(B-A).abs(),h=distanceToLine(P[u],P[i],P[i+1]-P[i]);
		point C=B+v*h,D=A+v*h;
		if (w*h<area){
			/*
			puts("For points:");
			P[l].print(),putchar(' '),P[r].print(),putchar(' '),P[u].print(),puts("");
			P[i].print(),putchar(' '),P[i+1].print(),puts("");
			puts("got Rect:");
			A.print(),putchar(' '),B.print(),puts("");
			C.print(),putchar(' '),D.print(),puts(""),puts("");
			*/
			area=w*h;
			Ans[0]=A,Ans[1]=B;
			Ans[2]=C,Ans[3]=D;
		}
	}
}
vector<point> P,CH;
int main(){
	int n;scanf("%d",&n);
	P.resize(n);
	rep (i,0,n-1)P[i].scan();
	getConvexhull(P,CH);
	getAns(CH);
	db miny=1e18;int st=0;
	rep (i,0,3) if (Ans[i].y<miny)miny=Ans[i].y,st=i;
	printf("%.5f\n",area);
	rep (i,0,3){
		db x=Ans[(i+st)%4].x,y=Ans[(i+st)%4].y;
		if (fabs(x)<eps) x=0;
		if (fabs(y)<eps) y=0;
		printf("%.5f %.5f\n",x,y);
	}
	return 0;
}
/*
6 
1.0 3.00000
1 4.00000
2.0000 1
3 0.0000
3.00000 6
6.0 3.0
*/








