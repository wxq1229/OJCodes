#include <bits/stdc++.h>

using namespace std;

typedef double db;
const db INF = 1e9;

template <typename cap_t, typename cost_t>
struct MCMF {
  static const int E = 1e5 + 10, V = 1e5 + 10;
  
  struct edge {
    int from, to, nxt;
    cap_t cap, flow;
    cost_t cost;
  } e[E << 1];
  int fst[V], n, cnt, s, t;
  
  void init(int S, int T, int sz) {
    n = sz, cnt = 1;
    s = S, t = T;
    for (int i = 0; i <= n; i++) fst[i] = 0;
  }
  
  void ade(int u, int v, cap_t w, cost_t c) {
    e[++cnt] = {u, v, fst[u], w, 0, c};
    fst[u] = cnt;
  }
  void addedge(int u, int v, cap_t w, cost_t c) {
    ade(u, v, w, c), ade(v, u, 0, -c);
  }
  
  cap_t incf[V]; cost_t d[V];
  int pre[V]; bool vis[V];
  
  bool spfa() {
    for (int i = 0; i <= n; i++) {
      incf[i] = (cap_t) INF, d[i] = (cost_t) INF;
      vis[i] = 0, pre[i] = 0;
    }
    d[s] = 0, vis[s] = 1;
    vector<int> q;
    q.push_back(s);
    for (int cur = 0; cur < q.size(); cur++) {
      int u = q[cur];
      vis[u] = 0;
      for (int i = fst[u]; i; i = e[i].nxt) {
        int v = e[i].to; cost_t w = e[i].cost;
        if (d[v] > d[u] + w && e[i].cap > e[i].flow) {
          d[v] = d[u] + w;
          pre[v] = i;
          incf[v] = min(e[i].cap - e[i].flow, incf[u]);
          if (!vis[v]) vis[v] = 1, q.push_back(v);
        }
      }
    }
    return d[t] < (cost_t) INF;
  }
  
  cap_t maxflow; cost_t mincost;
  
  void augment() {
    int u = t;
    for (; u != s; u = e[pre[u]].from) {
      e[pre[u]].flow += incf[t];
      e[pre[u]^1].flow -= incf[t];
    }
    maxflow += incf[t], mincost += incf[t] * d[t];
  }
  
  pair<cap_t, cost_t> mcmf() {
    maxflow = mincost = 0;
    while (spfa()) augment();
    return make_pair(maxflow, mincost);
  }
};

MCMF<int, db> g;

const db eps = 1e-7;
const int N = 110;

int a[N][N], b[N][N], n;

bool chk(db mid) {
  int s = 0, t = n*2 + 1;
  g.init(s, t, n*2 + 2);
  for (int i = 1; i <= n; i++) g.addedge(s, i, 1, 0);
  for (int i = 1; i <= n; i++) g.addedge(i + n, t, 1, 0);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) g.addedge(i, j+n, 1, b[i][j]*mid - a[i][j]);
  auto ans = g.mcmf();
  return -ans.second >= 0;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) 
    for (int j = 1; j <= n; j++) scanf("%d", &a[i][j]);
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) scanf("%d", &b[i][j]);
  db l = 0, r = 1e4;
  while (l + eps < r) {
    db mid = (l+r) / 2;
    if (chk(mid)) l = mid;
    else r = mid;
  }
  printf("%.6f\n", l);
  return 0;
}
