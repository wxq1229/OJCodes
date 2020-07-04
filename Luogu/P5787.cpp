#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

struct DSU {
  int fa[N], siz[N], top;
  pair<int, int> stk[N];

  void init(int n) {
    for (int i = 0; i <= n; i++) {
      fa[i] = i;
      siz[i] = 1;
    }
    top = 0;
  }

  void _undo() {
    int u = stk[top].first, v = stk[top].second;
    fa[u] = u, siz[v] -= siz[u];
    --top;
  }
  void undo(int lst) {
    while (top > lst) _undo();
  }

  int find(int u) { return u == fa[u] ? u : find(fa[u]); }
  void merge(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return;
    if (siz[pu] > siz[pv]) swap(pu, pv);
    siz[pv] += siz[pu], fa[pu] = pv;
    stk[++top] = make_pair(pu, pv);
  }

  inline bool check(int u, int v) { return find(u) == find(v); }
} dsu;

struct Opt {
  int u, v;
} op[N];

struct node {
  int l, r;
  vector<int> os;
} t[N << 2];

void build(int x, int l, int r) {
  t[x].l = l, t[x].r = r;
  t[x].os.clear();
  if (l == r) return;
  int mid = (l + r) >> 1;
  build(x<<1, l, mid);
  build(x<<1|1, mid+1, r);
}
void upd(int x, int ql, int qr, int o) {
  int l = t[x].l, r = t[x].r;
  if (ql <= l && r <= qr) {
    t[x].os.push_back(o);
    return;
  }
  int mid = (l + r) >> 1;
  if (ql <= mid) upd(x<<1, ql, qr, o);
  if (mid < qr) upd(x<<1|1, ql, qr, o);
}

bool ans[N];
int n, m, K;

void solve(int x) {
  int l = t[x].l, r = t[x].r;
  int lst = dsu.top;
  for (auto oid : t[x].os) {
    int u = op[oid].u, v = op[oid].v;
    if (dsu.check(u, v)) {
      for (int i = l; i <= r; i++) ans[i] = false;
      dsu.undo(lst);
      return;
    }
    dsu.merge(u, v + n), dsu.merge(u + n, v);
  }
  if (l == r) {
    ans[l] = true;
    dsu.undo(lst);
    return;
  }
  solve(x<<1), solve(x<<1|1);
  dsu.undo(lst);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m >> K;
  dsu.init(n << 1);
  build(1, 1, K);
  for (int i = 1; i <= m; i++) {
    int l, r;
    cin >> op[i].u >> op[i].v >> l >> r;
    ++l;
    upd(1, l, r, i);
  }
  solve(1);
  for (int i = 1; i <= K; i++) puts(ans[i] ? "Yes" : "No");
  return 0;
}