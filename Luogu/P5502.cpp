#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10;

long long a[N];
               
long long solve(int l, int r) {
  if (l == r) {
    return a[l];
  }
  int mid = (l + r) >> 1;
  long long ans = max(solve(l, mid), solve(mid + 1, r));
  int cur = mid;
  long long d = 0;
  for (int i = mid + 1; i <= r; i++) {
    d = gcd(d, a[i]);
    while (cur >= l && a[cur] % d == 0) --cur;
    ans = max(ans, d * (i - cur));
  }
  d = 0;
  cur = mid + 1;
  for (int i = mid; i >= l; i--) {
    d = gcd(d, a[i]);
    while (cur <= r && a[cur] % d == 0) ++cur;
    ans = max(ans, d * (cur - i));
  }
  return ans;
}
  
int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }    
  cout << solve(1, n) << '\n';
  return 0;
}
