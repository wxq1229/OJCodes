#include <bits/stdc++.h>
using namespace std;
template<class T> inline T RD(){
	T x=0,f=1;char ch=getchar();while (!isdigit(ch)){f=ch=='-'?-f:f;ch=getchar();}
	while (isdigit(ch)){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;
}
template<class T> inline void output(T x){
	if (x<0){putchar('-');x=-x;}
	if (x>9) output(x/10); putchar(x%10+48);
}
#define RI RD<int>()
#define RL RD<long long>()
typedef __int128 ll;
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
ll exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){x=1,y=0; return a;}
	ll d=exgcd(b,a%b,x,y),tmp=x; x=y,y=tmp-a/b*y;
	return d;
}
ll mult(ll a,ll b,ll m){
	ll ret=0; for (a%=m;b;b>>=1,a=a*2%m)if (b&1) ret=(ret+a)%m;
	return ret;
}
ll getans(ll a,ll b,ll m){ 
	ll x,y,d=exgcd(a,m,x,y);
	if (b%d!=0) return -1;
	x=mult(x,b/d,m);
	return (x%m+m)%m;
}
const int N=1e5+10;
int n;
ll a[N],b[N];
ll excrt(){
	ll lcm=b[1],ans=a[1];
	for (int i=2;i<=n;i++){
		ll k1=lcm,k2=((a[i]-ans)%b[i]+b[i])%b[i],k=getans(k1,k2,b[i]);
		if (k==-1){puts("FFF"); return -1;}
		ans+=k*lcm;
		lcm=b[i]/gcd(lcm,b[i])*lcm;
		ans=(ans%lcm+lcm)%lcm;
	}
	return (ans%lcm+lcm)%lcm;
}
int main(){
#ifdef WXQ
	freopen("A.in","r",stdin);
#endif
	n=RI;for (int i=1;i<=n;i++) b[i]=RL,a[i]=RL,a[i]%=b[i];
	output(excrt());
	return 0;
}
