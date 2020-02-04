#include <bits/stdc++.h>
using namespace std;
const int N=1e6,P=998244353,gen=3,igen=(P+1)/gen;
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
inline int normal(int x){return (x%P+P)%P;}
inline int getnum(){
	int x=0,f=1; char ch=getchar(); 
	while(!isdigit(ch)){f=ch=='-'?-f:f;ch=getchar();}
	while(isdigit(ch)){x=(10ll*x+ch-48)%P;ch=getchar();}
	return normal(x*f);
}
namespace Poly{
	int rev[N];
	void init(int n){
		for (int i=0;i<n;i++)
			rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
	}
	void ntt(int *f,int n,int flg){
		for (int i=0;i<n;i++)
			if (rev[i]<i) swap(f[i],f[rev[i]]);
		for (int len=2,k=1;len<=n;len<<=1,k<<=1){
			int wn=fpow(flg==1?gen:igen,(P-1)/len);
			for (int i=0;i<n;i+=len){
				for (int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
					int tmp=1ll*w*f[j+k]%P;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
			}
		}
		if (flg==-1){
			int inv=fpow(n,P-2);
			for (int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
		}
	}
	void dao(int *f,int n,int *g){
		static int F[N]; for (int i=0;i<=n;i++)F[i]=f[i];
		for (int i=1;i<=n;i++) g[i-1]=1ll*i*F[i]%P; g[n]=0;
	}
	void jifen(int *f,int n,int *g){
		static int F[N]; for (int i=0;i<=n;i++)F[i]=f[i];
		for (int i=0;i<=n;i++) g[i+1]=1ll*fpow(i+1,P-2)*F[i]%P; g[0]=0;
	}
	void getinv(int *f,int n,int *G){
		if (n==1){G[0]=fpow(f[0],P-2);return;}
		getinv(f,(n+1)>>1,G); static int F[N];
		int limit=1; while(limit<=2*n)limit<<=1; init(limit);
		for (int i=0;i<limit;i++) F[i]=i>=n?0:f[i],G[i]=i>=n?0:G[i];
		ntt(F,limit,1),ntt(G,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*G[i]*sub(2,1ll*F[i]*G[i]%P)%P;
		ntt(G,limit,-1);
		for (int i=n;i<limit;i++) G[i]=0;
	}
	void getln(int *f,int n,int *G){
		static int F[N],iF[N]; for (int i=0;i<n;i++) F[i]=f[i];
		getinv(F,n,iF),dao(F,n-1,F);
		int limit=1; while(limit<=2*n)limit<<=1; init(limit);
		for (int i=n-1;i<limit;i++) F[i]=0;
		ntt(F,limit,1),ntt(iF,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*F[i]*iF[i]%P;
		ntt(G,limit,-1);
		jifen(G,n-1,G); for (int i=n;i<limit;i++)G[i]=0;
	}
	void exp(int *f,int n,int *G){
		if (n==1){G[0]=1;return;}
		exp(f,n>>1,G);
		static int F[N],ln[N]; int limit=1;
		while(limit<=2*n)limit<<=1; init(limit);
		for (int i=0;i<limit;i++) F[i]=i>=n?0:f[i],G[i]=i>=n?0:G[i];
		getln(G,n,ln);
		ntt(F,limit,1),ntt(G,limit,1),ntt(ln,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*G[i]*add(sub(1,ln[i]),F[i])%P;
		ntt(G,limit,-1);
		for (int i=n;i<limit;i++) G[i]=0;
	}
	void getexp(int *f,int n,int *G){
		static int F[N]; for (int i=0;i<n;i++) F[i]=f[i];
		int limit=1; while(limit<=n)limit<<=1;
		for (int i=n;i<limit;i++) F[i]=0;
		exp(F,limit,G);
		for (int i=n;i<limit;i++) G[i]=0;
	}
	void getpow(int *f,int n,int k,int *G){
		static int F[N]; for (int i=0;i<n;i++) F[i]=f[i];
		getln(F,n,F);
		for (int i=0;i<n;i++) F[i]=1ll*F[i]*k%P;
		getexp(F,n,G);
	}
}
int f[N],ans[N],n,k;
int main(){
	scanf("%d",&n),k=getnum();
	for (int i=0;i<n;i++)scanf("%d",&f[i]);
	Poly::getpow(f,n,k,ans);
	for (int i=0;i<n;i++)printf("%d ",ans[i]);
	return 0;
}
