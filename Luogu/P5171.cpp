#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
ll solve(ll a,ll b,ll c,ll n){
//	cerr<<a<<" "<<b<<" " <<c<<" "<<n<<endl;
	ll ac=a/c,bc=b/c,m=(a*n+b)/c;
	if (a==0)return bc*(n+1);
	if (a>=c||b>=c)
		return n*(n+1)/2*ac+(n+1)*bc+solve(a%c,b%c,c,n);
	return n*m-solve(c,c-b-1,a,m-1);
}
int main(){
	ll a,b,c;
	scanf("%lld%lld%lld",&a,&b,&c);
	ll n=c/a;
	printf("%lld\n",solve(a,c%a,b,n)+n+1);
	return 0;
}
