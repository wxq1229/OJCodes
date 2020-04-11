#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=1e6+10;

char s[N];
int f[N];
int n;

void solve(int kase) {
	scanf("%s",s+1);
	f[1]=0;
	rep(i,2,n+1) {
		int j=f[i-1];
		while (j&&s[j+1]!=s[i]) j=f[j];
		f[i]=j+(s[j+1]==s[i]);
	}
	printf("Test case #%d\n",kase);
	rep(i,1,n+1) if (f[i]&&i%(i-f[i])==0) 
		printf("%d %d\n",i,i/(i-f[i]));
	puts("");
}

int main() {
	int t=0;
	while (scanf("%d",&n)==1&&n) solve(++t);
	return 0;
}