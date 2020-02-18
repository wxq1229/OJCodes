#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef double db;
const db eps=1e-9;
inline int sign(db a)
{return a<-eps?-1:a>eps;}
struct point
{
    db x,y;
    point(db xx=0,db yy=0):x(xx),y(yy){}
    db abs2(){return x*x+y*y;}
    db abs(){return sqrt(abs2());}
    int quad()const
    {
    	return sign(y)==-1||(sign(y)==0&&sign(x)==-1);
    }
    void scan()
    {scanf("%lf%lf",&x,&y);}
    void print(char ch=' ')
    {
        printf("%.4f %.4f",x,y);
        putchar(ch);
    }
};
point operator + (point a,point b){return (point){a.x+b.x,a.y+b.y};}
point operator - (point a,point b){return (point){a.x-b.x,a.y-b.y};}
point operator * (point a,db x){return (point){a.x*x,a.y*x};}
point operator / (point a,db x){return (point){a.x/x,a.y/x};}
db operator * (point a,point b){return a.x*b.y-a.y*b.x;}
db operator ^ (point a,point b){return a.x*b.x+a.y*b.y;}
bool operator < (point a,point b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
typedef vector<point> polygon;
db area(polygon P)
{
    int n=P.size(); db ret=0.0;
    for(int i=0;i<n;i++) ret+=P[i]*P[(i+1)%n];
    return ret/2.0;
}
point intersect(point A,point B,point C,point D)
{
    point u=A-C,v=B-A,w=D-C; db x=(w*u)/(v*w);
    return A+v*x;
}
bool cmpang(point a,point b)
{
    if(a.quad()!=b.quad()) return a.quad()<b.quad();
    else return sign(a*b)>0;
}
struct line
{
    point p[2];
    line(point A,point B)
    {p[0]=A,p[1]=B;}
    line(){}
    point &operator [] (int i){return p[i];}
    point dir(){return p[1]-p[0];}
    int include(point P){return sign((p[1]-p[0])*(P-p[0]))>0;}
    void print()
    {
        p[0].print(' '),p[1].print('\n');
    }
};
point intersect(line a,line b){return intersect(a[0],a[1],b[0],b[1]);}
bool parellel(line a,line b){return sign(a.dir()*b.dir())==0;}
bool samed(line a,line b)
{return parellel(a,b)&&sign(a.dir()^b.dir())>0;}
bool operator < (line a,line b)
{
    if(samed(a,b)) return b.include(a[0]);
    else return cmpang(a.dir(),b.dir());
}
int getHPI(vector<line> L,polygon &H)
{
    #define chkL(l,a,b) (l.include(intersect(a,b)))
    int n=L.size(); H.clear();
    static deque<line> q; q.clear();
    sort(L.begin(),L.end());
    for(int i=0;i<n;i++)
    {
        if(i&&samed(L[i],L[i-1])) continue;
        while(q.size()>1&&!chkL(L[i],q[q.size()-1],q[q.size()-2])) q.pop_back();
        while(q.size()>1&&!chkL(L[i],q[0],q[1])) q.pop_front();
        q.pb(L[i]);
    }
    while(q.size()>2&&!chkL(q[0],q[q.size()-1],q[q.size()-2]))
        q.pop_back();
    while(q.size()>2&&!chkL(q[q.size()-1],q[0],q[1]))
        q.pop_front();
    if(q.size()==0) return 1; if(q.size()<=2) return -1;
    int m=q.size();
    for(int i=0;i<m;i++) H.pb(intersect(q[i],q[(i+1)%m]));
    return 1;
}
vector<line> L;
polygon P,H;
int main()
{
    int _;scanf("%d",&_);while(_--)
    {
        int n;scanf("%d",&n);
        P.resize(n);
        for(int i=0;i<n;i++) P[i].scan();
        for(int i=0;i<n;i++) L.pb(line(P[i],P[(i+1)%n]));
    }
    getHPI(L,H);
    printf("%.3f\n",area(H));
    return 0;
}
