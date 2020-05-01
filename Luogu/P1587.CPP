#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll gcd(ll x, ll y) { return y ? gcd(y, x%y) : x; }
inline ll sqr(ll x) { return x * x; }

const int maxn = 6e6, N = maxn + 10, maxk = 2000, NK = maxk + 10;

#define ref ptilopsis // f**k c++11

int K;
int mu[N], ref[NK];
bool vis[N];
int ps[500010], pn;

void init() {
  mu[1] = 1;
  for (register int i = 2; i <= maxn; i++) {
    if (!vis[i]) { ps[pn++] = i; mu[i] = -1; }
    for (int j = 0; j < pn && i*ps[j] <= maxn; j++) {
      vis[i * ps[j]] = 1;
      if (i % ps[j] == 0) { mu[i*ps[j]] = 0; break; }
      else mu[i * ps[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= maxn; i++) mu[i] += mu[i-1];
  
  ref[0] = 0;
  for (int i = 1; i <= maxk; i++) ref[i] = ref[i-1] + (gcd(i,K) == 1);
}

inline ll f(int n) { return 1ll * (n / K) * ref[K] + ref[n % K]; }

map<int,ll> ansmu;

ll Smu(int n) {
  if (n <= maxn) return mu[n];
  if (ansmu.count(n)) return ansmu[n];
  ll ans = 1;
  for (int l = 2, r = 0; l <= n; l = r+1) {
    r = n / (n / l);
    ans -= 1ll * (r-l+1) * Smu(n / l);
  }
  return ansmu[n] = ans;
}

map<pair<int,int>, ll> recg;
vector<int> d[NK];

ll g(int n, int k) {
  if (recg.count(make_pair(n,k))) return recg[make_pair(n,k)];
  if (n == 0) return 0;
  if (k == 1) return Smu(n);
  ll ans = 0;
  for (auto i : d[k]) if (mu[i]-mu[i-1] != 0)
    ans += 1ll * sqr(mu[i]-mu[i-1]) * g(n/i, i);
  return recg[make_pair(n,k)] = ans;
}

int n, m;

int main() {
  scanf("%d%d%d", &n, &m, &K);
  init(); int tn = min(n,m); ll ans = 0;
  for (int i = 1; i <= maxk; i++)
    for (int j = i; j <= maxk; j+=i) d[j].push_back(i);
  for (int l = 1, r = 0; l <= tn; l = r+1) {
    r = min(n/(n/l), m/(m/l));
    ans += 1ll * (n/l) * f(m/l) * (g(r,K) - g(l-1,K));
  }
  printf("%lld\n", ans);
  return 0;
}
