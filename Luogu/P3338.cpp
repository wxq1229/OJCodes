#include <bits/stdc++.h>
using namespace std;
#define sqr(x) ((x)*(x))
typedef double db;
const int N=4e5+10;
const db PI=acos(-1.0);
struct cpl{
	db x,y;
	cpl operator + (cpl k1)const{return (cpl){x+k1.x,y+k1.y};}
	cpl operator - (cpl k1)const{return (cpl){x-k1.x,y-k1.y};}
	cpl operator * (cpl k1)const{return (cpl){x*k1.x-y*k1.y,x*k1.y+y*k1.x};}
}F[N],G[N],H[N];
int rev[N];
void fft(cpl *f,int n,int k1){
	for (int i=0;i<n;i++) if(i<rev[i]) swap(f[i],f[rev[i]]);
	for (int len=2;len<=n;len<<=1){
		cpl w1=(cpl){cos(2*PI/len),sin(2*PI/len)*k1};
		for (int i=0;i<n;i+=len){
			cpl w=(cpl){1,0};
			for (int j=i;j<i+(len>>1);j++){
				cpl tmp=w*f[j+(len>>1)];
				f[j+(len>>1)]=f[j]-tmp;
				f[j]=f[j]+tmp;
				w=w*w1;
			}
		}
	}
}
db q[N],p[N],rq[N],a[N],b[N];
int main(){
	int n; scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lf",&q[i]);
	for (int i=1;i<=n;i++) rq[i]=q[n-i+1],p[i]=1.0/(db)i/(db)i;
	int limit=1; while (limit<=n*2)limit<<=1;
	for (int i=0;i<limit;i++) rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
	for (int i=0;i<limit;i++) F[i].x=q[i],G[i].x=rq[i],H[i].x=p[i];
	fft(F,limit,1),fft(G,limit,1),fft(H,limit,1);
	for (int i=0;i<limit;i++) F[i]=F[i]*H[i],G[i]=G[i]*H[i];
	fft(F,limit,-1),fft(G,limit,-1);
	for (int i=0;i<limit;i++) F[i].x/=limit,G[i].x/=limit;
	for (int i=1;i<=n;i++) printf("%.3f\n",F[i].x-G[n-i+1].x);
	return 0;
}
