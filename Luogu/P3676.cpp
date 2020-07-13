#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

vector<int> g[N];
int n;
int fa[N], siz[N], son[N], depth[N], top[N], dfn[N], tim;
long long wei[N], sum[N];

void dfs1(int u, int f) {
  fa[u] = f;
  siz[u] = 1;
  sum[u] = wei[u];
  depth[u] = depth[f] + 1;
  siz[son[u] = 0] = 0;
  for (auto v : g[u]) if (v ^ f) {
    dfs1(v, u);
    siz[u] += siz[v], sum[u] += sum[v];
    if (siz[v] > siz[son[u]]) {
      son[u] = v;
    }
  }
}
void dfs2(int u, int f) {
  top[u] = f;
  dfn[u] = ++tim;
  if (!son[u]) return;
  dfs2(son[u], f);
  for (auto v : g[u]) if (v != fa[u] && v != son[u]) {
    dfs2(v, v);
  }
}

struct info {
  long long s1, s2;
  info operator+(const info &other) const {
    info res = *this;
    res.s1 += other.s1;
    res.s2 += other.s2;
    return res;
  }
  info &operator+=(const info &other) {
    *this = *this + other;
    return *this;
  }
};                    


struct SegTree {
  struct node {
    int l, r;
    long long s1, s2, add;
  } t[N << 2];

  void pushup(int x) {
    int lc = x << 1, rc = x << 1 | 1;
    t[x].s1 = t[lc].s1 + t[rc].s1;
    t[x].s2 = t[lc].s2 + t[rc].s2;
  }
  void padd(int x, long long v) {
    int l = t[x].l, r = t[x].r;
    t[x].s2 += 2 * t[x].s1 * v + (r - l + 1) * v * v;
    t[x].s1 += v * (r - l + 1);
    t[x].add += v;
  }
  void pushdown(int x) {
    if (t[x].add) {
      padd(x<<1, t[x].add), padd(x<<1|1, t[x].add);
      t[x].add = 0;
    }
  }

  long long arr[N];
  void build(int x, int l, int r) {
    t[x].l = l, t[x].r = r;
    t[x].add = 0;
    if (l == r) {
      t[x].s1 = arr[l];
      t[x].s2 = arr[l] * arr[l];
      return;
    }
    int mid = (l + r) >> 1;
    build(x<<1, l, mid);
    build(x<<1|1, mid + 1, r);
    pushup(x);
  }

  void update(int x, int ql, int qr, long long v) {
    int l = t[x].l, r = t[x].r;
    if (ql <= l && r <= qr) {
      padd(x, v);
      return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ql <= mid) update(x<<1, ql, qr, v);
    if (mid < qr) update(x<<1|1, ql, qr, v);
    pushup(x);
  }

  info query(int x, int ql, int qr) {
    int l = t[x].l, r = t[x].r;
    if (ql <= l && r <= qr) {
      return {t[x].s1, t[x].s2};
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    info ans = {0, 0};
    if (ql <= mid) ans += query(x<<1, ql, qr);
    if (mid < qr) ans += query(x<<1|1, ql, qr);
    return ans; 
  }
} sgt;

void init(int rt = 1) {
  depth[0] = 0;
  dfs1(rt, 0);
  dfs2(rt, rt);
  for (int i = 1; i <= n; i++) {
    sgt.arr[dfn[i]] = sum[i];
  }
  sgt.build(1, 1, n);
}

void update_chain(int u, int v, long long d) {
  while (top[u] != top[v]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    } 
    sgt.update(1, dfn[top[u]], dfn[u], d);
    u = fa[top[u]];
  }
  if (dfn[u] > dfn[v]) {
    swap(u, v);
  }
  sgt.update(1, dfn[u], dfn[v], d);
}
info query_chain(int u, int v) {
  info ans = {0, 0};
  while (top[u] != top[v]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    } 
    ans += sgt.query(1, dfn[top[u]], dfn[u]);
    u = fa[top[u]];
  }
  if (dfn[u] > dfn[v]) {
    swap(u, v);
  }
  ans += sgt.query(1, dfn[u], dfn[v]);
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> n >> tt;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    cin >> wei[i];
  }
  init();  
  long long ans = sgt.query(1, 1, n).s2;
  while (tt--) {
    int opt, u;
    cin >> opt >> u;
    if (opt == 1) {
      long long v;
      cin >> v;
      update_chain(1, u, v - wei[u]);
      wei[u] = v;
      ans = sgt.query(1, 1, n).s2;
    } else {
      long long sum1 = sgt.query(1, dfn[1], dfn[1]).s1;
      cout << ans + (depth[u] - 1) * sum1 * sum1 - 2 * sum1 * query_chain(1, u).s1 + 2 * sum1 * sum1 << '\n';
    }
  }
  return 0;
}