#include <bits/stdc++.h>
using i64 = long long;

template <typename T>
std::string binToStr(T x) {
	if (!x) return "0";
	std::string s = "";
	while (x) {
		if (x & 1) s = "1" + s;
		else s = "0" + s;
		x >>= 1;
	}
	return s;
}

template <typename T>
struct LinearBasis {
	static constexpr int N = 51;
	T a[N];
	void insert(T v) {
		for (int i = N - 1; i >= 0; --i) if (v >> i & 1) {
			if (a[i] == 0) { a[i] = v; break; }
			v ^= a[i];
		}
	}
	T query() {
		T ans = 0;
		for (int i = N - 1; i >= 0; --i) 
			ans = std::max(ans, ans ^ a[i]);
		return ans;
	}
};
LinearBasis<i64> lb;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;
	for (int i = 0; i < n; ++i) {
		i64 v;
		std::cin >> v;
		lb.insert(v);
	}
	std::cout << lb.query() << '\n';

	return 0;
}