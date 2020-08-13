#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 3e5 + 10, P = 998244353;

int mpow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = (ll) a * a % P)
        if (b & 1) ans = (ll) ans * a % P;
    return ans;
}
void upd(int &x, int y) { x = x + y - P; x += x >> 31 & P; }

struct mat {
    int a[8][8], n, m;

    mat(int r = 0, int c = 0, int v = 0) {
        n = r, m = c;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) a[i][j] = v;
    }

    mat operator*(const mat &o) const {
        // cerr << n << " " << m << " " << o.n << " " << o.m << endl;
        assert(m == o.n);
        mat ans(n, o.m);
        for (int k = 0; k < m; ++k)
            for (int i = 0; i < ans.n; ++i)
                for (int j = 0; j < ans.m; ++j)
                    upd(ans.a[i][j], (ll) a[i][k] * o.a[k][j] % P);
        return ans;
    }

    mat operator*(const int &o) const {
        mat ans(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.a[i][j] = (ll) a[i][j] * o % P;
        return ans;
    }

    mat operator+(const mat &o) const {
        // cerr << n << " " << m << " " << o.n << " " << o.m << endl;
        assert(n == o.n && m == o.m);
        mat ans(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.a[i][j] = a[i][j], upd(ans.a[i][j], o.a[i][j]);
        return ans;
    }

    mat operator-(const mat &o) const {
        assert(n == o.n && m == o.m);
        mat ans(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.a[i][j] = a[i][j], upd(ans.a[i][j], P - o.a[i][j]);
        return ans;
    }
} zero, I, I2;

mat unit(int n) {
    mat ans(n, n);
    for (int i = 0; i < n; ++i)
        ans.a[i][i] = 1;
    return ans;
}

const int gn = 3, ign = (P + 1) / gn;
int rev[N], W[2][N];

void initW() {
    for (int len = 2; len < N; len <<= 1) {
        W[1][len] = mpow(gn, (P - 1) / len);
        W[0][len] = mpow(ign, (P - 1) / len);
    }
}

int glim(int n) {
    int lim = 1;
    while (lim <= n) lim <<= 1;
    return lim;
}
void fft_init(int n) {
    for (int i = 0; i < n; ++i)
        rev[i] = rev[i>>1] >> 1 | ((i&1) ? n >> 1 : 0);    
}
void fft(mat *f, int n, int flg) {
    for (int i = 0; i < n; ++i)
        if (rev[i] < i) swap(f[i], f[rev[i]]);
    for (int len = 2; len <= n; len <<= 1) {
        int k = len >> 1, wn = W[flg==1][len];
        for (int i = 0; i < n; i += len)
            for (int w = 1, j = i; j < i + k; j++, w = (ll) w * wn % P) {
                mat tmp = f[j + k] * w;
                f[j + k] = f[j] - tmp;
                f[j] = f[j] + tmp;
            }
    }
    if (flg == -1) {
        int inv = mpow(n, P - 2);
        for (int i = 0; i < n; ++i)
            f[i] = f[i] * inv;
    }
}

void poly_inv(const mat *f, int n, mat *g) {
    if (n == 1) { g[0] = I; return; }
    poly_inv(f, (n + 1) >> 1, g);
    static mat tf[N];
    int lim = glim((n - 1) << 1);
    for (int i = 0; i < lim; ++i) {
        tf[i] = i < n ? f[i] : zero;
        g[i] = i < n ? g[i] : zero;
    }
    fft_init(lim);
    fft(tf, lim, 1), fft(g, lim, 1);
    for (int i = 0; i < lim; ++i) g[i] = g[i] * (I2 - tf[i]*g[i]);
    fft(g, lim, -1);
    for (int i = n; i < lim; ++i) g[i] = zero;
}

mat f[N], ans[N];
int n, m, mv, Q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    initW();
    cin >> n >> m >> Q >> mv;
    zero = mat(n, n);
    int MLIM = glim(mv << 1);
    for (int i = 0; i <= MLIM; ++i) ans[i] = f[i] = zero;
    f[0] = I = unit(n);
    I2 = I * 2;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        upd(f[w].a[u][v], P - 1);
    }
    poly_inv(f, mv + 1, ans);
    while (Q--) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        cout << ans[w].a[u][v] << '\n';
    }
    return 0;
}