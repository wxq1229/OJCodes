#include <bits/stdc++.h>

template <typename A, typename B> 
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p) {
	os << "{" << p.first << ", " << p.second << "}";
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
	bool fst = true;
	os << "{";
	for (auto t : v) {
		if (fst) fst = false;
		else os << ", ";
		os << t;
	}
	os << "}";
	return os;
}

constexpr int N = 5e5 + 5, K = 15, P = 1e9 + 7;

int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = int64_t(a) * a % P)
		if (b & 1) ans = int64_t(ans) * a % P;
	return ans;
}
void upd(int &x, int y) { x += y; if (x >= P) x -= P; }

struct Poly {
	std::vector<int> a;

	Poly() { a = std::vector<int>(0); }
	Poly(int v) {
		v %= P;
		if (v < 0) v += P;
		a = {v};
	}
	Poly(const std::vector<int> &v) { a = v; }
	Poly(const std::initializer_list<int> &l) { a = l; }

	int size() const { return (int) a.size(); }
	int deg() const { return size() - 1; }

	int operator[](int i) const { return 0 <= i && i < size() ? a[i] : 0; }
	int &operator[](int i) {
		assert(0 <= i && i < size());
		return a[i];
	}

	Poly operator+(const Poly &o) const {
		int n = size(), m = o.size();
		std::vector<int> res(std::max(n, m));
		for (int i = 0; i < res.size(); ++i) {
			res[i] = this->operator[](i) + o[i];
			if (res[i] >= P) res[i] -= P;
		}
		return Poly(res);
	}
	Poly operator-(const Poly &o) const {
		int n = size(), m = o.size();
		std::vector<int> res(std::max(n, m));
		for (int i = 0; i < res.size(); ++i) {
			res[i] = this->operator[](i) - o[i];
			if (res[i] < 0) res[i] += P;
		}
		return Poly(res);
	}
	Poly operator*(const Poly &o) const {
		int n = size(), m = o.size();
		std::vector<int> res(n + m - 1);
		for (int i = 0; i < n; ++i) if (a[i] != 0) {
			for (int j = 0; j < m; ++j)
				upd(res[i + j], int64_t(a[i]) * o[j] % P);
		}
		return Poly(res);
	}

	Poly &operator+=(const Poly &o) { return *this = (*this) + o; }
	Poly &operator-=(const Poly &o) { return *this = (*this) - o; }
	Poly &operator*=(const Poly &o) { return *this = (*this) * o; }

	friend std::ostream &operator<<(std::ostream &os, const Poly &p) { return os << p.a; }
};

int fact[K], invFact[K], pw[K][K];
struct Lagrange {
	int x[K], y[K], n, kk;

	void init(int k) {
		int sum = 0;
		n = k + 2;
		kk = k;
		for (int i = 1; i <= n; ++i) {
			upd(sum, pw[i][k]);
			x[i] = i, y[i] = sum;
		}
	}
	
	int calc(int x0) {
		if (x0 <= n) {
			int ans = 0;
			for (int i = 1; i <= x0; ++i) {
				upd(ans, pw[i][kk]);
			}
			return ans;
		}
		int tmp = 1;	
		for (int i = 1; i <= n; ++i)
			tmp = int64_t(tmp) * (x0 - i + P) % P;
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			int coeff = int64_t(tmp) * mpow(x0 - i + P, P - 2) % P;
			coeff = int64_t(coeff) * invFact[i - 1] % P * 
						((n - i) & 1 ? P - invFact[n - i] : invFact[n - i]) % P;
			upd(ans, int64_t(coeff) * y[i] % P);
		}
		return ans;
	}
} func[K];

int w[K], n, k;
struct Walk { int c, d; } walk[N];

int lft[K][N], rgt[K][N], delta[K], ori[K], res[K];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);

	for (int i = 0; i < K; ++i)
		for (int j = 0; j < K; ++j)
			pw[i][j] = mpow(i, j);
	fact[0] = 1;
	for (int i = 1; i < K; ++i)
		fact[i] = int64_t(fact[i - 1]) * i % P;
	invFact[K - 1] = mpow(fact[K - 1], P - 2);
	for (int i = K - 2; i >= 0; --i)
		invFact[i] = int64_t(invFact[i + 1]) * (i + 1) % P;
	for (int i = 1; i < K; ++i)
		func[i].init(i);
	
	std::cin >> n >> k;
	for (int i = 1; i <= k; ++i) std::cin >> w[i];
	for (int i = 1; i <= n; ++i)
		std::cin >> walk[i].c >> walk[i].d;
	
	bool infinity = true;
	for (int i = 1; i <= k; ++i) {
		int cur = 0, mx = 0, mn = 0;
		for (int j = 1; j <= n; ++j) {
			int c = walk[j].c, d = walk[j].d;
			if (i == c) cur += d;
			mn = std::min(mn, cur);
			mx = std::max(mx, cur);
			lft[i][j] = mn, rgt[i][j] = mx;
		}
		delta[i] = cur;
		ori[i] = w[i] - mx + mn;

		infinity &= delta[i] == 0 && mx - mn + 1 <= w[i];
	}
	if (infinity) { std::cout << "-1\n"; return 0; }

	int ans = 1;
	for (int i = 1; i <= k; ++i)
		ans = int64_t(ans) * w[i] % P;
	for (int i = 1; i <= n; ++i) {
		int tmp = 1;
		for (int j = 1; j <= k; ++j)
			tmp = int64_t(tmp) * std::max(0, w[j] - rgt[j][i] + lft[j][i]) % P;
		upd(ans, tmp);
	}

	int lst = -1;
	for (int i = 1; i <= n; ++i) {
		int lim = 1e9;
		bool flg = 0;
		Poly mul = 1;
		for (int j = 1; j <= k; ++j) {
			int newOut = std::max(0, delta[j] + rgt[j][i] - rgt[j][n])
							+ std::max(0, lft[j][n] - (delta[j] + lft[j][i]));
			int roundOut = abs(delta[j]);
			if (ori[j] - newOut - roundOut  <= 0) {
				flg = 1; break;
			}
			if (roundOut != 0) lim = std::min(lim, (ori[j] - newOut) / roundOut);
			Poly line = {(ori[j] - newOut + P) % P, (P - roundOut) % P};
			mul *= line;
		}
		if (flg) break;

		if (lim != lst) {
			for (int j = 0; j <= k; ++j)
				res[j] = func[j].calc(lim);
		}
		upd(ans, int64_t(mul[0]) * (lim + 1) % P);
		int tmp = 0;
		for (int j = 1; j < mul.size(); ++j) {
			upd(tmp, int64_t(mul[j]) * res[j] % P);
		}
		upd(ans, tmp);
		lst = lim;
	}

	std::cout << ans << '\n';
	return 0;
}