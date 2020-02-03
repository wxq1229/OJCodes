#include <bits/stdc++.h>
using namespace std;
const int P=998244353,i2=(P+1)/2,g=3,ig=(P+1)/g;
inline int fpow(int x,int y){
	int ret=1; for (x%=P;y;y>>=1,x=1ll*x*x%P)
		if (y&1) ret=1ll*ret*x%P;
	return ret;
}
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
int main(){
	int n,p,k; scanf("%d%d%d",&n,&p,&k);
	int ik=fpow(k,P-2),ans=1ll*n*p%P*fpow(p+1,n-1)%P;
	ans=sub(ans,1ll*i2*(k-1)%P*fpow(add(p,1),n)%P);
	int wk=fpow(g,(P-1)/k),iwk=fpow(ig,(P-1)/k);
	for (int iw=iwk,w=wk,j=1;j<k;j++,w=1ll*wk*w%P,iw=1ll*iwk*iw%P){
		int iw1=fpow(sub(iw,1),P-2);
		ans=sub(ans,1ll*fpow(add(1ll*p*w%P,1),n)*iw1%P);
	}
	printf("%d\n",1ll*ans*ik%P);
	return 0;
}
