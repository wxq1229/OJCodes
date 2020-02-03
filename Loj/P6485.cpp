#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	char ch; ll x=0; while(!isdigit(ch=getchar()));
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}return x;
}
const int P=998244353,G=3,IG=(P+1)/G;
inline int fpow(int a,ll b){
	int ret=1; for (;b;b>>=1,a=1ll*a*a%P)
		if (b&1) ret=1ll*a*ret%P;
	return ret;
}
const int i4=fpow(4,P-2);
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
ll n; int a[4],s;
int calc(int k){
	int ans=0,w4=fpow(G,(P-1)/4),iw4=fpow(IG,(P-1)/4);
	for (int j=0;j<4;j++)
		ans=add(ans,1ll*fpow(iw4,j*k)*fpow(add(1ll*s*fpow(w4,j)%P,1),n)%P);
	ans=1ll*ans*a[k]%P;
	return ans;
}
int main(){
	for (int _=read();_;_--){
		int ans=0;
		n=read(),s=read()%P,a[0]=read()%P,a[1]=read()%P,a[2]=read()%P,a[3]=read()%P;
		for (int k=0;k<4;k++)ans=add(ans,calc(k));
		printf("%d\n",1ll*i4*ans%P);
	}
	return 0;
}
