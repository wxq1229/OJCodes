#include <bits/stdc++.h>

using namespace std;

const int N = 5e4 + 10;
                     
struct point {
  long long x;
  long long y;
  point(long long _x = 0, long long _y = 0) : x(_x), y(_y) { }
};

ostream& operator<<(ostream& stream, const point& p) {
  stream << "{" << p.x << ", " << p.y << "}";
  return stream;
}

point operator+(const point& a, const point& b) {
  return point(a.x + b.x, a.y + b.y);
}
point operator-(const point& a, const point& b) {
  return point(a.x - b.x, a.y - b.y);
}
long long operator*(const point& a, const point& b) {
  return a.x * b.y - a.y * b.x;
}

int n, m;
struct edge {
  int u, v, w;
  point p;
  bool operator<(const edge& other) const {
    return w < other.w;
  }
} e[N], ek[N];

int fa[N];
int find(int u) {
  return u == fa[u] ? u : fa[u] = find(fa[u]);
}
point kruskal() {
  for (int i = 1; i <= n; i++) {
    fa[i] = i;
  }
  point ans(0, 0);
  int cnt = n;
  for (int i = 1; i <= m; i++) {
    int u = ek[i].u, v = ek[i].v;
    int pu = find(u), pv = find(v);
    if (pu == pv) {
      continue;
    }
    fa[pu] = pv;
    ans = ans + ek[i].p;
    --cnt;
    if (cnt == 1) {
      break;
    }
  }
  return ans;
} 
  
point ans(1e9, 1e9);

void update(point& p, point q) {
  long long costp = p.x * p.y;
  long long costq = q.x * q.y;
  if (costq < costp || (costq == costp && q.x < p.x)) {
    p = q;
  }
}

void solve(point A, point B) {
//  cerr << A << " " <	< B << '\n';
  update(ans, A), update(ans, B);
  for (int i = 1; i <= m; i++) {
    ek[i] = e[i];
    ek[i].w = (A.y - B.y) * e[i].p.x + (B.x - A.x) * e[i].p.y;
  }
  sort(ek + 1, ek + m + 1);
  point C = kruskal();
  if ((B - A) * (C - A) >= 0) {
    return;
  }
  solve(A, C), solve(C, B);
}
                                     
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    cin >> e[i].u >> e[i].v >> e[i].p.x >> e[i].p.y;
    ++e[i].u;
    ++e[i].v;
  }
  for (int i = 1; i <= m; i++) {
    ek[i] = e[i];
    ek[i].w = e[i].p.x;
  }
  sort(ek + 1, ek + m + 1);
  point A = kruskal();
  for (int i = 1; i <= m; i++) {
    ek[i] = e[i];
    ek[i].w = e[i].p.y;
  }
  sort(ek + 1, ek + m + 1);
  point B = kruskal();
  solve(A, B);
  cout << ans.x << " " << ans.y << '\n';
  return 0;
}