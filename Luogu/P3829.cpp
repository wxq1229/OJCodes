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

const db PI=acos(-1.0);
const db eps=1e-10;
inline int sign(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	bool operator == (const point& k1)const{return sign(x-k1.x)==0&&sign(y-k1.y)==0;}
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	point operator / (const db& k1)const{return (point){x/k1,y/k1};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	db operator ^ (const point& k1)const{return x*k1.x+y*k1.y;}
	point turn(const db& k1){return (point){cos(k1)*x-sin(k1)*y,sin(k1)*x+cos(k1)*y};}
	db abs2(){return x*x+y*y;}
	db abs(){return sqrt(abs2());}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("(%.7f %.7f)",x,y);}
};
typedef point vec;

const int MAXN=50010;
point ch[MAXN],P[MAXN];
int main(){
	int n; db a,b,r;
	scanf("%d%lf%lf%lf",&n,&a,&b,&r);
	a/=2.0,b/=2.0;
	int cnt=0;
	rep(i,1,n){
		point p;db ang;
		p.scan(),scanf("%lf",&ang);
		P[++cnt]=p+(vec){b-r,a-r}.turn(ang);
		P[++cnt]=p+(vec){-(b-r),a-r}.turn(ang);
		P[++cnt]=p+(vec){-(b-r),-(a-r)}.turn(ang);
		P[++cnt]=p+(vec){b-r,-(a-r)}.turn(ang);
	}
	sort(P+1,P+cnt+1);
	int now=0;
	rep(i,1,cnt){
		while(now>1&&sign((ch[now]-ch[now-1])*(P[i]-ch[now-1]))<=0)now--;
		ch[++now]=P[i];
	}
	int tmp=now;
	per(i,cnt-1,1){
		while(now>tmp&&sign((ch[now]-ch[now-1])*(P[i]-ch[now-1]))<=0)now--;
		ch[++now]=P[i];
	}
	ch[now+1]=ch[1];
//	rep(i,1,now)ch[i].print(),putchar(' ');
//	putchar('\n');
	db ans=0;
	rep(i,1,now)
		ans+=(ch[i+1]-ch[i]).abs();
	ans+=2*PI*r;
	printf("%.2f\n",ans);
	return 0;
}
/*
2
6.0 2.0 0.0
0.0 0.0 0.0
2.0 -2.0 1.5707963268
*/
/*
3
6.0 6.0 1.0
4.0 4.0 0.0
0.0 8.0 0.0
0.0 0.0 0.0
*/
/*
3
6.0 6.0 1.0
4.0 4.0 0.1745329252
0.0 8.0 0.3490658504
0.0 0.0 0.5235987756
*/

