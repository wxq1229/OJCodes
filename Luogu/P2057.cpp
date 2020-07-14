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
  int n, m;
  cin >> n >> m;
  const int S = 0, T = n + 1, tot = T;
  g.init(tot, S, T);
  for (int i = 1; i <= n; i++) {
    bool will;
    cin >> will;          
    if (will) g.addedge(S, i, 1);
    else g.addedge(i, T, 1);
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    g.addedge(u, v, 1);
    g.addedge(v, u, 1);
  }
  cout << g.maxflow() << '\n';
  return 0;
}