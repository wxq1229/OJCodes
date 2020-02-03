#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int T;scanf("%d",&T);while (T--){
		ll n;scanf("%lld",&n);
		if (n==4) puts("5");
		else if (n==10) puts("11");
		else printf("%lld\n",n-1);
	}
	return 0;
}
