#include <bits/stdc++.h>

constexpr int N = 2e5 + 10;
int fenw[N];
void mdf(int x, int v) {
    for (++x; x < N; x += x & -x)
        fenw[x] = std::max(fenw[x], v);
}
int qry(int x) {
    int ans = 0;
    for (++x; x; x -= x & -x)
        ans = std::max(ans, fenw[x]);
    return ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    int tt;
    std::cin >> tt;
    while (tt--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i)
            std::cin >> a[i];
        std::vector<int> pre(n), suf(n);
        pre[0] = 1;
        for (int i = 1; i < n; ++i)
            pre[i] = a[i] > a[i - 1] ? pre[i - 1] + 1 : 1;
        suf[n - 1] = 1;
        for (int i = n - 2; i >= 0; --i)
            suf[i] = a[i] < a[i + 1] ? suf[i + 1] + 1 : 1;

        std::map<int, int> idx;
        for (auto v : a) idx[v] = 1;
        int tot = 0;
        for (auto &p : idx) p.second = tot++;
        for (auto &v : a) v = idx[v];

        std::memset(fenw, 0, sizeof fenw);
        int ans = -0x3f3f3f3f;
        for (int i = 0; i < n; ++i) {
            if (a[i] > 0) ans = std::max(ans, suf[i] + qry(a[i] - 1));
            mdf(a[i], pre[i]);
            ans = std::max(ans, pre[i]);
        }
        std::cout << ans << '\n';
    }
    return 0;
}