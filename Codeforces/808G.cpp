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

const int N=1e7+10;

int nxt[N],n,m,f[N],g[N];
char s[N],t[N];

int main() {
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);
	nxt[1]=0;
	rep(i,2,m+1) {
		int j=nxt[i-1];
		while (j!=0&&t[j+1]!=t[i]) j=nxt[j];
		nxt[i]=j+(t[j+1]==t[i]);
	}
	auto match=[&](int p) {
		rep(i,1,m+1) if (s[p-m+i]!=t[i]&&s[p-m+i]!='?') return 0;
		return 1;
	};
	rep(i,m,n+1) {
		if (match(i)) {
			g[i]=f[i-m]+1;
			int j=nxt[m];
			while (j!=0) {
				g[i]=max(g[i],g[i-(m-j)]+1);
				j=nxt[j];
			}
		}
		f[i]=max(f[i-1],g[i]);
	}
	printf("%d\n",f[n]);
	return 0;
}