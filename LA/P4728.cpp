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

const db eps=1e-10;
inline int sign(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	bool operator == (const point& k1)const{return sign(x-k1.x)==0&&sign(y-k1.y)==0;}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	db abs2(){return x*x+y*y;}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	void scan(){scanf("%lf%lf",&x,&y);}
};
typedef point vec;

void getconvexhull(vector<point>P,vector<point>&sol){
	sort(P.begin(),P.end());
	int n=unique(P.begin(),P.end())-P.begin(),m=0;
	rep(i,0,n-1){
		while(m>1&&sign((sol[m-1]-sol[m-2])*(P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		m++,sol.push_back(P[i]);
	}
	int tmp=m;
	per(i,n-2,0){
		while(m>tmp&&sign((sol[m-1]-sol[m-2])*(P[i]-sol[m-2]))<=0)m--,sol.pop_back();
		m++,sol.push_back(P[i]);
	}
	if(n>1)sol.pop_back(),m--;
}

db solve(vector<point>P){
	db ans=0.0;int n=P.size();
	if(n==2){return (P[1]-P[0]).abs2();}
	P.push_back(P[0]);int j=2;
	rep(i,0,n-1){
		while((P[i+1]-P[i])*(P[j]-P[i])<(P[i+1]-P[i])*(P[j+1]-P[i]))
			j=(j+1)%n;
		ans=max(ans,max((P[j]-P[i]).abs2(),(P[j]-P[i+1]).abs2()));
	}
	return ans;
}

int main(){
	int T;
	for(scanf("%d",&T);T;T--){
		int n;scanf("%d",&n);
		vector<point>P,ch;
		rep(i,1,n){
			point o;db w;
			o.scan();scanf("%lf",&w);
			P.push_back(o);P.push_back(o+(vec){w,0});
			P.push_back(o+(vec){0,w});P.push_back(o+(vec){w,w});
		}
		getconvexhull(P,ch);
		printf("%.0f\n",solve(ch));
	}
	return 0;
}
/*
2

3
0 0 1
1 0 2
0 0 1

6
2 1 2
1 4 2
3 2 3
4 4 4
6 5 1
5 1 3
*/

