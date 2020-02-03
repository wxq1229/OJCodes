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
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
inline db cross(point k1,point k2){return k1.x*k2.y-k1.y*k2.x;}
inline db dot(point k1,point k2){return k1.x*k2.x+k1.y*k2.y;}
void getConvexhull(vector<point>P,vector<point> &sol){
	int n=P.size(),m=0,k=0;
	sort(P.begin(),P.end());sol.clear();
	rep (i,0,n-1){
		while (m>1&&sign(cross(sol[m-1]-sol[m-2],P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		sol.push_back(P[i]),m++;
	}
	k=m;
	per (i,n-2,0){
		while (m>k&&sign(cross(sol[m-1]-sol[m-2],P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		sol.push_back(P[i]),m++;
	}
	if (n>1) m--,sol.pop_back();
}
db solve(vector<point>P){
	int n=P.size();P.push_back(P[0]);
	db ans=0.0;
	rep (i,0,n-1){
		int k1=(i+1)%n,k2=(i+3)%n;
		rep (j,(i+2)%n,n-1){
			while ((k1+1)%n!=j&&cross(P[i]-P[j],P[k1]-P[j])<cross(P[i]-P[j],P[k1+1]-P[j]))
				k1=(k1+1)%n;
			while ((k2+1)%n!=i&&cross(P[k2]-P[j],P[i]-P[j])<cross(P[k2+1]-P[j],P[i]-P[j]))
				k2=(k2+1)%n;
			ans=max(ans,cross(P[i]-P[j],P[k1]-P[j])+cross(P[k2]-P[j],P[i]-P[j]));
		}
	}
	return ans/2.0;
}
vector<point>P,ch;
int main(){
	int n;scanf("%d",&n);
	rep (i,1,n){point tmp;tmp.scan(),P.push_back(tmp);}
	getConvexhull(P,ch);
	printf("%.3f\n",solve(ch));
	return 0;
}
/*
5
0 0
1 0
1 1 
0 1
0.5 0.5












*/

