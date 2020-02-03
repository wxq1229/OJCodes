#include <bits/stdc++.h>
using namespace std;
#define sq(x) ((x)*(x))
typedef double db;
int n,m;db aver,ans=1e9;
int sum[233],a[233];
void randomShuffle(){
	for (int i=1;i<=n;i++)swap(a[i],a[rand()%n+1]);
}
void solve(){
	randomShuffle();
	memset(sum,0,sizeof(sum));
	for (int pos,i=1;i<=n;i++){
		for (int minv=2333333,j=1;j<=m;j++)
			if (sum[j]<minv)minv=sum[pos=j];
		sum[pos]+=a[i];
	}
	db tmp=0.0;
	for (int i=1;i<=m;i++)tmp+=sq(sum[i]-aver);
	ans=min(ans,tmp/m);
}
int main(){
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	srand(233333);
	scanf("%d%d",&n,&m);
	int tmp=0;for (int i=1;i<=n;i++)scanf("%d",&a[i]),tmp+=a[i];
	aver=1.0*tmp/m;
	while (1.0*clock()/CLOCKS_PER_SEC<0.9)solve();
	printf("%.2f\n",sqrt(ans));
	return 0;
}
