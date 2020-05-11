#include <bits/stdc++.h>
using namespace std;
#define N 1111111
#define MOD 998244353
inline int qpow(int a,int b=MOD-2,int m=MOD)
{
	int ans=1%m;
	for(;b;b>>=1,a=1ll*a*a%m)
		if(b&1) ans=1ll*ans*a%m;
	return ans;
}
const int gn=3,ign=qpow(gn);
namespace FFT {int r[N];}
inline int glim(int n)
{
	int lim=1;
	while(lim<=n) lim<<=1;
	return lim;
}
void fftinit(int n)
{
	using namespace FFT;
	for(int i=0;i<n;i++) r[i]=r[i>>1]>>1|((i&1)?n>>1:0);
}
void fft(int *f,int n,int flg)
{
	using namespace FFT;
	for(int i=0;i<n;i++) if(r[i]<i) swap(f[i],f[r[i]]);
	for(int len=2,k=1;len<=n;len<<=1,k<<=1)
	{
		int wn=qpow(flg==1?gn:ign,(MOD-1)/len);
		for(int i=0;i<n;i+=len)
			for(int j=i,w=1;j<i+k;j++,w=1ll*w*wn%MOD)
			{
				int tmp=1ll*f[j+k]*w%MOD;
				f[j+k]=f[j]-tmp<0?f[j]-tmp+MOD:f[j]-tmp;
				f[j]=f[j]+tmp>=MOD?f[j]+tmp-MOD:f[j]+tmp;
			}
	}
	if(flg==-1)
	{
		int inv=qpow(n);
		for(int i=0;i<n;i++) f[i]=1ll*f[i]*inv%MOD;
	}
}
namespace PolyMul {int f[N],g[N];}
struct poly
{
	vector<int> a;
	inline int size() const {return a.size();}
	inline int deg() const {return size()-1;}
	inline int operator [] (int i) const {return i>=size()?0:a[i];}
	inline int &operator [] (int i) {assert(i<size());return a[i];}
	poly(int n=0,int v=0) {a=vector<int>(n,v);}
	void resize(int n) {a.resize(n);}
	void debug()
	{
		for(int i=0;i<size();i++) printf("%d%c",a[i]," \n"[i==size()-1]);
	}
};
poly operator * (const poly &a,const poly &b)
{
	using namespace PolyMul;
	int n=a.deg(),m=b.deg(),lim=glim(n+m);
	fftinit(lim);
	for(int i=0;i<lim;i++) f[i]=a[i],g[i]=b[i];
	fft(f,lim,1),fft(g,lim,1);
	for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%MOD;
	fft(f,lim,-1);
	poly c(n+m+1);
	for(int i=0;i<c.size();i++) c[i]=f[i];
	return c;
}
poly a[N];
poly solve(int l,int r)
{
	if(l==r) return a[l];
	int mid=(l+r)>>1;
	return solve(l,mid)*solve(mid+1,r);
}
poly s1;
int ifac[N],fac[N];
int comb(int n,int r) {return 1ll*fac[n]*ifac[r]%MOD*ifac[n-r]%MOD;}
int main()
{
	int n,A,B;
	scanf("%d%d%d",&n,&A,&B);
	if(A+B-2>n-1||(!A)||(!B)) {puts("0");return 0;}
	if(n==1){puts("1");return 0;}
	fac[0]=ifac[0]=1;
	for(int i=1;i<=200000;i++) fac[i]=1ll*fac[i-1]*i%MOD,ifac[i]=qpow(fac[i]);
	for(int i=1;i<=n-1;i++)
	{
		a[i]=poly(2);
		a[i][0]=i-1,a[i][1]=1;
	}
	s1=solve(1,n-1);
	printf("%d\n",1ll*s1[A+B-2]*comb(A+B-2,A-1)%MOD);
	return 0;
}
