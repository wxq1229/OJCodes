#include <bits/stdc++.h>
using namespace std;
const int N=1010; int P;
#define normal(x) (((x)%P+P)%P)
inline int fpow(int a,int b,int m=P){
	int ret=1; 
	for (;b;b>>=1,a=1ll*a*a%m) if (b&1) ret=1ll*ret*a%m;
	return ret;
}
inline int getinv(int x){return fpow(x,P-2);}
inline void update(int &x,int y){x+=y; if (x>=P)x-=P;}
int lagrange(int *x,int *y,int n,int K){
	int ans=0;
	for (int i=1;i<=n;i++){
		int tmp=y[i];
		for (int j=1;j<=n;j++) if(j!=i)
			tmp=1ll*tmp*normal(K-x[j])%P*getinv(normal(x[i]-x[j]))%P;
		update(ans,tmp);
	}
	return ans;
}
int f[N][N],n,m,x[N],y[N];
int main(){
	scanf("%d%d%d",&m,&n,&P);
	int fac=1;for (int i=1;i<=n;i++) fac=1ll*fac*i%P;
	for (int i=0;i<=2*n+1;i++) f[0][i]=1;
	for (int i=1;i<=n;i++){
		for (int j=1;j<=2*n+1;j++){
			update(f[i][j],1ll*j*f[i-1][j-1]%P);
			update(f[i][j],f[i][j-1]%P);
		}
	}
	for (int i=1;i<=2*n+1;i++) x[i]=i,y[i]=f[n][i];
	printf("%d\n",1ll*fac*lagrange(x,y,2*n+1,m)%P);
	return 0;
}
