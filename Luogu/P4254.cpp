#include <bits/stdc++.h>

using namespace std;

typedef double db;
const int N = 5e4 + 10;

struct line {
  db k, b;
  inline db operator () (db x) const { return k * x + b; }
};

struct node {
  int l, r;
  line f;
} t[N << 2];

void build(int x, int l, int r) {
  t[x] = {l, r, line()};
  if (l == r) return;
  int mid = (l+r) >> 1;
  build(x<<1, l, mid);
  build(x<<1|1, mid + 1, r);
}

void update(int x, line g) {
  int l = t[x].l, r = t[x].r; line &f = t[x].f;
  if (l == r) {
    if (f(l) < g(l)) f = g;
    return;
  }
  int mid = (l + r) >> 1;
  if (g.k > f.k) {
    if (f(mid) < g(mid)) update(x<<1, f), f = g;
    else update(x<<1|1, g);
  } else {
    if (f(mid) < g(mid)) update(x<<1|1, f), f = g;
    else update(x<<1, g);
  }
}

db query(int x, int p) {
  int l = t[x].l, r = t[x].r; db ans = t[x].f(p);
  if (l == r) return ans;
  int mid = (l + r) >> 1;
  if (p <= mid) ans = max(ans, query(x<<1, p));
  else ans = max(ans, query(x<<1|1, p));
  return ans;
}

int main() {
  char s[23];
  build(1, 1, 50000);
  int _; for (scanf("%d", &_); _; _--) {
    scanf("%s", s);
    if (s[0] == 'P') {
      db b, k; scanf("%lf%lf", &b, &k);
      update(1, (line) {k, b});
    } else {
      int x; scanf("%d", &x);
      printf("%d\n", (int) (query(1, x - 1) / 100));
    }
  }
  return 0;
}
