#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int N = 1e5 + 10;

struct node {
  int lc, rc;
  ll s[5]; int cnt;
} t[N * 40];
int rt = 0, siz = 0;

void pushup(int x) {
  int lc = t[x].lc, rc = t[x].rc, ls = t[lc].cnt;
  for (int i = 0; i < 5; i++) t[x].s[i] = t[lc].s[i];
  for (int i = 0; i < 5; i++) t[x].s[(i + ls) % 5] += t[rc].s[i];
  t[x].cnt = t[lc].cnt + t[rc].cnt;
}

void insert(int &x, int l, int r, int p, int v) {
  if (!x) x = ++siz; 
  if (l == r) {
    t[x].cnt += v;
    t[x].s[1] += 1ll * l * v;
    return;
  }
  int mid = (l + r) >> 1;
  if (p <= mid) insert(t[x].lc, l, mid, p, v);
  else insert(t[x].rc, mid + 1, r, p, v);
  pushup(x);
}

int main() {
  char s[23];
  int _; for (scanf("%d", &_); _; _--) {
    scanf("%s", s);
    if (s[0] == 's') printf("%lld\n", t[rt].s[3]);
    else {
      int d = s[0] == 'd' ? -1 : 1, v;
      scanf("%d", &v);
      insert(rt, 1, 1e9, v, d);
    }
  }
  return 0;
}
