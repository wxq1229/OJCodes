#include <bits/stdc++.h>
using namespace std;

struct matrix {
    int n, m, a[3][3];

    matrix(int r = 0, int c = 0) {
        n = r, m = c;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                a[i][j] = 0;
    }

    matrix operator*(const matrix &o) const {
        assert(m == o.n);
        matrix ans(n, o.m);
        for (int k = 0; k < m; ++k)
            for (int i = 0; i < ans.n; ++i)
                for (int j = 0; j < ans.m; ++j)
                    ans.a[i][j] += a[i][k] * o.a[k][j];
        return ans;
    }

    matrix &operator*=(const matrix &o) { return (*this) = (*this) * o; }

    const int *operator[](int i) const { return a[i]; }
    int *operator[](int i) { return a[i]; }

    bool operator==(const matrix &o) const {
        if (n != o.n || m != o.m) return false;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (a[i][j] != o[i][j]) return false;
        return true;
    }

    int operator()() const { return a[1][0]; }
};
matrix unit(int n) {
    matrix ans(n, n);
    for (int i = 0; i < n; ++i)
        ans.a[i][i] = 1;
    return ans;
}
const matrix I = unit(3);

const int N = 1e5 + 10;
struct node {
    int l, r;
    matrix mat, mul;
} t[N << 2];

void pushdown(int x) {
    if (t[x].mul == I) return;
    t[x << 1].mul = t[x].mul * t[x << 1].mul;
    t[x << 1 | 1].mul = t[x].mul * t[x << 1 | 1].mul;
    t[x << 1].mat = t[x].mul * t[x << 1].mat;
    t[x << 1 | 1].mat = t[x].mul * t[x << 1 | 1].mat;
    t[x].mul = I;
}

void build(int x, int l, int r) {
    t[x].l = l, t[x].r = r;
    t[x].mat = matrix(3, 1);
    t[x].mat[2][0] = 1;
    t[x].mul = I;
    if (l == r) return;
    int mid = (l + r) >> 1;
    build(x << 1, l, mid);
    build(x << 1 | 1, mid + 1, r);
}

void upd(int x, int ql, int qr, const matrix &mat) {
    int l = t[x].l, r = t[x].r;
    if (ql <= l && r <= qr) {
        t[x].mul = mat * t[x].mul;
        t[x].mat = mat * t[x].mat;
        return;
    }
    pushdown(x);
    int mid = (l + r) >> 1;
    if (ql <= mid) upd(x << 1, ql, qr, mat);
    if (mid < qr) upd(x << 1 | 1, ql, qr, mat);
}

matrix qry(int x, int p) {
    int l = t[x].l, r = t[x].r;
    if (l == r) return t[x].mat;
    pushdown(x);
    int mid = (l + r) >> 1;
    if (p <= mid) return qry(x << 1, p);
    else return qry(x << 1 | 1, p);
}

vector<int> g[N];

int top[N], fa[N], siz[N], son[N], dep[N], tim, dfn[N];

void dfs1(int u, int f) {
    fa[u] = f;
    dep[u]= dep[f] + 1;
    siz[u] = 1;
    siz[son[u] = 0] = 0;
    for (auto v : g[u]) {
        if (v == f) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > siz[son[u]]) son[u] = v;
    }
}
void dfs2(int u, int topf) {
    top[u] = topf;
    dfn[u] = ++tim;
    if (!son[u]) return;
    dfs2(son[u], topf);
    for (auto v : g[u]) if (v != fa[u] && v != son[u])
        dfs2(v, v);
}

void upd_link(int u, int v, const matrix &mat) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        upd(1, dfn[top[u]], dfn[u], mat);
        u = fa[top[u]];
    }
    if (dfn[u] > dfn[v]) swap(u, v);
    upd(1, dfn[u], dfn[v], mat);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    build(1, 1, n);
    cin >> m;
    while (m--) {
        int opt, x;
        cin >> opt >> x;
        if (opt == 3) {
            matrix ans = qry(1, dfn[x]);
            cout << ans() << '\n';
        } else {
            int d;
            cin >> d;
            matrix tmp = I;
            if (opt == 1) tmp[0][2] = d;
            else tmp[1][0] = d;
            upd_link(1, x, tmp);
        }
    }
    return 0;
}