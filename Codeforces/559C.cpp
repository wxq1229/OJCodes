#include <bits/stdc++.h>
using i64 = long long;

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

template <typename T>
std::string binToStr(T x) {
	std::string s = "";
	while (x) {
		if (x & 1) s = "1" + s;
		else s = "0" + s;
		x >>= 1;
	}
	return s;
}

constexpr int P = 1e9 + 7;
inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = i64(a) * a % P)
		if (b & 1) ans = i64(ans) * a % P;
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	constexpr int N = 200000;
	std::vector<int> fac(N + 1), invFac(N + 1);
	fac[0] = 1;
	for (int i = 1; i <= N; ++i)
		fac[i] = 1ll * fac[i - 1] * i % P;
	invFac[N] = mpow(fac[N], P - 2);
	for (int i = N - 1; i >= 0; --i) {
		invFac[i] = 1ll * invFac[i + 1] * (i + 1) % P;
	}
	auto C = [&](int n, int m) -> int {
		if (n < 0 || m < 0 || n - m < 0)
			return 0;
		return 1ll * fac[n] * invFac[m] % P * invFac[n - m] % P;
	};

	int h, w, n;
	std::cin >> h >> w >> n;
	std::vector<std::pair<int, int>> p(n + 2);
	for (int i = 0; i < n; ++i) {
		std::cin >> p[i].first >> p[i].second;
	}
	p[n] = std::make_pair(1, 1);
	p[n + 1] = std::make_pair(h, w);
	std::sort(p.begin(), p.end());
	n += 2;
	std::vector<int> dp(n);
	for (int i = 0; i < n; ++i) {
		dp[i] = C(p[i].first + p[i].second - 2, p[i].first - 1);
		for (int j = 1; j < i; ++j)
			if (p[j].first <= p[i].first && p[j].second <= p[i].second)
				dp[i] = (dp[i] - 1ll * C(p[i].first - p[j].first + p[i].second - p[j].second, p[i].first - p[j].first) * dp[j] % P + P) % P;
	}
	// std::cerr << "dp = " << dp << '\n';
	std::cout << dp[n - 1] << '\n';
	return 0;
}