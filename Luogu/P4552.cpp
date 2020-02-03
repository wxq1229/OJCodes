#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[233333],d[233333];
int main(){
	int n;scanf("%d",&n);for (int i=1;i<=n;i++)scanf("%lld",&a[i]),d[i]=a[i]-a[i-1];
	ll tmp1=0,tmp2=0;for (int i=2;i<=n;i++)d[i]>0?tmp1+=d[i]:tmp2+=-d[i];
	printf("%lld\n%lld\n",max(tmp1,tmp2),abs(tmp1-tmp2)+1);
	return 0;
}
