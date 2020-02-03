#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
const int MAXN=100010;
ll q[MAXN],a[MAXN],dp[MAXN],sum[MAXN];
int main(){
	int n,k;scanf("%d%d",&n,&k);
	int l=1,r=1;
	q[1]=0;
	rep (i,1,n)scanf("%lld",&a[i]),sum[i]=sum[i-1]+a[i];
	rep (i,1,n+1){
		//rep (j,l,r)printf("%d ",q[j]);
		//puts("");
		while (l<=r&&q[l]<i-k-1)l++;
		dp[i]=dp[q[l]]+sum[i-1]-sum[q[l]];
		while (l<=r&&dp[i]-sum[i]>=dp[q[r]]-sum[q[r]])r--;
		q[++r]=i;
	}
	printf("%lld\n",dp[n+1]);
	return 0;
}
