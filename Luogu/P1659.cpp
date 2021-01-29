#include <bits/stdc++.h>
using i64 = long long;

constexpr int P = 19930726;

inline int mpow(int a, int b) {
	int ans = 1;
	for (; b; b >>= 1, a = i64(a) * a % P)
		if (b & 1) ans = i64(ans) * a % P;
	return ans;
}

// LongestPalindromicSubstr.size() = max{R[i] - 1}
std::vector<int> manacher(const std::string &s) {
	int n = (int) s.size();

	std::vector<int> R(n);
	int p = -1, mx = -1;
	for (int i = 0; i < n; ++i) {
		if (i <= mx) R[i] = std::min(mx - i + 1, R[2 * p - i]);
		else R[i] = 1;
		while (i - R[i] >= 0 && i + R[i] < n && s[i - R[i]] == s[i + R[i]])
			++R[i];
		if (i + R[i] - 1 > mx)
			p = i, mx = i + R[i] - 1;
	}

	return R;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n; i64 k;
	std::cin >> n >> k;
	std::string s;
	std::cin >> s;

	auto R = manacher(s);
	std::vector<i64> sum(n + 1);
	for (int i = 0; i < n; ++i) {
		// 2*1-1, 2*2-1, 2*3-1, ..., 2*R[i]-1
		++sum[1], --sum[R[i] + 1];
	}
	for (int i = 1; i <= n; ++i) sum[i] += sum[i - 1];
	
	int ans = 1;
	for (int i = n; i >= 1; --i) {
		ans = i64(ans) * mpow(2 * i - 1, std::min(k, sum[i])) % P;
		k -= sum[i];
		if (k <= 0) break;
	}
	if (k > 0) std::cout << "-1\n";
	else std::cout << ans << '\n';
		
	return 0;
}