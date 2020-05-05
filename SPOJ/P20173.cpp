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
typedef unsigned long long ull;

const int N = 1e8 + 10;
int maxn;

bool vis[N];
int ps[20000001], pn;
ull sigma[N];
short mu[N], low[N];

void sieve() {
  int n = maxn; sigma[1] = mu[1] = 1;
  rep(i,2,n+1) {
    if (!vis[i]) {
      ps[pn++] = i;
      mu[i] = -1;
      sigma[i] = 2, low[i] = 1;
    }
    for (int j=0; j<pn && i*ps[j]<=n; j++) {
      int ip = i*ps[j]; vis[ip] = 1;
      if (i % ps[j] == 0) {
        mu[ip] = 0;
        low[ip] = low[i] + 1;
        sigma[ip] = sigma[i] / (low[i]+1) * (low[ip]+1);
        break;
      } else {
        mu[ip] = -mu[i];
        low[ip] = 1;
        sigma[ip] = sigma[i] * 2;
      }
    }
  }
  rep(i,1,n+1) sigma[i] += sigma[i-1];
}

map<ull,ull> ds;

inline ull Sd(ull n) {
  if (n <= maxn) return sigma[n];
  if (ds.count(n)) return ds[n];
  ull ans = 0;
  for (ull l=1, r=0; l <= n; l = r+1) {
    r = n / (n / l);
    ans += (n / l) * (r-l+1);
  }
  return ds[n] = ans;
}

map<ull,ull> recf;

inline ull f(ull n) {
  if (recf.count(n)) return recf[n];
  ull ans = 0;
  for (ull l=1, r=0; l <= n; l = r+1) {
    r = n / (n / l);
    ans += (Sd(r)-Sd(l-1)) * (n/l);
  }
  return recf[n] = ans;
}

ull solve(ll n) {
  ull ans = 0;
  for (ll i = 1; i*i <= n; i++)
    ans += f(n/i/i) * mu[i];
  return ans;
}

ll q[10010];

int main() {
  ll lim = 0;
  int T; scanf("%d",&T); rep(i,1,T+1) scanf("%lld",&q[i]), lim = max(lim, q[i]); 
  maxn = pow(lim, 2.0/3), sieve();
  rep(i,1,T+1) printf("%llu\n", solve(q[i]));
  return 0;
}