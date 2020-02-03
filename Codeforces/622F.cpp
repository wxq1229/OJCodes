#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P=1e9+7;
const int N=1e6+10;
void update(int &x,int y){
	x+=y; if (x>=P) x-=P;
}
int fpow(int a,int b){
	int ret=1; for (;b;b>>=1,a=1ll*a*a%P) if (b&1)ret=1ll*ret*a%P;
	return ret;
}
int getinv(int x){return fpow(x,P-2);}
#define normal(x) (((x)%P+P)%P)
int pre[N],suf[N],ifac[N],inv[N];
int main(){
	int n,K; scanf("%d%d",&n,&K);
	if (K==0){printf("%d\n",n);return 0;}
	ifac[0]=1,inv[1]=1,ifac[1]=1;
	for (int i=2;i<=K+2;i++){
		inv[i]=1ll*inv[P%i]*(P-P/i)%P;
		ifac[i]=1ll*ifac[i-1]*inv[i]%P;
	}
	pre[0]=1; 
	for (int i=1;i<=K+2;i++) pre[i]=1ll*pre[i-1]*normal(n-i)%P;
	suf[K+3]=1; 
	for (int i=K+2;i>=0;i--) suf[i]=1ll*suf[i+1]*normal(n-i)%P;
	int yi=0,ans=0; for (int i=1;i<=K+2;i++){
		update(yi,fpow(i,K));
		ll tmp=1ll*yi*ifac[i-1]%P*ifac[K+2-i]%P*pre[i-1]%P*suf[i+1]%P;
		if ((K+2-i)%2==0) update(ans,tmp); else update(ans,P-tmp);
	}
	printf("%d\n",ans);
	return 0;
}
