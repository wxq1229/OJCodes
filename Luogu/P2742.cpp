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
inline int sgn(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	bool operator == (const point& k1)const{return sgn(x-k1.x)==0&&sgn(y-k1.y)==0;}
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	db operator ^ (const point& k1)const{return x*k1.x+y*k1.y;}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
const int MAXN=10010;
point P[MAXN],st[MAXN];
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n)P[i].scan();
	sort(P+1,P+n+1);
	int top=0;
	rep(i,1,n){
		while(top>1&&sgn((st[top]-st[top-1])*(P[i]-st[top-1]))<0)top--;
		st[++top]=P[i];
	}
	//puts("Now ST:");
	//rep(i,1,top)
	//	st[i].print(),putchar(' ');
	//putchar('\n');
	int k=top;
	per(i,n-1,1){
		while(top>k&&sgn((st[top]-st[top-1])*(P[i]-st[top-1]))<0)top--;
		st[++top]=P[i];
	}
	st[top+1]=st[1];
	//puts("Now ST:");
	//rep(i,1,top)
	//	st[i].print(),putchar(' ');
	//putchar('\n');
	db ans=0;
	rep(i,1,top)
		ans+=(st[i+1]-st[i]).abs();
	printf("%.2f\n",ans);
	return 0;
}
