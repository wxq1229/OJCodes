#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

struct DSU {
  int fa[N], siz[N], block, top;
  int stk[N][2];
  
  void merge(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return;
    if (siz[pu] > siz[pv]) swap(pu, pv);
    fa[pu] = pv, siz[pv] += siz[pu];
    --block;
    stk[++top][0] = pu;
    stk[top][1] = pv;
  }
  int find(int u) { while (u ^ fa[u]) u = fa[u]; return u; }
  
  void undo(int lst) { 
    while (top > lst) {
      int u = stk[top][0], v = stk[top][1];
      fa[u] = u, siz[v] -= siz[u];
      --top;
      ++block;
    } 
  }
  
  void init(int n) {
    for (int i = 1; i <= n; i++) {
      siz[i] = 1;
      fa[i] = i;
    }
    top = 0;
    block = n;
  }
} dsu;

struct event {
  int u, v;
} evt[N << 1];

struct node {
  int l, r;
  vector<int> evs;
} t[444444];

void build(int x, int l, int r) {
  t[x].l = l, t[x].r = r;
  if (l == r) return;
  int mid = (l + r) >> 1;
  build(x<<1, l, mid);
  build(x<<1|1, mid + 1, r);
}

void upd(int x, int ql, int qr, int id) {
  int l = t[x].l, r = t[x].r;
  if (ql <= l && r <= qr) {
    t[x].evs.push_back(id);
    return;
  }
  int mid = (l + r) >> 1;
  if (ql <= mid) upd(x<<1, ql, qr, id);
  if (mid < qr) upd(x<<1|1, ql, qr, id);
}

int n;

void solve(int x) {
  int l = t[x].l, r = t[x].r;
  int lst = dsu.top;
  for (unsigned i = 0; i < t[x].evs.size(); i++) {
    int id = t[x].evs[i];
    int u = evt[id].u, v = evt[id].v;
    dsu.merge(u, v);
    if (dsu.block == 1) {
      printf("%d\n", l);
      exit(0);
    }
  }
  if (l < r) solve(x<<1), solve(x<<1|1);
  dsu.undo(lst);
}

inline char nc() {
  const int SZ = 1 << 10;
  static char buf[SZ], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SZ, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T> inline T rd() {
  T x = 0; char ch = nc(); bool f = 1;
  while (!isdigit(ch)) { f ^= ch == '-'; ch = nc(); }
  while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = nc(); }
  return f ? x : -x;
}
#define gi rd<int>

int main() {
  int m;
  n = gi(), m = gi();
  dsu.init(n);
  int lim = 100000;
  build(1, 0, lim);
  for (int i = 1; i <= m; i++) {
    evt[i].u = gi(), evt[i].v = gi();
    int w = gi();
    if (0 <= w - 1) upd(1, 0, w - 1, i);
    if (w + 1 <= lim) upd(1, w + 1, lim, i);
 }
  solve(1);
  return 0;
}