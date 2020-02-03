#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10,P=998244353,gen=3,igen=(P+1)/gen;
inline int add(int x,int y){
	return x+y>=P?x+y-P:x+y;
}
inline int sub(int x,int y){
	return x-y<0?x-y+P:x-y;
}
inline int fpow(int x,int y){
	int ret=1; for (x%=P;y;y>>=1,x=1ll*x*x%P)
		if (y&1) ret=1ll*ret*x%P;
	return ret;
}
namespace Poly{
	int rev[N];
	void init(int limit){
		for (int i=0;i<limit;i++)
			rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
	}
	void dao(int *f,int n,int *d){
		static int F[N]; for (int i=0;i<=n;i++) F[i]=f[i];
		for (int i=1;i<=n;i++) d[i-1]=1ll*F[i]*i%P;	d[n]=0;
	}
	void jifen(int *f,int n,int *jf){
		static int F[N]; for (int i=0;i<=n;i++) F[i]=f[i];
		for (int i=0;i<=n;i++) 
			jf[i+1]=1ll*F[i]*fpow(i+1,P-2)%P;
		jf[0]=0;
	}
	void ntt(int *f,int n,int flg){
		for (int i=0;i<n;i++)
			if (rev[i]<i) swap(f[i],f[rev[i]]);
		for (int len=2,k=1;len<=n;len<<=1,k<<=1){
			int wn=fpow(flg==1?gen:igen,(P-1)/len);
			for (int i=0;i<n;i+=len){
				for (int j=i,w=1;j<i+k;j++,w=1ll*w*wn%P){
					int tmp=1ll*f[j+k]*w%P;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
			}
		}
		if (flg==-1){
			int inv=fpow(n,P-2);
			for (int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
		}
	}
	void getinv(int *f,int n,int *G){
		if (n==1){G[0]=fpow(f[0],P-2);return;}
		getinv(f,(n+1)>>1,G); static int F[N];
		int limit=1; while(limit<=2*n)limit<<=1; init(limit);
		for (int i=0;i<limit;i++)
			F[i]=i>=n?0:f[i],G[i]=i>=n?0:G[i];
		ntt(F,limit,1),ntt(G,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*G[i]*sub(2,1ll*F[i]*G[i]%P)%P;
		ntt(G,limit,-1);
		for (int i=n;i<limit;i++) G[i]=0;
	}
	void getln(int *f,int n,int *G){
		static int F[N],iF[N];
		for (int i=0;i<=n;i++) F[i]=f[i];
		getinv(F,n+1,iF),dao(F,n,F);
		int limit=1; while(limit<=2*n)limit<<=1; init(limit);
		ntt(F,limit,1),ntt(iF,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*F[i]*iF[i]%P;
		ntt(G,limit,-1);
		for (int i=n+1;i<limit;i++) G[i]=0;
		jifen(G,n,G);
	}
}
int f[N],n,ln[N];
int main(){
	scanf("%d",&n),--n;
	for (int i=0;i<=n;i++)scanf("%d",&f[i]);
	Poly::getln(f,n,ln);
	for (int i=0;i<=n;i++) printf("%d ",ln[i]);
	return 0;
}
