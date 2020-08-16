#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int P = 998244353;
inline int mpow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = (ll) a * a % P)
        if (b & 1) ans = (ll) ans * a % P;
    return ans;
}
const int gn = 3, ign = mpow(gn, P - 2);
const int N = 2e5 + 10;

int roots[N][2];
bool initialized = 0;
void root_init() {
    initialized = 1;
    for (int len = 1; len < N; len <<= 1) {
        roots[len][0] = mpow(ign, (P - 1) / len);
        roots[len][1] = mpow(gn, (P - 1) / len);
    }
}

vector<int> rev;
void fft(vector<int>& a, int flg) {
    if (!initialized) root_init();
    int n = a.size();
    if (rev.size() != n) {
        rev.resize(n);
        for (int i = 0; i < n; ++i)
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) ? n >> 1 : 0);
    }
    for (int i = 0; i < n; ++i)
        if (rev[i] < i) swap(a[i], a[rev[i]]);
    for (int len = 2; len <= n; len <<= 1) {
        int k = len >> 1, wn = roots[len][flg == 1];
        for (int i = 0; i < n; i += len) {
            for (int j = i, w = 1; j < i + k; ++j, w = (ll) w * wn % P) {
                int tmp = (ll) a[j + k] * w % P;
                int x = a[j] + tmp, y = a[j] - tmp;
                a[j] = x >= P ? x - P : x;
                a[j + k] = y < 0 ? y + P : y;
            }
        }
    }
    if (flg == -1) {
        int inv = mpow(n, P - 2);
        for (int i = 0; i < n; ++i)
            a[i] = (ll) a[i] * inv % P;
    }
}

struct Poly {
    vector<int> a;

    Poly() { }
    Poly(int v) {
        v %= P;
        if (v < 0) v += P;
        a = {v};
    }
    Poly(const vector<int>& v) { a = v; }
    Poly(const initializer_list<int>& l) { a = l; }

    int size() const { return a.size(); }
    int deg() const { return size() - 1; }

    int operator[](int k) const {
        if (k < 0 || k >= size()) return 0;
        else return a[k];
    }
    int& operator[](int k) { assert(0 <= k && k < size()); return a[k]; }

    Poly modxk(int k) const {
        if (a.size() <= k) return Poly(a);
        else return Poly(vector<int>(a.begin(), a.begin() + k));
    }
    Poly reverse() const {
        vector<int> res = a;
        ::reverse(res.begin(), res.end());
        return Poly(res);
    }

    friend Poly operator+(const Poly a, const Poly &b) {
        int n = max(a.size(), b.size());
        Poly ans = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = a[i] + b[i];
            if (ans[i] >= P) ans[i] -= P;
        }
        return ans;
    }
    friend Poly operator-(const Poly a, const Poly &b) {
        int n = max(a.size(), b.size());
        Poly ans = vector<int>(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = a[i] - b[i];
            if (ans[i] < 0) ans[i] += P;
        }
        return ans;
    }
    friend Poly operator*(const Poly a, const Poly &b) {
        int n = a.deg(), m = b.deg();
        int lim = 1;
        while (lim <= n + m) lim <<= 1;
        vector<int> f = a.a, g = b.a;
        f.resize(lim), g.resize(lim);
        fft(f, 1), fft(g, 1);
        for (int i = 0; i < lim; ++i)
            f[i] = (ll) f[i] * g[i] % P;
        fft(f, -1);
        Poly ans = vector<int>(n + m + 1);
        for (int i = 0; i <= n + m; ++i)
            ans[i] = f[i];
        return ans;
    }

    Poly &operator+=(const Poly &o) { return (*this) = (*this) + o; }
    Poly &operator-=(const Poly &o) { return (*this) = (*this) - o; }
    Poly &operator*=(const Poly &o) { return (*this) = (*this) * o; }

    Poly inv(int m) const {
        int k = 1;
        Poly x(mpow(a[0], P - 2));
        while (k < m) {
            k <<= 1;
            x = (x * (2 - modxk(k) * x)).modxk(k);
        }
        return x.modxk(m);
    }

    Poly sqrt(int m) const {
        Poly x(1);
        int k = 1;
        while (k < m) {
            k <<= 1;
            x = ((2 * x.modxk(k)).inv(k) * ((x * x).modxk(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }

    Poly deriv() const {
        Poly ans = *this;
        for (int i = 0; i < ans.size() - 1; ++i)
            ans[i] = (ll) a[i + 1] * (i + 1) % P;
        ans[size() - 1] = 0;
        return ans;
    }
    Poly integ() const {
        Poly ans = *this;
        for (int i = 1; i < ans.size(); ++i)
            ans[i] = (ll) a[i - 1] * mpow(i, P - 2) % P;
        ans[0] = 0;
        return ans;
    }

    Poly ln(int m) const {
        return (deriv() * inv(m)).integ().modxk(m);
    }
    Poly exp(int m) const {
        Poly x(1);
        int k = 1;
        while (k < m) {
            k <<= 1;
            x = (x * (1 - x.ln(k) + modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }

    friend pair<Poly, Poly> divmod(const Poly &a, const Poly &b) {
        int n = a.deg(), m = b.deg();
        if (n < m) {
            return make_pair(Poly(), a);
        }
        Poly ar = a.reverse(), br = b.reverse();
        Poly q = (ar * br.inv(n - m + 1)).modxk(n - m + 1);
        q = q.reverse();
        return make_pair(q, (a - b * q).modxk(m));
    }

    friend Poly operator/(const Poly &a, const Poly &b) { return divmod(a, b).first; }
    friend Poly operator%(const Poly &a, const Poly &b) { return divmod(a, b).second; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    Poly f = vector<int>(k + 1);
    vector<int> a(k);
    for (int i = 1; i <= k; ++i) {
        cin >> f[i];
        f[i] %= P;
        if (f[i] < 0) f[i] += P;
    }
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
        a[i] %= P;
        if (a[i] < 0) a[i] += P;
    }
    Poly md = vector<int>(k + 1);
    md[k] = 1;
    for (int i = 1; i <= k; ++i) {
        md[k - i] = P - f[i];
    }
    Poly F(1);
    {
        Poly a = {0, 1};
        for (; n; n >>= 1, a = a * a % md)
            if (n & 1) F = F * a % md;
    }
    int ans = 0;
    for (int i = 0; i < k; ++i) {
        ans += (ll) a[i] * F[i] % P;
        if (ans >= P)
            ans -= P;
    }
    cout << ans << '\n';
    return 0;
}