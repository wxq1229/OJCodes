#include <bits/stdc++.h>
using namespace std;
const int N=1111111,MOD=167772161;
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
void ginv(const int *f,int n,int *g)
{
	if(n==1){g[0]=qpow(f[0]);return;}
	ginv(f,(n+1)>>1,g);
	static int f1[N]; int lim=glim((n-1)<<1);
	fftinit(lim);
	for(int i=0;i<lim;i++) g[i]=i<n?g[i]:0,f1[i]=i<n?f[i]:0;
	fft(g,lim,1),fft(f1,lim,1);
	for(int i=0;i<lim;i++) g[i]=1ll*g[i]*(2ll-1ll*f1[i]*g[i]%MOD+MOD)%MOD;
	fft(g,lim,-1);
	for(int i=n;i<lim;i++) g[i]=0;
}
namespace PolyMul {int f[N],g[N];}
struct poly
{
	vector<int> a;
	inline int size() const {return a.size();}
	inline int deg() const {return size()-1;}
	inline int operator [] (int i) const {return i<size()?a[i]:0;}
	inline int &operator [] (int i) {assert(i<size());return a[i];}
	poly(int n=0,int v=0) {a=vector<int>(n,v);}
	void resize(int n) {a.resize(n);}
	void debug() {printf("Poly Debug: ");for(int i=0;i<size();i++) printf("%d%c",a[i]," \n"[i==size()-1]);}
	void reverse() {for(int i=0,j=size()-1;i<j;i++,j--) swap(a[i],a[j]);}
	poly inv(int n)
	{
		static int f[N],g[N];
		memset(f,0,sizeof(f)),memset(g,0,sizeof(g));
		for(int i=0;i<n;i++) f[i]=i<size()?a[i]:0; // !!!!!! [] !!!!!!
		ginv(f,n,g); poly c(n);
		for(int i=0;i<n;i++) c[i]=g[i];
		return c;
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
poly solve(int l,int r)
{
	if(l==r)
	{
		poly ans(2);
		ans[0]=1,ans[1]=MOD-l;
		return ans;
	}
	int mid=(l+r)>>1;
	return solve(l,mid)*solve(mid+1,r);
}
poly ans;
int main()
{
#ifdef LOCAL
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
#endif
	int n,k;scanf("%d%d",&n,&k);
	if(n-k+1<=0)
	{
		for(int i=0;i<=n;i++) printf("0 ");
		return 0;
	}
	ans=solve(1,k).inv(n-k+1);
	for(int i=0;i<k;i++) printf("0 ");
	for(int i=k;i<=n;i++) printf("%d ",ans[i-k]);
	return 0;
}
