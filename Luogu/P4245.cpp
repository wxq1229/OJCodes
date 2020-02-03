#include <bits/stdc++.h>
using namespace std;
typedef long double db;
typedef long long ll;
const db PI=acos(-1.0);
const int N=3e5+10;
struct cpl{
	db x,y;
	cpl operator + (cpl k1)const{return (cpl){x+k1.x,y+k1.y};}
	cpl operator - (cpl k1)const{return (cpl){x-k1.x,y-k1.y};}
	cpl operator * (cpl k1)const{return (cpl){x*k1.x-y*k1.y,x*k1.y+y*k1.x};}
};
int rev[N];
void fft(cpl *f,int n,int k1){
	for (int i=0;i<n;i++)
		if (rev[i]<i)swap(f[i],f[rev[i]]);
	for (int len=2;len<=n;len<<=1){
		cpl wn=(cpl){cos(2*PI/len),k1*sin(2*PI/len)};
		for (int i=0;i<n;i+=len){
			cpl w=(cpl){1,0};
			for (int j=i;j<i+(len>>1);j++){
				cpl tmp=w*f[j+(len>>1)];
				f[j+(len>>1)]=f[j]-tmp;
				f[j]=f[j]+tmp;
				w=w*wn;
			}
		}
	}
}
cpl f[2][N],g[2][N],ans[3][N];
#define normal(x) (((ll)(x/limit+0.5)%mod+mod)%mod)
void mtt(int *a,int n,int *b,int m,int mod){
	int limit=1; while (limit<=n+m)limit<<=1;
	for (int i=0;i<limit;i++) rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
	for (int i=0;i<limit;i++){
		f[0][i].x=a[i]>>15;f[1][i].x=a[i]&0x7fff;
		g[0][i].x=b[i]>>15;g[1][i].x=b[i]&0x7fff;
	}
	fft(f[0],limit,1),fft(f[1],limit,1);
	fft(g[0],limit,1),fft(g[1],limit,1);
	for (int i=0;i<limit;i++){
		ans[0][i]=f[0][i]*g[0][i];
		ans[1][i]=f[0][i]*g[1][i]+f[1][i]*g[0][i];
		ans[2][i]=f[1][i]*g[1][i];
	}
	fft(ans[0],limit,-1),fft(ans[1],limit,-1),fft(ans[2],limit,-1);
	for (int i=0;i<=n+m;i++){
		ll k1=(normal(ans[0][i].x)<<30ll)%mod;
		ll k2=(normal(ans[1][i].x)<<15ll)%mod;
		ll k3=normal(ans[2][i].x)%mod;
		printf("%d ",((k1+k2)%mod+k3)%mod);
	}
}
int n,m,a[N],b[N],mod;
int main(){
#ifdef WXQ
	freopen("A.in","r",stdin);
#endif
	scanf("%d%d%d",&n,&m,&mod);
	for (int i=0;i<=n;i++)scanf("%d",&a[i]);
	for (int i=0;i<=m;i++)scanf("%d",&b[i]);
	mtt(a,n,b,m,mod);
	return 0;
}
