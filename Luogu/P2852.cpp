#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 10, SIGMA = 514;

char s[N];  
int n, rk[N], sa[N];

void build() {
  static int cnt[N];
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= n; i++) ++cnt[s[i]];
  for (int i = 1; i <= SIGMA; i++) cnt[i] += cnt[i - 1];
  for (int i = 1; i <= n; i++) sa[cnt[s[i]]--] = i;
  rk[sa[1]] = 1;
  for (int i = 2; i <= n; i++) {
    rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
  }
  for (int k = 1; rk[sa[n]] != n; k <<= 1) {
    static int x[N], y[N], sb[N];
    for (int i = 1; i <= n; i++) {
      x[i] = rk[i];
      y[i] = i + k <= n ? rk[i + k] : 0;
    }
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) ++cnt[y[i]];
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for (int i = 1; i <= n; i++) sb[cnt[y[i]]--] = i;
    memset(cnt, 0, sizeof(cnt));
    for (int i = 1; i <= n; i++) ++cnt[x[i]];
    for (int i = 1; i <= n; i++) cnt[i] += cnt[i - 1];
    for (int i = n; i >= 1; i--) sa[cnt[x[sb[i]]]--] = sb[i];
    rk[sa[1]] = 1;
    for (int i = 2; i <= n; i++) {
      rk[sa[i]] = rk[sa[i - 1]] + (x[sa[i]] != x[sa[i - 1]] || y[sa[i]] != y[sa[i - 1]]);
    }
  }
}

int height[N];

void get_height() {
  for (int i = 1, k = 0; i <= n; i++) {
    if (k) --k;
    while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
    height[rk[i]] = k;
  }
}

inline char nc() {
  char ch = getchar(); while(isspace(ch)) ch = getchar();
  return ch;
}

int main() {
  int k;
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    int x; scanf("%d", &x);
    s[i] = x;
  }
  build(), get_height();
  multiset<int> s;
  for (int i = 2; i <= k; i++) s.insert(height[i]);
  int ans = *s.begin();
  for (int i = k + 1; i <= n; i++) {
    s.erase(s.find(height[i - k + 1]));
    s.insert(height[i]);
    ans = max(ans, *s.begin());
  }
  printf("%d\n", ans);
  return 0;
}