#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=3e6+10;
ll n,p;
ll inv[MAXN];
int main(){
	scanf("%lld%lld",&n,&p);
	inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=(p-p/i)*inv[p%i]%p;
	for (int i=1;i<=n;i++)printf("%lld\n",inv[i]);
	return 0;
}
