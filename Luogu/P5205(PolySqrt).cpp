#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10,P=998244353,g=3,ig=(P+1)/g;
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
inline int sqr(int x){return 1ll*x*x%P;}
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
		for (int i=0;i<n;i++)
			if (rev[i]<i) swap(f[i],f[rev[i]]);
		for (int k=1,len=2;len<=n;len<<=1,k<<=1){
			int wn=fpow(flg==1?g:ig,(P-1)/len);
			for (int i=0;i<n;i+=len){
				for (int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
					int tmp=1ll*w*f[j+k]%P;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
			}
		}
		if (flg!=1){
			int inv=fpow(n,P-2);
			for (int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
		}
	}
	int F[N];
	void getinv(int *f,int n,int *inv){
		if (n==1){inv[0]=fpow(f[0],P-2);return;}
		getinv(f,(n+1)>>1,inv);
		int limit=1; while (limit<=n*2)limit<<=1; init(limit);
		for (int i=0;i<n;i++) F[i]=f[i];
		for (int i=n;i<limit;i++) F[i]=inv[i]=0;
		ntt(F,limit,1),ntt(inv,limit,1);
		for (int i=0;i<limit;i++) inv[i]=1ll*inv[i]*sub(2,1ll*F[i]*inv[i]%P)%P;
		ntt(inv,limit,-1);
		for (int i=n;i<limit;i++) inv[i]=0;
	}
	int H[N],iH[N];
	void getsqrt(int *f,int n,int *sqt){
		if (n==1){sqt[0]=1;return;}
		getsqrt(f,(n+1)>>1,sqt);
		int limit=1; while (limit<=2*n) limit<<=1;
		for (int i=0;i<limit;i++) H[i]=i>=n?0:2ll*sqt[i]%P;
		getinv(H,n,iH),init(limit);
		for (int i=0;i<limit;i++) F[i]=i>=n?0:f[i],sqt[i]=i>=n?0:sqt[i];
		ntt(F,limit,1),ntt(sqt,limit,1),ntt(iH,limit,1);
		for (int i=0;i<limit;i++) sqt[i]=1ll*add(F[i],sqr(sqt[i]))*iH[i]%P;
		ntt(sqt,limit,-1);
		for (int i=n;i<limit;i++) sqt[i]=0;
//		cout<<n<<" wtf: "; for (int i=0;i<n;i++) cout<<sqt[i]<<" "; cout<<endl;
	}
}
int f[N],sqt[N];
int main(){
	int n; scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&f[i]);
	Poly::getsqrt(f,n,sqt);
	for (int i=0;i<n;i++) printf("%d ",sqt[i]);
	return 0;
}
/*
7
1 8596489 489489 4894 1564 489 35789489  
*/
/*
1 503420421 924499237 13354513 217017417 707895465 411020414
*/
