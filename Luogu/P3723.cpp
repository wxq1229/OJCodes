#include <bits/stdc++.h>
using namespace std;
#define sqr(x) ((x)*(x))
const int N=2e6+10;
typedef double db;
typedef long long ll;
const ll INF=1e18;
const db PI=acos(-1.0);
struct cpl{
	db x,y;
	cpl operator + (cpl k1)const{return (cpl){x+k1.x,y+k1.y};}
	cpl operator - (cpl k1)const{return (cpl){x-k1.x,y-k1.y};}
	cpl operator * (cpl k1)const{return (cpl){x*k1.x-y*k1.y,x*k1.y+y*k1.x};}
};
int rev[N];
void fft(cpl *f,int n,int k1){
	for (int i=0;i<n;i++) if (i<rev[i]) swap(f[rev[i]],f[i]);
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
cpl f[N],g[N];
ll s[N];
int main(){
	int n,m; scanf("%d%d",&n,&m);
	ll a1=0,a2=0,b1=0,b2=0;
	for (int i=1;i<=n;i++) scanf("%lf",&f[i].x),a1+=f[i].x,a2+=sqr(f[i].x);
	for (int i=1;i<=n;i++) scanf("%lf",&g[i].x),b1+=g[i].x,b2+=sqr(g[i].x);
	reverse(f+1,f+n+1);
	for (int i=1;i<=n;i++) g[i+n]=g[i];
	int limit=1; for (;limit<=n*3;limit<<=1);
	for (int i=0;i<limit;i++) rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
	fft(f,limit,1),fft(g,limit,1);
	for (int i=0;i<limit;i++) f[i]=f[i]*g[i];
	fft(f,limit,-1);
	for (int i=0;i<limit;i++) s[i]=(ll)(f[i].x/limit+0.5);
	ll ans=INF;
	for (int c=-m;c<=m;c++)
		for (int k=0;k<n;k++)
			ans=min(ans,sqr(c)*n+a2+b2+2ll*c*(a1-b1)-2ll*s[n+k+1]);
	printf("%lld\n",ans);
	return 0;
}
