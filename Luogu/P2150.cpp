#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename A, typename B, typename C>
ostream &operator<<(ostream &os, const tuple<A, B, C> &a) {
    return os << "{" << get<0>(a) << ", " << get<1>(a) << ", " << get<2>(a) << "}";
}
template <typename T>
ostream & operator<<(ostream &os, const vector<T> &a) {
    os << "{";
    bool first = 1;
    for (auto v : a) {
        if (first) first = 0;
        else os << ", ";
        os << v;
    }
    os << "}";
    return os;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    const vector<int> ps = {2, 3, 5, 7, 11, 13, 17, 19};
    int n;
    ll P;
    cin >> n >> P;
    --n;
    auto upd = [&](ll &x, ll y) -> void { x += y; if (x >= P) x -= P; };
    vector<tuple<int, int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        int s = 0;
        for (int j = 0; j < (int) ps.size(); ++j)
            if ((i + 2) % ps[j] == 0) s |= 1 << j;
        int mxp = 1, tmp = i + 2;
        for (int j = 2; j * j <= tmp; ++j) while (tmp % j == 0) tmp /= j;
        if (tmp > 19) mxp = tmp;
        a[i] = make_tuple(mxp, i + 2, s);
    }
    sort(a.begin(), a.end());
    // cerr << a << '\n';
    vector<vector<ll>> dp(1 << 8, vector<ll>(1 << 8));
    dp[0][0] = 1;
    vector<vector<vector<ll>>> f(2, vector<vector<ll>>(1 << 8, vector<ll>(1 << 8)));
    for (int i = 0; i < (int) a.size(); ++i) {
        if (i == 0 || get<0>(a[i]) != get<0>(a[i - 1]) || get<0>(a[i - 1]) == 1) {
            f[0] = f[1] = dp;
        }
        auto new_f = f;
        for (int s0 = 0; s0 < (1 << 8); ++s0)
            for (int s1 = 0; s1 < (1 << 8); ++s1) {
                int t = get<2>(a[i]);
                if ((s0 & t) == 0) upd(new_f[1][s0][s1 | t], f[1][s0][s1]);
                if ((s1 & t) == 0) upd(new_f[0][s0 | t][s1], f[0][s0][s1]);
            }
        swap(f, new_f);
        if (i == (int) a.size() - 1 || get<0>(a[i + 1]) != get<0>(a[i]) || get<0>(a[i + 1]) == 1) {
            for (int s0 = 0; s0 < (1 << 8); ++s0)
                for (int s1 = 0; s1 < (1 << 8); ++s1) {
                    ll tmp = dp[s0][s1];
                    dp[s0][s1] = f[0][s0][s1];
                    upd(dp[s0][s1], f[1][s0][s1]);
                    upd(dp[s0][s1], P - tmp);
                }
        }
    }
    ll ans = 0;
    for (int s0 = 0; s0 < (1 << 8); ++s0)
        for (int s1 = 0; s1 < (1 << 8); ++s1) if ((s0 & s1) == 0 && dp[s0][s1])
            upd(ans, dp[s0][s1]);
    cout << ans << '\n';
    return 0;
}