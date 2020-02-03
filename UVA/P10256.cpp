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
	bool operator == (const point& k1)const{return sign(x-k1.x)==0&&sign(y-k1.x)==0;}
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	point operator + (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
inline db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
inline db dot(point k1,point k2){return k1.x*k2.x+k1.y*k1.y;}
bool segmentProperIntersect(point k1,point k2,point k3,point k4){
	db c1=sign(cross(k2-k1,k3-k1)),c2=sign(cross(k2-k1,k4-k1));
	db c3=sign(cross(k4-k3,k2-k3)),c4=sign(cross(k4-k3,k1-k3));
	return c1*c2<0&&c3*c4<0;
}
bool onSegment(point p,point k1,point k2){
	return sign(cross(k1-p,k2-p))==0&&sign(dot(k1-p,k2-p))<0;
}
int inPolygon(point p,vector<point>P){
	int n=P.size();P.push_back(P[0]);
	int cnt=0;
	rep (i,0,n-1){
		if (onSegment(p,P[i],P[i+1])) return -1;
		int k=sign(cross(P[i+1]-P[i],p-P[i])),d1=sign(P[i].y-p.y),d2=sign(P[i+1].y-p.y);
		if (k>0&&d1<=0&&d2>0) cnt++;
		if (k<0&&d2<=0&&d1>0) cnt--;
	}
	return cnt!=0;
}
void getConvexhull(vector<point>P,vector<point> &sol){
	int n=P.size(),m=0,k;
	sol.clear();
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
	if (n>1) sol.pop_back(),m--;
}
vector<point> P1,P2,ch1,ch2;
int main(){
	int n,m;
	while (scanf("%d%d",&n,&m)&&n&&m){
		P1.clear(),P2.clear();
		rep (i,1,n){point tmp;tmp.scan(),P1.push_back(tmp);}
		rep (i,1,m){point tmp;tmp.scan(),P2.push_back(tmp);}
		if (n==1&&m==1){
			if (P1[0]==P2[0]) puts("No"); else puts("Yes");
			continue;
		}
		getConvexhull(P1,ch1);
		getConvexhull(P2,ch2);
		int ret=1;
		int n1=ch1.size(),n2=ch2.size();
		rep (i,0,n1-1)
			if (inPolygon(ch1[i],ch2)){ret=0;break;}
		if (!ret){puts("No");continue;}
		rep (i,0,n2-1)
			if (inPolygon(ch2[i],ch1)){ret=0;break;}
		if (!ret){puts("No");continue;}
		ch1.push_back(ch1[0]);ch2.push_back(ch2[0]);
		rep (i,0,n1-1) {
			rep (j,0,n2-1)
				if (segmentProperIntersect(ch1[i],ch1[i+1],ch2[j],ch2[j+1])){
					ret=0;break;
				}
			if (!ret)break;
		}
		puts(ret?"Yes":"No");
	}
	return 0;
}
/*
4 3
100 600
200 400
600 500
300 700
400 100
600 200
500 300
4 3
100 600
400 100
600 200
500 300
200 400
600 500
300 700
0 0










*/

