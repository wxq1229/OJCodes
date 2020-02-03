#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef double db;
const db eps=1e-9;
const db PI=acos(-1.0);
inline int sgn(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	point turn(const db& k1){return (point){cos(k1)*x-sin(k1)*y,sin(k1)*x+cos(k1)*y};}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("(%.8f,%.8f)",x,y);}
};
typedef point vec;
db torad(db a){return a/180*PI;}
db area(vector<point>P){
	int n=P.size();db ans=0.0;
	rep(i,1,n-2)
		ans+=(P[i]-P[0])*(P[i+1]-P[0]);
	return ans/2.0;
}
void getconvexhull(vector<point>P,vector<point>&sol){
	int n=P.size(),m=0;
	sort(P.begin(),P.end());
	rep(i,0,n-1){
		while(m>1&&sgn((sol[m-1]-sol[m-2])*(P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		sol.push_back(P[i]),m++;
	}
	int tmp=m;
	per(i,n-2,0){
		while(m>tmp&&sgn((sol[m-1]-sol[m-2])*(P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		sol.push_back(P[i]),m++;
	}
	if(n>1)m--,sol.pop_back();
}
int main(){
	int T;
	for(scanf("%d",&T);T;T--){
		int n;scanf("%d",&n);
		vector<point>P,ch;
		db s1=0.0,s2=0.0;
		rep(i,1,n){
			point o;db w,h,ang;
			o.scan(),scanf("%lf%lf%lf",&w,&h,&ang);
			ang=-torad(ang);s1+=w*h;
			w/=2.0,h/=2.0;
			P.push_back(o+(vec){w,h}.turn(ang));
			P.push_back(o+(vec){w,-h}.turn(ang));
			P.push_back(o+(vec){-w,h}.turn(ang));
			P.push_back(o+(vec){-w,-h}.turn(ang));
		}
		getconvexhull(P,ch);
		s2=area(ch);
		//printf("%f %f\n",s1,s2);
		printf("%.1f %%\n",s1*100/s2);
	}
	return 0;
}
/*
input:
1

4
4 7.5 6 3 0
8 11.5 6 3 0
9.5 6 6 3 90
4.5 3 4.4721 2.2361 26.565


convex hull:
(1.00000000,6.00000000)
(3.70144897,0.63097665)
(5.91612492,0.93977049)
(9.49677415,2.64589959)
(12.18521584,8.00987957)
(11.00000000,13.00000000)
(5.00000000,13.00000000)
(1.00000000,9.00000000)


*/
