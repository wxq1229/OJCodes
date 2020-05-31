#include <bits/stdc++.h>
using namespace std;
const int MOD=998244353,i2=(MOD+1)>>1,N=1<<18;
template<typename T> inline void upd(T &x)
{while(x>=MOD) x-=MOD; while(x<0) x+=MOD;}
void fwtor(int *f,int n,int flg)
{
	for(int len=2,k=1;len<=n;len<<=1,k<<=1)
		for(int i=0;i<n;i+=len)
			for(int j=i;j<i+k;j++) upd(f[j+k]+=flg*f[j]);
}
void fwtand(int *f,int n,int flg)
{
	for(int len=2,k=1;len<=n;len<<=1,k<<=1)
		for(int i=0;i<n;i+=len)
			for(int j=i;j<i+k;j++) upd(f[j]+=flg*f[j+k]);
}
void fwtxor(int *f,int n,int flg)
{
	for(int len=2,k=1;len<=n;len<<=1,k<<=1)
		for(int i=0;i<n;i+=len)
			for(int j=i;j<i+k;j++)
			{
				int x=f[j],y=f[j+k];
				upd(f[j]=x+y),upd(f[j+k]=x-y);
				if(flg==-1) f[j]=1ll*f[j]*i2%MOD,f[j+k]=1ll*f[j+k]*i2%MOD;
			}
}
template<typename T> void mult(int *f,int *g,int n,T fwt)
{
	fwt(f,n,1),fwt(g,n,1);
	for(int i=0;i<n;i++) f[i]=1ll*f[i]*g[i]%MOD;
	fwt(f,n,-1);
}
int n,a[N],b[N],f[3][N],g[3][N];
int main()
{
	scanf("%d",&n); n=1<<n;
	for(int i=0;i<n;i++) scanf("%d",&a[i]),f[0][i]=f[1][i]=f[2][i]=a[i];
	for(int i=0;i<n;i++) scanf("%d",&b[i]),g[0][i]=g[1][i]=g[2][i]=b[i];
	mult(f[0],g[0],n,fwtor);
	mult(f[1],g[1],n,fwtand);
	mult(f[2],g[2],n,fwtxor);
	for(int i=0;i<n;i++) printf("%d%c",f[0][i]," \n"[i==n-1]);
	for(int i=0;i<n;i++) printf("%d%c",f[1][i]," \n"[i==n-1]);
	for(int i=0;i<n;i++) printf("%d%c",f[2][i]," \n"[i==n-1]);
	return 0;
}