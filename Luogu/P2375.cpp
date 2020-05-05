#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a; i<n; i++)
#define per(i,a,n) for (int i=n-1; i>=a; i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N = 1e6 + 10, LOGN = 21, mod = 1e9 + 7;

char s[N];
int n, f[N], g[N];

void solve() {
  memset(g,0,sizeof(g));
  scanf("%s", s + 1); n = strlen(s+1);
  f[1] = g[0] = 0, g[1] = 1;
  rep(i,2,n+1) {
    int j = f[i-1];
    while (j && s[j+1]!=s[i]) j = f[j];
    f[i] = j + (s[j+1]==s[i]);
    g[i] = g[f[i]] + 1;
  }
  int ans = 1;
  {
    int j = f[1];
    rep(i,2,n+1) {
      while (j && s[j+1]!=s[i]) j = f[j];
      j += s[j+1] == s[i];
      while (j && (j<<1) > i) j = f[j];
      ans = 1ll * ans * (g[j]+1) % mod;
    }
  }
  printf("%d\n", ans);
}

int main() {
  int _; for (scanf("%d",&_); _; _--) solve();
  return  0;
}