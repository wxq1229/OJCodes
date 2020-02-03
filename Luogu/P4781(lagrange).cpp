#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int P=998244353;
inline int fpow(int a,int b){
	int ret=1; for (;b;b>>=1,a=1ll*a*a%P) if (b&1) ret=1ll*ret*a%P;
	return ret; 
}
#define normal(x) (((x)%P+P)%P)
#define inv(x) (fpow((x),P-2))
const int N=2010;
int lagrange(int *x,int *y,int n,int k){
	int ans=0;
	for (int i=1;i<=n;i++){
		ll tmp=y[i]%P;
		for (int j=1;j<=n;j++) if (j!=i)
			tmp=1ll*tmp*inv(normal(x[i]-x[j]))%P*normal(k-x[j])%P;
		ans=(ans+tmp)%P;
	}
	return ans;
}
int x[N],y[N],K,n;
int main(){
#ifdef WXQ
	freopen("A.in","r",stdin);
#endif
	scanf("%d%d",&n,&K);
	for (int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
	printf("%d\n",lagrange(x,y,n,K));
	return 0;
}
