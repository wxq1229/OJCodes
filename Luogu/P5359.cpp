#include <bits/stdc++.h>
using namespace std;
const int N=6e5+10,P=167772161;
inline int fpow(int x,int y,int mod=P)
{
	int ret=1; for(x%=mod;y;y>>=1,x=1ll*x*x%mod)
		if(y&1) ret=1ll*ret*x%P;
	return ret;
}
const int gen=3,igen=fpow(gen,P-2);
inline int add(int x,int y,int mod=P){return (x+=y)>=mod?x-mod:x;}
inline int sub(int x,int y,int mod=P){return (x-=y)<0?x+mod:x;}
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
int f[N],g[N],inv[N],ifac[N],n;
int main()
{
	scanf("%d",&n);
	ifac[0]=ifac[1]=1,inv[1]=1;
	for(int i=2;i<=n;i++)
	{
		inv[i]=1ll*(P-P/i)*inv[P%i]%P;
		ifac[i]=1ll*inv[i]*ifac[i-1]%P;
	}
	for(int i=0;i<=n;i++)
	{
		f[i]=1ll*fpow(i,n)*ifac[i]%P;
		g[i]=1ll*((i&1)?P-1:1)*ifac[i]%P;
	}
	int limit=1; while(limit<=n*2)limit<<=1; init(limit);
	ntt(f,limit,1),ntt(g,limit,1);
	for(int i=0;i<limit;i++) f[i]=1ll*f[i]*g[i]%P;
	ntt(f,limit,-1);
	for(int i=0;i<=n;i++) printf("%d ",f[i]);
	return 0;
}