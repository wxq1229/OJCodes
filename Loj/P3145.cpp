#pragma GCC optimize(2)
#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;

struct DSU {
  int fa[N], siz[N], n, top;
  pair<int,int> stk[N];

  void init(int vs = 0) {
    n = vs;
    for (int i = 1; i <= n; i++) fa[i] = i, siz[i] = 1;
    top = 0;
  }
  DSU(int vs = 0) { init(vs); }
  
  int find(int u) { return u == fa[u] ? u : find(fa[u]); }
  void merge(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return;
    if (siz[pu] > siz[pv]) swap(pu, pv);
    fa[pu] = pv, siz[pv] += siz[pu];
    stk[++top] = make_pair(pu, pv);
  }

  int qry(int u) { return siz[find(u)]; }

  void _undo() {
    int u = stk[top].first, v = stk[top].second;
    siz[v] -= siz[u], fa[u] = u;
    --top;
  }
  void undo(int lst) { while (top > lst) _undo(); }
} dsu;  

int n, m, Q;

struct edge { 
  int u, v, w; 
} e[N];

struct Query {
  int opt, u, w, id, tim;
} q[N];

int ans[N];
int une[N], qs[N], os[N], lstw[N];

void solve(int ql, int qr) {
  dsu.init(n);
  vector<bool> vis(m + 1, 0);
  // vector<int> une, qs, os;
  int qs_cnt = 0, os_cnt = 0, une_cnt = 0;
  for (int i = ql; i <= qr; i++) {
    if (q[i].opt == 1) {
      os[++os_cnt] = i;
      vis[q[i].u] = 1;
    } else {
      qs[++qs_cnt] = i;
    }
  }
  for (int i = 1; i <= m; i++) if (!vis[i]) {
    une[++une_cnt] = i;
  }
  for (int i = 1; i <= os_cnt; i++) {
    int eid = q[os[i]].u;
    q[Q + eid] = (Query){1, eid, e[eid].w, 0, 0};
    os[i + os_cnt] = Q + eid;
  }
  os_cnt <<= 1;
  sort(qs + 1, qs + qs_cnt + 1, [&](int i, int j) { return q[i].w > q[j].w; });
  sort(une + 1, une + une_cnt + 1, [&](int i, int j) { return e[i].w > e[j].w; });
  sort(os + 1, os + os_cnt + 1, [&](int i, int j) { return q[i].tim < q[j].tim; });
  // for (auto eid : une) {
    // cerr << "{" << e[eid].u << ", " << e[eid].v << ", " << e[eid].w << "}\n";
  // }
  int cur = 1;
  for (int qqi = 1; qqi <= qs_cnt; ++qqi) {
    int qid = qs[qqi];
    int u = q[qid].u, w = q[qid].w, id = q[qid].id, tim = q[qid].tim;
    // cerr << "Qry {" << u << ", " << w << ", " << id << ", " << tim << "}\n";
    while (cur <= une_cnt && e[une[cur]].w >= w) {
      // cerr << "merge " << e[une[cur]].u << ", " << e[une[cur]].v << '\n';
      dsu.merge(e[une[cur]].u, e[une[cur]].v);
      ++cur;
    }
    int lst = dsu.top;
    for (int ooi = 1; ooi <= os_cnt; ++ooi) {
      int oid = os[ooi];
      if (q[oid].tim < tim) {
        lstw[q[oid].u] = q[oid].w;
      }
      else break;
    }
    for (int ooi = 1; ooi <= os_cnt; ++ooi) {
      int oid = os[ooi];
      if (q[oid].tim > tim) break;
      if (lstw[q[oid].u] >= w) {
        int u = e[q[oid].u].u, v = e[q[oid].u].v;
        dsu.merge(u, v);
      }
    }
    for (int ooi = 1; ooi <= os_cnt; ++ooi) {
      int oid = os[ooi];
      lstw[q[oid].u] = 0;
    }
    ans[id] = dsu.qry(u);
    dsu.undo(lst);
    // cerr << "---------------------------------\n";
  }
  for (int ooi = 1; ooi <= os_cnt; ooi++) {
    int oid = os[ooi];
    e[q[oid].u].w = q[oid].w;
  }
}

inline char nc() {
  const int SZ = 1 << 17;
  static char buf[SZ], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SZ, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T> inline T rd() {
  T x = 0; char ch = nc(); bool f = 1;
  while (!isdigit(ch)) { f ^= ch == '-'; ch = nc(); }
  while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = nc(); }
  return f ? x : -x;
}
#define gi rd<int>

int main() {
#ifdef LOCAL
  double STIME = clock();
#endif
  n = gi(), m = gi();
  // printf("%d %d\n", n, m);
  for (int i = 1; i <= m; i++) {
    e[i].u = gi(), e[i].v = gi(), e[i].w = gi();
  }
  Q = gi(); int qt = 0;
  for (int i = 1; i <= Q; i++) {
    q[i].opt = gi(), q[i].u = gi(), q[i].w = gi();
    if (q[i].opt == 2) {
      q[i].id = ++qt;
    }
    q[i].tim = i;
  } 
  int B = 1234;
  for (int i = 1; i <= Q; i += B) {
    solve(i, min(Q, i + B - 1));
  }
  for (int i = 1; i <= qt; i++) {
    printf("%d\n", ans[i]);
  }
#ifdef LOCAL
  cerr << "Time used: " << (clock() - STIME) / CLOCKS_PER_SEC << " s\n";
#endif
  return 0;
}