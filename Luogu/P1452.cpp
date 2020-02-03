#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for(int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for(int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define fi first
#define second se
typedef double db;
typedef pair<int,int> pii;
typedef long long ll;

const db eps=1e-10;
inline int sign(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	bool operator == (const point& k1)const{return sign(x-k1.x)==0&&sign(y-k1.y)==0;}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	db operator ^ (const point& k1)const{return x*k1.x+y*k1.y;}
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};

void getconvexhull(vector<point>P,vector<point>&sol){
	int n=P.size(),m=0;
	sort(P.begin(),P.end());
	rep(i,0,n-1){
		while(m>1&&sign((sol[m-1]-sol[m-2])*(P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		sol.push_back(P[i]);m++;
	}
	int tmp=m;
	per(i,n-2,0){
		while(m>tmp&&sign((sol[m-1]-sol[m-2])*(P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		sol.push_back(P[i]);m++;
	}
	if(n>1)m--,sol.pop_back();
}
db solve(vector<point>P){
	int n=P.size();db res=0.0;
	if(n==2)return (P[1]-P[0]).abs2();
	int j=2;P.push_back(P[0]);
	rep(i,0,n-1){
		while((P[i+1]-P[i])*(P[j]-P[i])<(P[i+1]-P[i])*(P[j+1]-P[i]))
			j=(j+1)%n;
		res=max(res,max((P[j]-P[i]).abs2(),(P[j]-P[i+1]).abs2()));
	}
	return res;
}

vector<point>P,ch;
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	int n;scanf("%d",&n);
	rep(i,1,n){point p;p.scan();P.push_back(p);}
	getconvexhull(P,ch);
	db ans=solve(ch);
	printf("%.0f\n",ans);
	return 0;
}

/*
4
0 0
0 1
1 1
1 0
*/
