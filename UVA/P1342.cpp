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
inline int sgn(db x){return fabs(x)<eps?0:(x<0?-1:1);}
struct point{
	db x,y;
	point operator + (const point& k1)const{return (point){x+k1.x,y+k1.y};}
	point operator - (const point& k1)const{return (point){x-k1.x,y-k1.y};}
	point operator * (const db& k1)const{return (point){x*k1,y*k1};}
	db operator * (const point& k1)const{return x*k1.y-y*k1.x;}
	db operator ^ (const point& k1)const{return x*k1.x+y*k1.y;}
	bool operator == (const point& k1)const{return sgn(x-k1.x)==0&&sgn(y-k1.y)==0;}
	bool operator < (const point& k1)const{return x<k1.x||(x==k1.x&&y<k1.y);}
	void scan(){scanf("%lf%lf",&x,&y);}
	void print(){printf("%.7f %.7f",x,y);}
};
typedef point vec;
point lineintersection(point A,vec v,point B,vec w){
	db x=w*(A-B)/(v*w);
	return A+v*x;
}
bool onsegment(point A,point B,point P){
	return sgn((A-P)*(B-P))==0&&sgn((A-P)^(B-P))<0;
}
bool segmentproperintersection(point A,point B,point C,point D){
	db t1=(A-B)*(C-A),t2=(A-B)*(D-A);
	db t3=(C-D)*(A-C),t4=(C-D)*(B-C);
	return sgn(t1)*sgn(t2)<0&&sgn(t3)*sgn(t4)<0;
}

const int MAXN=310;
point P[MAXN],V[MAXN*MAXN];
int main(){
	int n,kase=0;
	while(scanf("%d",&n)==1&&n){
		kase++;
		rep(i,1,n){
			P[i].scan();
			V[i]=P[i];
		}
		--n;
		int t1=n,t2=n;
		rep(i,1,n)rep(j,i+1,n)
			if(segmentproperintersection(P[i],P[i+1],P[j],P[j+1]))
				V[++t1]=lineintersection(P[i],P[i+1]-P[i],P[j],P[j+1]-P[j]);
		sort(V+1,V+t1+1);
		t1=unique(V+1,V+t1+1)-V-1;
		rep(i,1,n)rep(j,1,t1){
			if(onsegment(P[i],P[i+1],V[j])) t2++;
		}
		printf("Case %d: There are %d pieces.\n",kase,t2+2-t1);
	}
	return 0;
}
