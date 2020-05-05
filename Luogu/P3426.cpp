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

const int N = 5e5 + 10;

char s[N];
int nxt[N], f[N], n, lst[N];

int main() {
  scanf("%s", s + 1), n = strlen(s + 1);
  nxt[1] = 0;
  rep(i,2,n+1) {
    int j = nxt[i-1];
    while (j && s[j+1]!=s[i]) j = nxt[j];
    nxt[i] = j + (s[j+1]==s[i]);
  }
//  rep(i,1,n+1) printf("%d%c", nxt[i], " \n"[i==n]);
  f[0] = 0, f[1] = 1, lst[1] = 1, lst[0] = 0;
  rep(i,2,n+1) {
    int j = nxt[i];
    if (lst[f[j]] >= i-nxt[i]) f[i] = f[j];
    else f[i] = i;
    lst[f[i]] = i;
  }
  printf("%d\n", f[n]);
  return 0;
}