#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll inf = 0x3f3f3f3f3f3f3f3f;

struct matrix {
    int n, m;
    ll a[255][255];

    matrix(int r = 0, int c = 0, ll v = -inf) {
        n = r, m = c;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = v;
    }

    const ll* operator[](int i) const { return a[i]; }
    ll* operator[](int i) { if (!(0 <= i && i < n)) cerr << i << '\n'; assert(0 <= i && i < n); return a[i]; }

    friend matrix operator*(const matrix &a, const matrix &b) {
        assert(a.m == b.n);
        matrix ans(a.n, b.m);
        for (int k = 0; k < a.m; ++k)
            for (int i = 0; i < ans.n; ++i)
                for (int j = 0; j < ans.m; ++j)
                    ans[i][j] = max(ans[i][j], a[i][k] + b[k][j]);
        return ans;
    }
};

struct event {
    int t, x, y;
    bool operator<(const event &o) const {
        return t < o.t;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m, T, K;
    cin >> n >> m >> T >> K;
    vector<ll> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    matrix A(n * 5, n * 5);
    auto id = [&](int u, int t) {
        return u + t * n;
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            A[id(i, j)][id(i, j + 1)] = 0;
        }
    }
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u;
        --v;
        A[id(v, 4)][id(u, 5 - w)] = max(A[id(v, 4)][id(u, 5 - w)], c[v]);
    }
    const int LOG = 30;
    vector<matrix> pw(LOG);
    pw[0] = A;
    for (int i = 1; i < LOG; ++i) {
        pw[i] = pw[i - 1] * pw[i - 1];
    }
    vector<event> events(K);
    for (int i = 0; i < K; ++i) {
        cin >> events[i].t >> events[i].x >> events[i].y;
        --events[i].x;
    }
    sort(events.begin(), events.end());
    int lst = 0;
    matrix F(5 * n, 1);
    F[id(0, 4)][0] = c[0];
    for (auto evt : events) {
        // cerr << evt.t << " " << evt.x << " " << evt.y << '\n';
        int delta = evt.t - lst;
        lst = evt.t;
        for (int i = LOG - 1; i >= 0; --i)
            if (delta & (1 << i)) F = pw[i] * F;
        F[id(evt.x, 4)][0] += evt.y;
    }
    int delta = T - lst;
    for (int i = LOG - 1; i >= 0; --i)
        if (delta & (1 << i)) F = pw[i] * F;
    if (F[id(0, 4)][0] < 0) cout << "-1\n";
    else cout << F[id(0, 4)][0] << '\n';
    return 0;
}