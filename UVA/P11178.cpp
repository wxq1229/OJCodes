#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;
const db eps=1e-8;
inline int sgn(db x){return fabs(x)<eps?0:(x<0?-1:0);}
struct point{
	db x,y;
	void read(){scanf("%lf%lf",&x,&y);}
	void write(char end=0){printf("%.6f %.6f",x,y);putchar(end);}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	point operator / (const db& k1)const{return (point){x/k1,y/k1};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	db operator ^ (const point& k1)const{return x*k1.x+y*k1.y;}
};
typedef point vec;
db length(vec v){return sqrt(v^v);}
point turn(point k1,db a){return (point){cos(a)*k1.x-sin(a)*k1.y,sin(a)*k1.x+cos(a)*k1.y};}
point lineintersection(point P,vec v,point Q,vec w){
	vec u=P-Q;
	db t=w*u/(v*w);
	return P+v*t;
}
db angle(vec v1,vec v2){return acos((v1^v2)/length(v1)/length(v2));}
point getpoint(point A,point B,point C){
	vec v1=C-B;db a1=angle(A-B,v1);
	v1=turn(v1,a1/3);
	vec v2=B-C;db a2=angle(A-C,v2);
	v2=turn(v2,-a2/3);
	return lineintersection(B,v1,C,v2);
}
int main(){
	int T;
	for(scanf("%d",&T);T;T--){
		point A,B,C,D,E,F;
		A.read(),B.read(),C.read();
		D=getpoint(A,B,C);
		E=getpoint(B,C,A);
		F=getpoint(C,A,B);
		D.write(' ');E.write(' ');F.write('\n');
	}
	return 0;
}
