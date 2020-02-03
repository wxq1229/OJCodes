#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef double db;
const db eps=1e-8;
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
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	point turn90(){return (point){-y,x};}
	point turn90c(){return (point){y,-x};}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
inline db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
inline db dot(point k1,point k2){return k1.x*k2.x+k1.y*k2.y;}
point intersect(point k1,point v,point k2,point w){
	db x=cross(w,k1-k2)/cross(v,w);
	return k1+v*x;
}
struct circle{
	point c;
	db r;
	void print(){printf("%.2f %.2f %.2f",c.x,c.y,r);}
};
circle getCircle(point k1,point k2,point k3){
	point p1=(k1+k2)/2,p2=(k2+k3)/2;
	point p=intersect(p1,(k2-k1).turn90c(),p2,(k3-k2).turn90c());
	return (circle){p,(p-k1).abs()};
}
int inCircle(point p1,circle c1){
	return (p1-c1.c).abs()<=c1.r+eps;
}
void randomShuffle(vector<point> &P){
	int n=P.size();
	rep (i,0,n-1){
		int j=(rand()%n+i)%n;
		swap(P[i],P[j]);
	}
}
circle minCircleCover(vector<point>P){
	int n=P.size();
	randomShuffle(P);
	circle ans=(circle){(point){0,0},0};
	rep (i,0,n-1){
		if (!inCircle(P[i],ans)){
			ans=(circle){P[i],0};
			rep (j,0,i-1){
				if (!inCircle(P[j],ans)){
					ans=(circle){(P[i]+P[j])/2,(P[j]-P[i]).abs()/2};
					rep (k,0,j-1){
						if (!inCircle(P[k],ans))ans=getCircle(P[i],P[j],P[k]);
					}
				}
			}
		}
	}
	return ans;
}
vector<point>P;
int main(){
	srand(time(NULL));
	int n;scanf("%d",&n);
	P=vector<point>(n);
	rep (i,0,n-1)P[i].scan();
	circle ans=minCircleCover(P);
	ans.print();
	return 0;
}
/*
5
1.200 1.200
2.400 2.400
3.800 4.500
2.500 3.100
3.900 1.300
*/









