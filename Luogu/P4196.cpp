#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
typedef double db;
const db eps=1e-8;
int sign(db k1){
	if (k1<-eps) return -1; else if (k1>eps) return 1; else return 0;
}
struct point{
	db x,y;
	point operator + (point k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (point k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (db k1)const{return (point){x*k1,y*k1};}
	point operator / (db k1)const{return (point){x/k1,y/k1};}
	int getP()const{
		return sign(y)==-1||(sign(y)==0&&sign(x)==-1);
	}
	void print(){printf("%.3f %.3f",x,y);}
	void scan(){scanf("%lf%lf",&x,&y);}
};
db dot(point k1,point k2){
	return k1.x*k2.x+k1.y*k2.y;
}
db cross(point k1,point k2){
	return k1.x*k2.y-k1.y*k2.x;
}
point getLL(point k1,point k2,point k3,point k4){
	point v=k2-k1,w=k4-k3;return k1+v*(cross(w,k1-k3)/cross(v,w));
}
int compareangle(point k1,point k2){
	return k1.getP()<k2.getP()||(k1.getP()==k2.getP()&&sign(cross(k1,k2))>0);
}
struct line{
	point p[2];
	line(){}
	line(point k1,point k2){p[0]=k1; p[1]=k2;}
	point &operator [] (int k1){return p[k1];}
	point dir(){return p[1]-p[0];}
	int include(point k1){
		return sign(cross(p[1]-p[0],k1-p[0]))>0;
	}
};
point getLL(line l1,line l2){
	return getLL(l1[0],l1[1],l2[0],l2[1]);
}
int parellel(line l1,line l2){
	return sign(cross(l1.dir(),l2.dir()))==0;
}
int sameDir(line l1,line l2){
	return parellel(l1,l2)&&sign(dot(l1.dir(),l2.dir()))==1;
}
int operator < (line l1,line l2){
	if (sameDir(l1,l2)) return l2.include(l1[0]); else return compareangle(l1.dir(),l2.dir());
}
int checkpos(line l1,line l2,line l3){
	return l3.include(getLL(l1,l2));
}
int getHPI(vector<line> L,vector<point>&H){
	int n=L.size(); H.clear();
	sort(L.begin(),L.end()); deque<line> q;
	for (int i=0;i<(int)L.size();i++){
		if (i&&sameDir(L[i],L[i-1])) continue;
		while (q.size()>1&&!checkpos(q[q.size()-2],q[q.size()-1],L[i])) q.pop_back();
		while (q.size()>1&&!checkpos(q[0],q[1],L[i])) q.pop_front();
		q.push_back(L[i]);
	}
	while (q.size()>2&&!checkpos(q[q.size()-2],q[q.size()-1],q[0])) q.pop_back();
	while (q.size()>2&&!checkpos(q[0],q[1],q[q.size()-1])) q.pop_front();
	if (q.size()==0) return 0; else if (q.size()<=2) return -1;
	for (int i=0;i<(int)q.size()-1;i++)
		H.push_back(getLL(q[i],q[i+1]));
	H.push_back(getLL(q[q.size()-1],q[0]));
	return 1;
}
db polygonarea(vector<point>A){
	int n=A.size(); db area=0.0;
//	for (int i=0;i<n;i++) A[i].print(),puts("");
	for (int i=1;i<(int)A.size()-1;i++)
		area+=cross(A[i]-A[0],A[i+1]-A[0]);
	return area/2.0;
}
vector<line> L;
vector<point> H;
int main(){
	int T; for (scanf("%d",&T);T;T--){
		int n; scanf("%d",&n);
		vector<point>P(n);
		for (int i=0;i<n;i++)P[i].scan();
		for (int i=0;i<n;i++)L.push_back(line(P[i],P[(i+1)%n]));
	}
	getHPI(L,H);
	printf("%.3f\n",polygonarea(H));
	return 0;
}









