#include <bits/stdc++.h>

using namespace std;
          
template <typename cap_t, cap_t MAXCAP = 0x3f3f3f3f>
struct Dinic {
  static const int V = 5e4 + 10, E = 1e5 + 10;
  
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
  void addedge(int u, int v, cap_t w) {
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
  int n;
  cin >> n;
  vector<vector<char>> grid(n, vector<char>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
    }
  }        
  auto id = [&](int i, int j) {
    return i * n + j;
  };
  auto color = [&](int i, int j) {
    return (i + j) % 2;
  };

  int tot = n * n, S = tot, T = S + 1;
  g.init(T + 1, S, T);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '1') {
        continue;
      }
      if (color(i, j)) g.addedge(id(i, j), T, 1);
      else g.addedge(S, id(i, j), 1);
    }
  }  
  const vector<int> dx = {-1, -2, 1, 2, -1, -2, 1, 2};
  const vector<int> dy = {-2, -1, -2, -1, 2, 1, 2, 1};
  auto inside = [&](int i, int j) {
    return 0 <= i && i < n && 0 <= j && j < n;
  };
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == '1' || color(i, j) != 0) {
        continue;
      }                   
      for (int d = 0; d < dx.size(); d++) {
        int ni = i + dx[d], nj = j + dy[d];
        if (!inside(ni, nj) || grid[ni][nj] != '0') {
          continue;
        }
        g.addedge(id(i, j), id(ni, nj), 1);
      }
    }
  }
  int ans = 0;                         
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      ans += grid[i][j] == '0';
    }
  }
  cout << ans - g.maxflow() << '\n';
  return 0;
}