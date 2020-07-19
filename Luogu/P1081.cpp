#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, LOG = 20;
const long long inf = (long long) 1e18;

int n;
long long h[N];

struct node {
  int id;   
  long long h;
  
  bool operator<(const node& other) const {
    return h < other.h;
  }
};
int nxta[N], nxtb[N];
long long nxtda[N], nxtdb[N], disa[N][LOG], disb[N][LOG];
int desta[N][LOG], destb[N][LOG];
int dest[N][LOG];
struct info {
  long long a, b;
  info operator+(const info& other) const {
    info ans = {0, 0};
    ans.a = a + other.a;
    ans.b = b + other.b;
    return ans;
  }
  double operator()() const { return 1.0 * a / b; }

  long long d() const { return a + b; }
} dis[N][LOG];  
  
void init() {
  multiset<node> s;
  s.insert({0, inf}), s.insert({0, inf});
  s.insert({0, -inf}), s.insert({0, -inf});
  for (int i = n; i >= 1;i--) {
    auto its = s.lower_bound({i, h[i]});
    auto itp = --s.lower_bound({i, h[i]});      
    long long dp = abs(h[i] - itp->h);
    long long ds = abs(h[i] - its->h);
    if (dp <= ds) {
      nxtb[i] = itp->id;
      auto itpp = prev(itp);
      long long dpp = abs(h[i] - itpp->h);
      if (dpp <= ds) {
        nxta[i] = itpp->id;
      } else {
        nxta[i] = its->id;
      }
    } else {
      nxtb[i] = its->id;
      auto itss = next(its);
      long long dss = abs(h[i] - itss->h);
      if (dp <= dss) {
        nxta[i] = itp->id;
      } else {
        nxta[i] = itss->id;
      }
    }
    nxtda[i] = abs(h[i] - h[nxta[i]]);
    nxtdb[i] = abs(h[i] - h[nxtb[i]]); 
    s.insert({i, h[i]});
  }               
  for (int i = 1; i <= n; i++) {
    desta[i][0] = nxta[i];
    if (desta[i][0]) {
      disa[i][0] = nxtda[i];
    }
    destb[i][0] = nxtb[i];
    if (destb[i][0]) {
      disb[i][0] = nxtdb[i];
    }
  }
  for (int j = 1; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
      disa[i][j] = disa[desta[i][j - 1]][j - 1] + disa[i][j - 1];
      disb[i][j] = disb[destb[i][j - 1]][j - 1] + disb[i][j - 1];
      desta[i][j] = desta[desta[i][j - 1]][j - 1];
      destb[i][j] = destb[destb[i][j - 1]][j - 1];
    }
  }
  for (int i = 1; i <= n; i++) {
    dest[i][0] = destb[desta[i][0]][0];
    if (dest[i][0]) {
      dis[i][0] = {disa[i][0], disb[desta[i][0]][0]};
    }
  }
  for (int j = 1; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
      dest[i][j] = dest[dest[i][j - 1]][j - 1];
      dis[i][j] = dis[i][j - 1] + dis[dest[i][j - 1]][j - 1];
    }
  }
}

info query(int s, int x) {
  info ans = {0, 0};
  int at = s;
  for (int i = LOG - 1; i >= 0; i--) {
    if (dest[at][i] == 0) {
      // cerr << "F\n";
      continue;
    }
    if ((ans + dis[at][i]).d() <= x) {
      ans = ans + dis[at][i];
      at = dest[at][i];
    } 
  }
  // cerr << "at: " << at << '\n';
  if (ans.d() + disa[at][0] <= x) {
    ans.a += disa[at][0];
  }
  // cerr << endl;
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> h[i];
  }
  init();
  {
    int x0;
    cin >> x0;
    double ans = inf;
    int s0 = 0;
    for (int i = 1; i <= n; i++) {
      info fo = query(i, x0);
      double d = 114514;
      if (fo.b == 0) {
        d = inf;
      } else {
        d = fo();
      }
      if (d < ans || (d == ans && h[i] > h[s0])) {
        ans = fo();
        s0 = i;
      }
    }
    cout << s0 << '\n';
  }
  int tt;
  cin >> tt;
  while (tt--) {
    int s, x;
    cin >> s >> x;
    info ans = query(s, x);
    cout << ans.a << " " << ans.b << '\n';
  }
  return 0;
}