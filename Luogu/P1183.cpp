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

const db eps=1e-8;
struct point{
	db x,y;
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	void scan(){scanf("%lf%lf",&x,&y);}
};
const int MAXN=1010;
point P[MAXN];
int main(){
	int n;scanf("%d",&n);
	rep(i,1,n)P[i].scan();
	db ans=0;
	rep(i,2,n-1)
		ans+=(P[i]-P[1])*(P[i+1]-P[1]);
	ans/=2;ans=fabs(ans);
	printf("%d\n",(int)ans);
	return 0;
}
