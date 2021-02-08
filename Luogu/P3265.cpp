#include <bits/stdc++.h>
using db = long double;
using Vector = std::vector<db>;

constexpr db EPS = 1e-6;
inline int sign(db x) { return x < -EPS ? -1 : x > EPS; }
Vector operator+(const Vector &a, const Vector &b) {
	int n = int(a.size());
	assert(n == b.size());
	Vector c(n);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] + b[i];
	return c;
}
Vector operator-(const Vector &a, const Vector &b) {
	int n = int(a.size());
	assert(n == b.size());
	Vector c(n);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] - b[i];
	return c;
}
Vector operator*(const Vector &a, const db &x) {
	int n = int(a.size());
	Vector c(n);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] * x;
	return c;
}
Vector operator/(const Vector &a, const db &x) {
	int n = int(a.size());
	Vector c(n);
	for (int i = 0; i < n; ++i)
		c[i] = a[i] / x;
	return c;
}
Vector operator*(const db &x, const Vector &a) { return a * x; }

constexpr int N = 510;
int n, order[N];
Vector a[N];
db c[N];

int dim, id[N];
Vector basis[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> dim;
	for (int i = 0; i < n; ++i) {
		a[i].resize(dim);
		for (int j = 0; j < dim; ++j)
			std::cin >> a[i][j];		
	}
	for (int i = 0; i < n; ++i)
		std::cin >> c[i];
	
	std::iota(order, order + n, 0);
	std::sort(order, order + n, [&](int i, int j) { return c[i] < c[j]; });

	std::memset(id, -1, sizeof id);
	int cnt = 0, ans = 0;
	for (int _ = 0; _ < n; ++_) {
		int i = order[_];
		Vector v = a[i];
		for (int j = 0; j < dim; ++j) if (sign(v[j]) != 0) {
			if (id[j] == -1) {
				id[j] = i;
				basis[j] = v;
				ans += c[i];
				++cnt;
				break;
			}
			db k = v[j] / basis[j][j];
			v = v - k * basis[j];
		}
	}
	std::cout << cnt << " " << ans << '\n';
	
	return 0;
}