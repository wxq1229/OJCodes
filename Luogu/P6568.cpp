#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int a[N],n,sum[N],k;
int main()
{
//	freopen("kettle.in","r",stdin);
//	freopen("kettle.out","w",stdout);
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]),sum[i]=sum[i-1]+a[i];
	int ans=0;
	for(int i=k+1;i<=n;i++) ans=max(ans,sum[i]-sum[i-k-1]);
	printf("%d\n",ans);
	return 0;
}
