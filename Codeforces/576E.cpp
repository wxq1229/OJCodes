#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 3;

struct DSU {
  int fa[N<<1], siz[N<<1];
  vector<pair<int,int>> stk;
  void merge(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return;
    if (siz[pu] > siz[pv]) swap(pu, pv);
    fa[pu] = pv, siz[pv] += siz[pu];
    stk.push_back(make_pair(pu, pv));
  }
  int find(int u) { return u==fa[u] ? u : find(fa[u]); }
  void _undo() {
    int u = stk.back().first, v = stk.back().second;
    fa[u] = u, siz[v] -= siz[u];
    stk.pop_back();
  }
  void undo(int lst) { while (stk.size() > lst) _undo(); }
  void init(int n) {
    for (int i = 0; i <= n; i++) {
      siz[i] = 1;
      fa[i] = i;
    }
    stk.clear();
  }
  bool chk(int u, int v) { return find(u) == find(v); }
} dsu[51];

struct edge {
  int u, v;
} es[N];

struct Opt {
  int eid, col;
} op[N];

int n, m, K, Q;

struct SegTree {
  vector<int> os[N << 2];
  
  void build(int x, int l, int r) {
    os[x].clear();
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(x<<1, l, mid);
    build(x<<1|1, mid + 1, r);
  }
  void upd(int x, int l, int r, int ql, int qr, int id) {
    if (ql <= l && r <= qr) {
      os[x].push_back(id);
      return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) upd(x<<1, l, mid, ql, qr, id);
    if (mid < qr) upd(x<<1|1, mid + 1, r, ql, qr, id);
  }
  
  short lst_col[N];
  void solve(int x, int l, int r) {
    vector<int> lst(K + 1, 114514 * 10);
    for (int i = 1; i <= K; i++) {
      lst[i] = dsu[i].stk.size();
    }
    auto undo_all = [&]() {
      for (int i = 1; i <= K; i++) dsu[i].undo(lst[i]);
    };
    for (auto o : os[x]) {
      int u = es[op[o].eid].u, v = es[op[o].eid].v, c = op[o].col;
      if (c != 0 && !dsu[c].chk(u,v)) {
        dsu[c].merge(u, v + n);
        dsu[c].merge(u + n, v);
      }
    }
    if (l == r) {
      int eid = op[l].eid;
      int u = es[eid].u, v = es[eid].v, c = op[l].col;
      if (dsu[c].chk(u, v)) {
        puts("NO");
        op[l].col = lst_col[eid];
      } else {
        puts("YES");
        lst_col[eid] = op[l].col;
      }
      undo_all();
      return;
    }
    int mid = (l + r) >> 1;
    solve(x<<1, l, mid), solve(x<<1|1, mid + 1, r);
    undo_all();
  }
} T;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> K >> Q;
  for (int i = 1; i <= m; i++) {
    cin >> es[i].u >> es[i].v;
  }
  for (int i = 1; i <= Q; i++) {
    cin >> op[i].eid >> op[i].col;
  }
  for (int i = 1; i <= K; i++) dsu[i].init(n << 1);
  T.build(1, 1, Q);
  vector<int> lst(m + 1, Q + 1);
  for (int i = Q; i >= 1; i--) {
    int l = i + 1, r = lst[op[i].eid] - 1;
    if (l <= r) T.upd(1, 1, Q, l, r, i);
    lst[op[i].eid] = i;
  }
  T.solve(1, 1, Q);
  return 0;
}