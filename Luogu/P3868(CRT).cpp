#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mult(ll a,ll b,ll c){
	if (b>a) swap(a,b);
	ll ret=0; for (;b;b>>=1,a=a*2%c) if (b&1) ret=(ret+a)%c;
	return ret;
}
void exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){x=1,y=0;return;}
	else{
		exgcd(b,a%b,x,y);
		ll tmp=x; x=y; y=tmp-a/b*x;
	}
}
ll a[110],b[110]; int n;
ll CRT(){
	ll m=1; for (int i=1;i<=n;i++)m*=b[i];
	for (int i=1;i<=n;i++) a[i]=(a[i]%m+m)%m;
	ll ans=0;
	for (int i=1;i<=n;i++){
		ll Mi=m/b[i],t,tmp;
		exgcd(Mi,b[i],t,tmp);
		t=(t%m+m)%m;
		ans=(ans+mult(Mi,mult(t,a[i],m),m))%m;
	}
	return ans;
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for (int i=1;i<=n;i++) scanf("%lld",&b[i]);
	printf("%lld\n",CRT());
	return 0;
}
