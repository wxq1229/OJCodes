#include <bits/stdc++.h>
using i64 = int64_t;

constexpr int P = 998244353, ROOT = 3, IROOT = (P + 1) / ROOT;
inline int mpow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = i64(a) * a % P)
        if (b & 1) ans = i64(ans) * a % P;
    return ans;
}

void fft(std::vector<int>& a, int flg) {
    static std::vector<int> rev;
    static std::vector<std::array<int, 2>> roots{{0, 0}};

    int n = int(a.size());
    if (int(rev.size()) != n) {
        rev.resize(n);
        for (int i = 0; i < n; ++i)
            rev[i] = rev[i >> 1] >> 1 | ((i & 1) ? n >> 1 : 0);
    }
    if (int(roots.size()) < n) {
        int m = int(roots.size()) << 1;
        roots.resize(n);
        while (m <= n) {
            roots[m - 1][0] = mpow(ROOT, (P - 1) / m);
            roots[m - 1][1] = mpow(IROOT, (P - 1) / m);
            m <<= 1;
        }
    }
    for (int i = 0; i < n; ++i)
        if (rev[i] < i) std::swap(a[i], a[rev[i]]);
    for (int len = 2; len <= n; len <<= 1) {
        int k = len >> 1, wn = roots[len - 1][flg == -1];
        for (int i = 0; i < n; i += len) {
            for (int j = i, w = 1; j < i + k; ++j, w = i64(w) * wn % P) {
                int tmp = i64(a[j + k]) * w % P;
                int x = a[j] + tmp, y = a[j] - tmp;
                a[j] = x >= P ? x - P : x;
                a[j + k] = y < 0 ? y + P : y;
            }
        }
    }
    if (flg == -1) {
        int inv = mpow(n, P - 2);
        for (int i = 0; i < n; ++i)
            a[i] = i64(a[i]) * inv % P;
    }
}

struct Poly {
    std::vector<int> a;

    Poly() { }
    Poly(int v) {
        v %= P;
        if (v < 0) v += P;
        a = {v};
    }
    Poly(const std::vector<int>& v) : a(v) { }
    Poly(const std::initializer_list<int>& l) : a(l) { }

    int size() const { return a.size(); }
    int deg() const { return size() - 1; }

    int operator[](int k) const {
        if (k < 0 || k >= size()) return 0;
        else return a[k];
    }
    int& operator[](int k) { assert(0 <= k && k < size()); return a[k]; }

    Poly modxk(int k) const {
        if (a.size() <= k) return Poly(a);
        else return Poly(std::vector<int>(a.begin(), a.begin() + k));
    }
    Poly divxk(int k) const {
        if (a.size() <= k) return Poly();
        else return Poly(std::vector<int>(a.begin() + k, a.end()));
    }
    friend Poly operator+(const Poly a, const Poly &b) {
        int n = std::max(a.size(), b.size());
        Poly ans = std::vector<int>(n);
        for (int i = 0; i < n; ++i) {
            ans[i] = a[i] + b[i];
            if (ans[i] >= P) ans[i] -= P;
        }
        return ans;
    }
    friend Poly operator-(const Poly a, const Poly &b) {
        int n = std::max(a.size(), b.size());
        Poly ans = std::vector<int>(n);
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
        std::vector<int> f = a.a, g = b.a;
        f.resize(lim), g.resize(lim);
        fft(f, 1), fft(g, 1);
        for (int i = 0; i < lim; ++i)
            f[i] = i64(f[i]) * g[i] % P;
        fft(f, -1);
        Poly ans = std::vector<int>(n + m + 1);
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
            x = (x + (modxk(k) * x.inv(k)).modxk(k)) * ((P + 1) / 2);
        }
        return x.modxk(m);
    }

    Poly deriv() const {
        Poly ans = *this;
        for (int i = 0; i < ans.size() - 1; ++i)
            ans[i] = i64(a[i + 1]) * (i + 1) % P;
        ans[size() - 1] = 0;
        return ans;
    }
    Poly integ() const {
        Poly ans = *this;
        for (int i = 1; i < ans.size(); ++i)
            ans[i] = i64(a[i - 1]) * mpow(i, P - 2) % P;
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

    friend std::pair<Poly, Poly> divmod(const Poly &a, const Poly &b) {
        int n = a.deg(), m = b.deg();
        if (n < m) {
            return std::make_pair(Poly(), a);
        }
        Poly ar = a, br = b;
		std::reverse(ar.a.begin(), ar.a.end());
		std::reverse(br.a.begin(), br.a.end());
        Poly q = (ar * br.inv(n - m + 1)).modxk(n - m + 1);
		std::reverse(q.a.begin(), q.a.end());
        return std::make_pair(q, (a - b * q).modxk(m));
    }

    friend Poly operator/(const Poly &a, const Poly &b) { return divmod(a, b).first; }
    friend Poly operator%(const Poly &a, const Poly &b) { return divmod(a, b).second; }

	friend std::ostream &operator<<(std::ostream &os, const Poly &p) {
		os << "{"; bool fst = true;
		for (auto v : p.a) { if (!fst) os << ", "; else fst = false; os << v; }
		return os << "}";
	}
};

template <typename T> void write(T x) {
	if (x < 0) x = -x, std::putchar('-');
	if (x > 9) write(x / 10);
	std::putchar(x % 10 + 48);
}
template <typename T> inline void writeln(T x) { write(x); std::puts(""); }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	constexpr int N = 500001;
	std::vector<int> fac(N + 1), invFac(N + 1), inv(N + 1);
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= N; ++i) {
		inv[i] = 1ll * inv[P % i] * (P - P / i) % P;
	}
	fac[0] = 1;
	for (int i = 1; i <= N; ++i)
		fac[i] = 1ll * fac[i - 1] * i % P;
	invFac[N] = mpow(fac[N], P - 2);
	for (int i = N - 1; i >= 0; --i)
		invFac[i] = 1ll * invFac[i + 1] * (i + 1) % P;

	int k, m;
	std::cin >> k >> m;
	std::vector<int> pw(m + 2);
	pw[0] = 1;
	for (int i = 1; i < m + 2; ++i)
		pw[i] = 1ll * pw[i - 1] * (k + 1) % P;
	Poly e = std::vector<int>(m + 2);
	for (int i = 0; i < m + 2; ++i)
		e[i] = invFac[i];
	Poly ek1 = std::vector<int>(m + 2);
	for (int i = 0; i < m + 2; ++i)
		ek1[i] = 1ll * invFac[i] * pw[i] % P;
	Poly s = (e.divxk(1).inv(m + 1) * ek1.divxk(1)).modxk(m + 1);
	for (int i = 0; i < m + 1; ++i) {
		s[i] = 1ll * s[i] * fac[i] % P;
	}

	Poly f = std::vector<int>(m + 1);
	for (int i = 1; i < m + 1; ++i) {
		f[i] = 1ll * inv[i] * s[i] % P;
		if ((i + 1) & 1) f[i] = P - f[i];
	}
	f = f.exp(m + 1);
	for (int i = 1; i < m + 1; ++i)
		writeln(1ll * f[i] * fac[i] % P);
	return 0;
}