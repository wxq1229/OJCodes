#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
ll exgcd(ll a,ll b,ll &x,ll &y){
	if (b==0){
		x=1,y=0;
		return a;
	}
	ll ret=exgcd(b,a%b,x,y),z=x;
	x=y,y=z-y*(a/b);
	return ret;
}
int main(){
	ll a,b;scanf("%lld%lld",&a,&b);
	ll x,y,d=exgcd(a,b,x,y);
	printf("%lld\n",(x+b)%b);
	return 0;
}
