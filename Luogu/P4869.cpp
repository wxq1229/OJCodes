#include <bits/stdc++.h>
using i64 = long long;

constexpr int N = 30, P = 10086;
inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = i64(a) * a % P)
		if (b & 1) ans = i64(ans) * a % P;
	return ans;
}

int a[N], pw[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	pw[0] = 1;
	for (int i = 1; i < N; ++i) pw[i] = 2ll * pw[i - 1] % P;

	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		int v;
		std::cin >> v;
		for (int j = N - 1; j >= 0; --j) if (v >> j & 1) {
			if (!a[j]) { a[j] = v; break; }
			v ^= a[j];
		}
	}
	for (int i = N - 1; i >= 0; --i) {
		for (int j = i + 1; j < N; ++j)
			if (a[j] >> i & 1) a[j] ^= a[i];
	}
	int dim = 0;
	std::vector<int> p;
	for (int i = 0; i < N; ++i) if (a[i] != 0) {
		p.push_back(i);
		++dim;
	}
	int q; std::cin >> q;
	int ans = 0;
	for (int _ = dim - 1; _ >= 0; --_) {
		int i = p[_];
		if (q >> i & 1) {
			q ^= a[i];
			ans = (ans + pw[_]) % P;
		}
	}
	std::cout << (1ll * ans * mpow(2, n - dim) % P + 1) % P << '\n';

	return 0;
}