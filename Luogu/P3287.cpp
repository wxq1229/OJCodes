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

constexpr int N = 5555;

int fw[N][N];
void upd(int x, int y, int v) {
	++x, ++y;
	for (int i = x; i < N; i += i & -i)
		for (int j = y; j < N; j += j & -j)
			fw[i][j] = std::max(fw[i][j], v);
}
int qry(int x, int y) {
	int ans = 0;
	++x, ++y;
	for (int i = x; i; i -= i & -i)
		for (int j = y; j; j -= j & -j)
			ans = std::max(ans, fw[i][j]);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, k;
	std::cin >> n >> k;
	std::vector<int> a(n);
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];

	std::vector<int> dp(k + 1, 0);
	int ans = 0;
	for (int i = 0; i < n; ++i) {
		std::vector<int> ndp(k + 1, -1);
		for (int j = 0; j <= k; ++j) {
			ndp[j] = qry(j, a[i] + j) + 1;
			ans = std::max(ans, ndp[j]);
		}
		for (int j = 0; j <= k; ++j) {
			upd(j, a[i] + j, ndp[j]);
		}
		std::swap(dp, ndp);
	}

	std::cout << ans << '\n';
	return 0;
}