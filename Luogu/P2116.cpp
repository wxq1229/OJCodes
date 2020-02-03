#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef double db;
typedef long long ll;
typedef pair<int,int> pii;

const db eps=1e-9;
const db pi=acos(-1.0);
inline int sgn(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	point operator / (const db& k1)const{return (point){x/k1,x/k1};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	db operator ^ (const point& k1)const{return x*k1.x+y*k1.y;}
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	bool operator == (const point& k1)const{return sgn(x-k1.x)==0&&sgn(y-k1.y)==0;}
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	void scan(){scanf("%lf%lf",&x,&y);}
};
const int MAXN=1010;
point P[MAXN],st[MAXN];
int main(){
	db l;int n;
	scanf("%d%lf",&n,&l);
	rep(i,1,n)P[i].scan();
	sort(P+1,P+n+1);
	int top=0;
	rep(i,1,n){
		while(top>1&&sgn((st[top]-st[top-1])*(P[i]-st[top-1]))<0)top--;	
		st[++top]=P[i];
	}
	int backup=top;
	per(i,n-1,1){
		while(top>backup&&sgn((st[top]-st[top-1])*(P[i]-st[top-1]))<0)top--;
		st[++top]=P[i];
	}
	st[top+1]=st[1];
	db ans=0.0;
	rep(i,1,top)
		ans+=(st[i+1]-st[i]).abs();
	ans+=2*pi*l;
	printf("%.0f\n",ans);
	return 0;
}
