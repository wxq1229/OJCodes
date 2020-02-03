#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P=1004535809,g=3,ig=334845270,N=500010;
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
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
	void ntt(int *f,int n,int flg){
		for (int i=0;i<n;i++) if (rev[i]<i) swap(f[i],f[rev[i]]);
		for (int k=1,len=2;len<=n;len<<=1,k<<=1){
			int wn=fpow(flg==1?g:ig,(P-1)/len);
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
	int F[N];
	void getinv(int *f,int n,int *G){
		if (n==1){G[0]=fpow(f[0],P-2);return;}
		getinv(f,(n+1)>>1,G);
		int limit=1; while(limit<=2*n)limit<<=1; init(limit);
		for (int i=0;i<n;i++) F[i]=f[i];
//		cout<<"wtf: "; for (int i=0;i<n;i++) cout<<G[i]<<" "; cout<<endl;
		for (int i=n;i<limit;i++) F[i]=G[i]=0;
		ntt(F,limit,1),ntt(G,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*G[i]*sub(2,1ll*F[i]*G[i]%P)%P;
		ntt(G,limit,-1);
		for (int i=n;i<limit;i++) G[i]=0;
	}
}
using Poly::ntt;
using Poly::getinv;
int G[N],iG[N],H[N],F[N];
int ifac[N],inv[N],fac[N];
int main(){
	int n; scanf("%d",&n);
	fac[0]=fac[1]=ifac[0]=ifac[1]=1,inv[1]=1;
	for (int i=2;i<=n;i++){
		inv[i]=1ll*inv[P%i]*(P-P/i)%P;
		ifac[i]=1ll*ifac[i-1]*inv[i]%P;
		fac[i]=1ll*fac[i-1]*i%P;
	}
	G[0]=1;
	for (int i=1;i<=n;i++) 
		G[i]=1ll*fpow(2,1ll*i*(i-1)/2%(P-1))*ifac[i]%P,H[i]=1ll*G[i]*i%P;
	getinv(G,n+1,iG);
	int limit=1; while(limit<=2*n)limit<<=1; Poly::init(limit);
	ntt(iG,limit,1),ntt(H,limit,1);
	for (int i=0;i<limit;i++) F[i]=1ll*iG[i]*H[i]%P;
	ntt(F,limit,-1);
	printf("%d\n",1ll*F[n]*fac[n-1]%P);
	return 0;
}




