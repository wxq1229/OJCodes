#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, inf = 0x3f3f3f3f;
        
int n, m, K, mod;
vector<pair<int, int>> g[N], gr[N];

struct node {
  int u, w;
  bool operator < (node o) const { return w > o.w; }
};

int dis[N];
bool vis[N];

void dijkstra(int s) {
  for (int i = 0; i <= n; i++) dis[i] = inf, vis[i] = 0;
  priority_queue<node> q;
  q.push({s, 0}); dis[s] = 0;
  while (q.size()) {
    int u = q.top().u;
    q.pop();
    if (vis[u]) continue;
    vis[u] = 1;
    for (auto e : g[u]) {
      int v = e.first, w = e.second;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        q.push({v, dis[v]});
      }
    }
  }
//  for (int i = 1; i <= n; i++) cerr << dis[i] << " "; cerr << '\n';
}

bool done[N][55], ins[N][55];
int f[N][55];

int dp(int v, int k) {
  if (done[v][k]) return f[v][k];
  if (dis[v] == inf) {
    done[v][k] = 1;
    return f[v][k] = 0;
  }
  if (ins[v][k]) return -1;
  ins[v][k] = 1;
  int &ans = f[v][k];
  ans = 0;
  for (auto e : gr[v]) {
    int u = e.first, w = e.second;
    // dis[u] + nk + w - dis[v] = k
    // nk = k + dis[v] - w - dis[u]
    int nk = k + dis[v] - w - dis[u];
    if (0 <= nk && nk <= K) {
      int tmp = dp(u, nk);
      if (tmp == -1) return -1;
      ans = (ans + tmp) % mod;
    }
  }
  ans += v == 1 && k == 0;
  done[v][k] = 1;
  ins[v][k] = 0;
//  cout << "f[" << v << "][" << k << "] = " << f[v][k] << endl;
  return ans;
}

void init() {
  memset(done, 0, sizeof(done));
  memset(ins, 0, sizeof(ins));
  memset(f, 0, sizeof(f));
  for (int i = 0; i <= n; i++) g[i].clear(), gr[i].clear();
}

void solve() {
  cin >> n >> m >> K >> mod;
  init();
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].push_back(make_pair(v, w));
    gr[v].push_back(make_pair(u, w));
  }
  dijkstra(1);
  int ans = 0;            
  for (int i = 0; i <= K; i++) {
    int tmp = dp(n, i);
    if (tmp == -1) { cout << "-1\n"; return; }
    ans = (ans + tmp) % mod;
  } 
  cout << ans << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt; cin >> tt;
  while (tt--) solve();
  return 0;
}