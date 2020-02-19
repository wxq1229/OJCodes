#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10,P=998244353;
inline int fpow(int x,int y,int mod=P)
{
	int ret=1; for(x%=mod;y;y>>=1,x=1ll*x*x%mod)
		if(y&1) ret=1ll*ret*x%P;
	return ret;
}
const int gen=3,igen=fpow(gen,P-2);
inline int add(int x,int y,int mod=P){return (x+=y)>=mod?x-mod:x;}
inline int sub(int x,int y,int mod=P){return (x-=y)<0?x+mod:x;}
inline int normal(int x,int mod=P){return x<0?x+mod:x;}
namespace Poly
{
	int rev[N];
	void init(int n)
	{
		for(int i=0;i<n;i++)
			rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
	}
	void ntt(int *f,int n,int flg)
	{
		for(int i=0;i<n;i++)
			if(rev[i]<i) swap(f[i],f[rev[i]]);
		for(int len=2,k=1;len<=n;len<<=1,k<<=1)
		{
			int wn=fpow(flg==1?gen:igen,(P-1)/len);
			for(int i=0;i<n;i+=len)
				for(int j=i,w=1;j<i+k;j++,w=1ll*w*wn%P)
				{
					int tmp=1ll*f[j+k]*w%P;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
		}
		if(flg==-1)
		{
			int inv=fpow(n,P-2);
			for(int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
		}
	}
}
using Poly::ntt;
int f[N],g[N],n;
int pw2[N],inv[N],ifac[N],fac[N];
int main()
{
	scanf("%d",&n);
	inv[1]=ifac[0]=ifac[1]=1;
	pw2[0]=1,pw2[1]=2; fac[0]=fac[1]=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=1ll*inv[P%i]*(P-P/i)%P;
		ifac[i]=1ll*ifac[i-1]*inv[i]%P;
		pw2[i]=2ll*pw2[i-1]%P;
		fac[i]=1ll*fac[i-1]*i%P;
	}
	for(int i=0;i<=n;i++)
	{
		f[i]=1ll*((i&1)?P-1:1)*ifac[i]%P;
		if(i==0) g[i]=1; else if(i==1) g[i]=n+1;
		else g[i]=1ll*sub(fpow(i,n+1),1)*ifac[i]%P*fpow(i-1,P-2)%P;
	}
	int limit=1; while(limit<=n*2)limit<<=1;
	Poly::init(limit);
	ntt(f,limit,1),ntt(g,limit,1);
	for(int i=0;i<limit;i++) f[i]=1ll*f[i]*g[i]%P;
	ntt(f,limit,-1);
	int ans=0;
	for(int i=0;i<=n;i++) ans=add(ans,1ll*pw2[i]*fac[i]%P*f[i]%P);
	printf("%d\n",ans);
	return 0;
}