#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;++i)
#define per(i,a,n) for (int i=n-1;i>=a;--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=3e5+10;
const db eps=1e-10;
inline int sign(db a) {return a<-eps?-1:a>eps;}

struct Pnt {
	db x,y;
	inline db abs2() {return x*x+y*y;}
	bool operator<(Pnt o)const {return x<o.x||(x==o.x&&y<o.y);}
};

Pnt operator+(Pnt A,Pnt B) {return (Pnt){A.x+B.x,A.y+B.y};}
Pnt operator-(Pnt A,Pnt B) {return (Pnt){A.x-B.x,A.y-B.y};}
inline db cross(Pnt A,Pnt B) {return A.x*B.y-A.y*B.x;}

namespace Compare {
	Pnt bas;
	inline bool cmp(Pnt A,Pnt B) {
		Pnt v=A-bas,w=B-bas;
		return sign(cross(v,w))==0?v.abs2()<w.abs2():sign(cross(v,w))>0;
	}
	void init(Pnt o) {bas=o;}
}
using Compare::cmp;

void ConvexHull(Pnt *ps,int &n) {
	static Pnt stk[N]; int top=0;
	rep(i,1,n) if (ps[i]<ps[0]) swap(ps[i],ps[0]);
	Compare::init(ps[0]);
	sort(ps+1,ps+n,cmp);
	rep(i,0,n) {
		while (top>=2&&sign(cross(ps[i]-stk[top-1],stk[top]-stk[top-1]))>=0)
			--top;
		stk[++top]=ps[i];
	} 
	n=top; rep(i,0,n) ps[i]=stk[i+1];
}

namespace Minkowski {
	Pnt mink[N],A[N],B[N];
	int n,m,tot;
	void init(Pnt *ps,int n1,Pnt *qs,int m1) {
		n=n1,m=m1;
		rep(i,0,n) A[i]=ps[i];
		rep(i,0,m) B[i]=qs[i];
		// cout<<"FFF"<<endl;
		// rep(i,0,n) printf("%f %f\n",A[i].x,A[i].y);
		// rep(i,0,m) printf("%f %f\n",B[i].x,B[i].y);
		// cout<<"GGG"<<endl;
	}
	void solve() {
		int p1=0,p2=0;
		mink[0]=A[0]+B[0],tot=0;
		static Pnt tA[N],tB[N];
		rep(i,0,n) tA[i]=A[i]; rep(i,0,m) tB[i]=B[i];
		rep(i,0,n) A[i]=tA[(i+1)%n]-tA[i];
		rep(i,0,m) B[i]=tB[(i+1)%m]-tB[i];
		while (p1<n&&p2<m) {
			if (sign(cross(A[p1],B[p2]))>=0) ++tot,mink[tot]=mink[tot-1]+A[p1++];
			else ++tot,mink[tot]=mink[tot-1]+B[p2++];
		}
		while (p1<n) tot++,mink[tot]=mink[tot-1]+A[p1++];
		while (p2<m) tot++,mink[tot]=mink[tot-1]+B[p2++];
		++tot;
		ConvexHull(mink,tot);
	}
}
using Minkowski::mink;
using Minkowski::tot;

inline bool check(Pnt p) {
	if (sign(cross(p-mink[0],mink[1]-mink[0]))>0||sign(cross(p-mink[0],mink[tot-1]-mink[0]))<0)
		return 0;
	Pnt o=mink[0];
	int l=1,r=tot-1,at=-1;
	while (l<=r) {
		int mid=(l+r)>>1;
		if (sign(cross(mink[mid]-o,p-o))>=0) at=mid,l=mid+1;
		else r=mid-1;
	}
	int nxt=(at+1)%tot;
	if (sign(cross(mink[nxt]-mink[at],p-mink[at]))<0) return 0;
	else return 1;
}

int n,m,Q;
Pnt A[N],B[N];

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&Q);
	rep(i,0,n) scanf("%lf%lf",&A[i].x,&A[i].y);
	rep(i,0,m) scanf("%lf%lf",&B[i].x,&B[i].y),B[i].x=-B[i].x,B[i].y=-B[i].y;
	ConvexHull(A,n),ConvexHull(B,m);
	Minkowski::init(A,n,B,m);
	Minkowski::solve();
	// rep(i,0,tot) cout<<mink[i].x<<" "<<mink[i].y<<endl; cout<<endl;
	while (Q--) {
		Pnt p; scanf("%lf%lf",&p.x,&p.y);
		puts(check(p)?"1":"0");
	}
	return 0;
}