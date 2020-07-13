#include <bits/stdc++.h>

using namespace std;
          
template <typename cap_t, cap_t MAXCAP = (cap_t) 2e9>
struct Dinic {
  static const int V = 1e6 + 10, E = 1e6 + 10;
  
  struct edge {
    edge *next, *rev;
    cap_t cap, flow;
    int from, to;
  } pool[E << 1], *cur, *fst[V];
  int s, t, n;

  void init(int sz, int S, int T) {
    s = S, t = T, n = sz;
    cur = pool;
    for (int i = 0; i <= n; i++) {
      fst[i] = NULL;
    }
  }

  edge *ade(int u, int v, cap_t w) {
    edge *ret = cur++;
    ret->from = u, ret->to = v;
    ret->cap = w, ret->flow = 0;
    ret->next = fst[u], fst[u] = ret;
    return ret;
  }
  void addedge(int u, int v, int w) {
    edge *e1 = ade(u, v, w), *e2 = ade(v, u, 0);
    e1->rev = e2, e2->rev = e1;
  }         

  int d[V];
  bool bfs() {
    for (int i = 0; i <= n; i++) {
      d[i] = 0;
    }
    vector<int> q; 
    q.push_back(s);
    d[s] = 1;
    for (int i = 0; i < (int) q.size(); i++) {
      int u = q[i];
      for (edge *p = fst[u]; p; p = p->next) {
        int v = p->to;
        if (p->cap > p->flow && !d[v]) {
          d[v] = d[u] + 1;
          q.push_back(v);
        }
      }
    }
    return d[t];
  }

  edge *ecur[V];
  cap_t dfs(int u, cap_t augment) {
    if (!augment || u == t) {
      return augment;
    }
    for (edge* &p = ecur[u]; p; p = p->next) {
      int v = p->to;
      if (p->cap > p->flow && d[v] == d[u] + 1) {
        cap_t out = dfs(v, min(augment, p->cap - p->flow));
        if (out) {
          p->flow += out;
          p->rev->flow -= out;
          return out;
        } else {
          d[v] = 0;
        }
      }
    }
    return 0;
  }

  cap_t maxflow() {
    cap_t res = 0;
    while (bfs()) {
      for (int i = 0; i <= n; i++) {
        ecur[i] = fst[i];
      }  
      while (true) {
        cap_t out = dfs(s, MAXCAP);
        if (!out) break;
        res += out;
      }
    }
    return res;
  }
};

Dinic<int> g;                                      

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  
  vector<vector<int>> a(n, vector<int>(m)), s(n, vector<int>(m));
  vector<vector<int>> same_a(n, vector<int>(m)), same_s(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> a[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> s[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> same_a[i][j];
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> same_s[i][j];
    }
  }                           

  int tot = n * m;
  auto Id = [&](int i, int j, int type = 0) {
    return i * m + j + type * tot;
  };

  const vector<int> dx = {0, 0, 1, 0, -1};
  const vector<int> dy = {0, 1, 0, -1, 0};
  auto inside = [&](int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < m;
  };

  const int S = tot * 3, T = S + 1, inf = (int) 1e9;
  g.init((tot + 1) * 3, S, T);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ans += a[i][j] + s[i][j] + same_a[i][j] + same_s[i][j];
      g.addedge(S, Id(i, j), a[i][j]);
      g.addedge(Id(i, j), T, s[i][j]);
      g.addedge(S, Id(i, j, 1), same_a[i][j]);
      g.addedge(Id(i, j, 2), T, same_s[i][j]);
      for (int d = 0; d < 5; d++) {
        int ni = i + dx[d], nj = j + dy[d];
        if (inside(ni, nj)) {
          g.addedge(Id(i, j, 1), Id(ni, nj), inf);
          g.addedge(Id(ni, nj), Id(i, j, 2), inf);
        }
      }
    }
  }
  cout << ans - g.maxflow() << '\n';              
  return 0;
}