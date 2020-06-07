#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,MOD=998244353;
inline int qpow(int a,int b=MOD-2,int m=MOD)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%m;
		a=1ll*a*a%m,b>>=1;
	}
	return ans;
}
const int gn=3,ign=qpow(gn);
namespace FFT {int r[N];}
inline int glim(int n)
{
	int lim=1; while(lim<=n) lim<<=1;
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
	for(int len=2;len<=n;len<<=1)
	{
		int k=len>>1,wn=qpow(flg==1?gn:ign,(MOD-1)/len);
		for(int i=0;i<n;i+=len)
			for(int w=1,j=i;j<i+k;j++,w=1ll*w*wn%MOD)
			{
				int tmp=1ll*f[j+k]*w%MOD,x=f[j]-tmp,y=f[j]+tmp;
				f[j+k]=x<0?x+MOD:x,f[j]=y>=MOD?y-MOD:y;
			}
	}
	if(flg==-1)
	{
		int inv=qpow(n);
		for(int i=0;i<n;i++) f[i]=1ll*f[i]*inv%MOD;
	}
}
void mult(const int *a,const int *b,int *c,int lim)
{
	static int f[N],g[N];
	for(int i=0;i<lim;i++) f[i]=a[i],g[i]=b[i];
	fftinit(lim);
	fft(f,lim,1),fft(g,lim,1);
	for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%MOD;
	fft(f,lim,-1);
	for(int i=0;i<lim;i++) c[i]=f[i];
}
void ginv(const int *f,int n,int *g)
{
	if(n==1) {g[0]=qpow(f[0]);return;}
	ginv(f,(n+1)>>1,g);
	static int tf[N]; int lim=glim((n-1)<<1);
	for(int i=0;i<lim;i++) tf[i]=i<n?f[i]:0,g[i]=i<n?g[i]:0;
	fftinit(lim);
	fft(tf,lim,1),fft(g,lim,1);
	for(int i=0;i<lim;i++) g[i]=1ll*g[i]*(2ll-1ll*tf[i]*g[i]%MOD+MOD)%MOD;
	fft(g,lim,-1);
	for(int i=n;i<lim;i++) g[i]=0;
}
void derv(const int *f,int n,int *g)
{
	for(int i=1;i<n;i++) g[i-1]=1ll*f[i]*i%MOD;
	g[n-1]=0;
}
void inte(const int *f,int n,int *g)
{
	for(int i=0;i<n;i++) g[i+1]=1ll*f[i]*qpow(i+1)%MOD;
	g[0]=g[n]=0;
}
void gln(const int *f,int n,int *g)
{
	static int inv[N],der[N],mt[N];
	int lim=glim((n-1)<<1);
	for(int i=0;i<lim;i++) mt[i]=inv[i]=der[i]=g[i]=0;
	ginv(f,n,inv),derv(f,n,der);
	mult(inv,der,mt,lim);
	inte(mt,n,g);
}
void gexp(const int *f,int n,int *g)
{
	if(n==1) {g[0]=1;return;}
	gexp(f,(n+1)>>1,g); int lim=glim((n-1)<<1);
	static int tf[N],lng[N];
	for(int i=0;i<lim;i++) lng[i]=0,tf[i]=i<n?f[i]:0,g[i]=i<n?g[i]:0;
	gln(g,n,lng);
	fftinit(lim);
	fft(tf,lim,1),fft(g,lim,1),fft(lng,lim,1);
	for(int i=0;i<lim;i++) g[i]=1ll*g[i]*(1ll-lng[i]+tf[i]+MOD)%MOD;
	fft(g,lim,-1);
	for(int i=n;i<lim;i++) g[i]=0;
}
struct poly
{
    vector<int> a;
    inline int operator[](int i)const {return a[i];}
    inline int &operator[](int i) {return a[i];}
    void init(int n=0,int v=0){a=vector<int>(n,v);}
    poly(int n=0,int v=0) {init(n,v);}
    inline int size()const {return a.size();}
    inline int deg()const {return size()-1;}
    template<typename T> poly getpoly(int n,T gt)
    {
        static int f[N],g[N];
        for(int i=0;i<n;i++) f[i]=a[i];
        gt(f,n,g); poly c(n);
        for(int i=0;i<n;i++) c[i]=g[i];
        return c;
    }
    poly inv(int n) {return getpoly(n,ginv);}
    poly exp(int n) {return getpoly(n,gexp);}
    poly ln(int n) {return getpoly(n,gln);}
};
poly operator*(const poly &a,const poly &b)
{
    int n=a.deg(),m=b.deg(),lim=glim(n+m);
    static int f[N],g[N];
    for(int i=0;i<lim;i++) f[i]=g[i]=0;
    for(int i=0;i<=n;i++) f[i]=a[i];
    for(int i=0;i<=m;i++) g[i]=b[i];
    fftinit(lim),fft(f,lim,1),fft(g,lim,1);
    for(int i=0;i<lim;i++) f[i]=1ll*f[i]*g[i]%MOD;
    fft(f,lim,-1); poly c(n+m+1);
    for(int i=0;i<=n+m;i++) c[i]=f[i];
    return c;
}
int fac[N],ifac[N],inv[N];
void facinit(int n)
{
	fac[0]=ifac[0]=fac[1]=ifac[1]=inv[1]=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=1ll*inv[MOD%i]*(MOD-MOD/i)%MOD;
		fac[i]=1ll*fac[i-1]*i%MOD;
		ifac[i]=1ll*ifac[i-1]*inv[i]%MOD;
	}
}
int main()
{
#ifdef LOCAL
    double _stime=clock();
#endif
    int n=100000; facinit(n);
    poly f(n+1),g(n+1),g1(n+1);
    for(int i=0;i<=n;i++) f[i]=i==0?1:MOD-ifac[i];
    f=f.inv(n+1);
    for(int i=0;i<=n;i++) g[i]=i==0?1:MOD-ifac[i],g1[i]=ifac[i];
    --g1[0];
    g=(g*g).inv(n+1)*g1;
    for(int i=0;i<=n;i++) f[i]=1ll*f[i]*fac[i]%MOD,g[i]=1ll*g[i]*fac[i]%MOD;
    int T;scanf("%d",&T);while(T--)
    {
        scanf("%d",&n);
        printf("%d\n",1ll*qpow(f[n])*g[n]%MOD);
    }
#ifdef LOCAL
    cerr << "Time used: " << clock()-_stime << " ms\n";
#endif
    return 0;
}