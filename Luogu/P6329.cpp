#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10, maxn = 100000, inf = 0x3f3f3f3f;

struct SegTree {
  int sum[N * 233], lc[N * 233], rc[N * 233], cnt = 0;

  void modify(int &x, int l, int r, int p, int v) {
    if (!x) x = ++cnt;
    sum[x] += v;
    if (l == r) {
      return;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) modify(lc[x], l, mid, p, v);
    else modify(rc[x], mid + 1, r, p, v);
  }

  int query(int x, int l, int r, int ql, int qr) {
    if (ql > qr || l > r || !x) return 0;
    if (ql <= l && r <= qr) {
      return sum[x];
    }
    int mid = (l + r) >> 1, ans = 0;
    if (ql <= mid) ans += query(lc[x], l, mid, ql, qr);
    if (mid < qr) ans += query(rc[x], mid + 1, r, ql, qr);
    return ans;
  }
} T;
int rts[N], rtf[N];
            
int n, m, wei[N];
vector<int> e[N];

struct graph {
  int fa[N], siz[N], son[N], depth[N], top[N];
             
  void dfs1(int u, int f) {
    fa[u] = f;
    depth[u] = depth[f] + 1;
    siz[u] = 1;
    siz[son[u] = 0] = 0;
    for (auto v : e[u]) {
      if (v != f) {
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
      }
    }
  }
  void dfs2(int u, int topf) {
    top[u] = topf;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto v : e[u]) if (v != son[u] && v != fa[u]) {
      dfs2(v, v);
    }
  }

  void init() {
    depth[0] = 0;
    dfs1(1, 0);
    dfs2(1, 1);
  }

  int lca(int u, int v) {
    while (top[u] != top[v]) {
      if (depth[top[u]] > depth[top[v]]) u =fa[top[u]];
      else v = fa[top[v]]; 
    }
    return depth[u] < depth[v] ? u : v;
  }

  int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];	
  }
} g;

int siz[N], fa[N], rt, mx[N], all;
bool vis[N];

void getrt(int u, int f) {
  siz[u] = 1, mx[u] = 0;
  for (auto v : e[u]) {
    if (!vis[v] && v != f) {
      getrt(v, u);
      siz[u] += siz[v];
      mx[u] = max(mx[u], siz[v]);
    }
  }
  mx[u] = max(mx[u], all - siz[u]);
  if (mx[u] < mx[rt]) rt = u;
}

void getd(int u, int f, int d, int &t1, int &t2) {
  T.modify(t1, 0, maxn, d, wei[u]);
  T.modify(t2, 0, maxn, d, wei[u]);
  for (auto v : e[u]) {
    if (!vis[v] && v != f) {
      getd(v, u, d + 1, t1, t2);
    } 
  }
}

void dfs(int u) {             
  vis[u] = 1;
  for (auto v : e[u]) {
    if (!vis[v]) {
      mx[rt = 0] = inf;
      all = siz[v];
      getrt(v, u);
      getd(v, u, 1, rts[u], rtf[rt]);
      fa[rt] = u, dfs(rt);
    }
  }
  T.modify(rts[u], 0, maxn, 0, wei[u]);
}

void init() {
  mx[rt = 0] = inf;
  all = n;
  getrt(1, 0);
  dfs(rt);
}

void modify(int u, int w) {
  for (int v = u; v; v = fa[v]) {
    int d = g.dist(u, v);
    T.modify(rts[v], 0, maxn, d, -wei[u]); 
    int f = fa[v];
    if (f) {
      int df = g.dist(u, f);
 	  T.modify(rtf[v], 0, maxn, df, -wei[u]);
    }
  }
  wei[u] = w;
  for (int v = u; v; v = fa[v]) {
    int d = g.dist(u, v);
    T.modify(rts[v], 0, maxn, d, wei[u]); 
    int f = fa[v];
    if (f) {
      int df = g.dist(u, f);
 	  T.modify(rtf[v], 0, maxn, df, wei[u]);
    }
  }
}

int query(int u, int k) {
  int ans = T.query(rts[u], 0, maxn, 0, k);
  for (int v = u; fa[v]; v = fa[v]) {
    int f = fa[v], d = g.dist(u, f);
    ans += T.query(rts[f], 0, maxn, 0, k - d);
    ans -= T.query(rtf[v], 0, maxn, 0, k - d); 
  }
  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    cin >> wei[i];
  }
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  g.init(), init();
  int lstans = 0;
  while (m--) {
    int opt, x, y;
    cin >> opt >> x >> y;
    x ^= lstans, y ^= lstans;
    if (opt == 0) {
      cout << (lstans = query(x, y)) << '\n';
    } else {
      modify(x, y);
    }
  }   
  return 0;
}