#include <bits/stdc++.h>

using namespace std;

typedef double db;
const db INF = 1e10;

struct segment {
  db l, r, k, b;
} seg[100010];
int cnt;

inline db f(int id, db x) {
  if (!id) return -INF;
  return seg[id].k * x + seg[id].b;
}

void addseg(int x0, int y0, int x1, int y1) {
  if (x0 > x1 || (x0==x1 && y0>y1)) swap(x0,x1), swap(y0,y1);
  ++cnt;
  seg[cnt].l = x0, seg[cnt].r = x1;
  seg[cnt].k = x0==x1 ? 0 : 1.0*(y1-y0)/(x1-x0);
  seg[cnt].b = y1 - x1 * seg[cnt].k;
}

db cmpx;
inline bool cmp(int i, int j) {
  return f(i, cmpx) > f(j, cmpx) || (f(i,cmpx) == f(j,cmpx) && i<j);
}
inline int segmax(int i, int j) { return cmp(i,j) ? i : j; }

struct node {
  int l, r, mx;
} t[400010];

void ins(int x, int id) {
  int l = t[x].l, r = t[x].r, ql = seg[id].l, qr = seg[id].r;
  int mid = (l + r) >> 1;
  cmpx = mid;
  if (l == r) {
    t[x].mx = segmax(t[x].mx, id);
    return;
  }
  if (!t[x].mx) {
    t[x].mx = id;
    return;
  }
  if (seg[id].k > seg[t[x].mx].k) {
    if (cmp(id, t[x].mx)) ins(x<<1, t[x].mx), t[x].mx = id;
    else ins(x<<1|1, id);
  } else {
    if (cmp(id, t[x].mx)) ins(x<<1|1, t[x].mx), t[x].mx = id;
    else ins(x<<1, id);
  }
}

void update(int x, int id) {
  int l = t[x].l, r = t[x].r, ql = seg[id].l, qr = seg[id].r;
  if (ql <= l && r <= qr) { ins(x, id); return; }
  int mid = (l + r) >> 1;
  if (ql <= mid) update(x<<1, id);
  if (mid < qr) update(x<<1|1, id);
}

int query(int x, int p) {
  cmpx = p; int l = t[x].l, r = t[x].r, mid = (l+r) >> 1, ans = t[x].mx;
  if (l == r) return ans;
  if (p <= mid) ans = segmax(ans, query(x<<1, p));
  else ans = segmax(ans, query(x<<1|1, p));
  return ans;
}

void build(int x, int l, int r) {
  t[x] = (node){l, r, 0};
  if (l == r) return;
  int mid = (l + r) >> 1;
  build(x<<1, l, mid);
  build(x<<1|1, mid + 1, r);
}

int main() {
  build(1, 1, 40000);
  int _, lstans = 0;
  auto decode = [&](int &x, int mod) { x = (x + lstans - 1) % mod + 1; };
  scanf("%d", &_); while (_--) {
    int opt; scanf("%d", &opt);
    if (opt == 0) {
      int p; scanf("%d", &p);
      decode(p, 39989);
      printf("%d\n", lstans = query(1, p));
    } else {
      int x0, y0, x1, y1; scanf("%d%d%d%d", &x0, &y0, &x1, &y1);
      decode(x0, 39989), decode(x1, 39989);
      decode(y0, 1e9), decode(y1, 1e9);
      addseg(x0, y0, x1, y1);
      update(1, cnt);
    }
  }
  return 0;
}
