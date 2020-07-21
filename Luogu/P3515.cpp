#include <bits/stdc++.h>

using namespace std;

const double inf = 1e18;
const int N = 1e6 + 10;         

double a[N];

void solve(double *f, int l, int r, int pl, int pr) {
  if (l > r || pl > pr) {
    return;
  }
  auto weight = [&](int i, int j) {
    return -a[j] + a[i] + sqrt(j - i);
  };
  if (pl == pr) {
    for (int i = l; i <= r; i++) {
      f[i] = weight(pl, i);
    }
    return;
  }
  int mid = (l + r) / 2;
  int pt = -1;
  double mx = -inf;
  for (int i = pl; i <= min(mid, pr); i++) {
    if (weight(i, mid) > mx) {
      mx = weight(i, mid);
      pt = i;
    }
  }
  f[mid] = mx;
  solve(f, l, mid - 1, pl, pt);
  solve(f, mid + 1, r, pt, pr);
}

double f1[N], f2[N];
int n;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  solve(f1, 1, n, 1, n);
  reverse(a + 1, a + n + 1);
  solve(f2, 1, n, 1, n);
  reverse(f2 + 1, f2 + n + 1);
  for (int i = 1; i <= n; i++) {
    cout << (int) ceil(max(f1[i], f2[i])) << '\n';
  }
  return 0;
}                                                    