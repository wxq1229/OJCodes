#include <bits/stdc++.h>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n, m;
	std::cin >> n >> m;
	std::vector<int> a(n), b(n);
	for (auto &v : a) std::cin >> v;
	for (auto &v : b) std::cin >> v;

	std::vector<int> preMax(n), preMin(n);
	std::vector<int> sufMax(n), sufMin(n);
	preMax[0] = b[0];
	for (int i = 1; i < n; ++i) preMax[i] = std::max(preMax[i - 1], b[i]);
	preMin[0] = b[0];
	for (int i = 1; i < n; ++i) preMin[i] = std::min(preMin[i - 1], b[i]);
	sufMax[n - 1] = b[n - 1];
	for (int i = n - 2; i >= 0; --i) sufMax[i] = std::max(sufMax[i + 1], b[i]);
	sufMin[n - 1] = b[n - 1];
	for (int i = n - 2; i >= 0; --i) sufMin[i] = std::min(sufMin[i + 1], b[i]);

	auto check = [&](int mid) {
		for (int i = 0, j = 0; i < n; ++i) {
			while (j < n && a[j] - a[i] <= mid) {
				if (i + n - 1 - j <= m) {
					int min = a[i], max = a[j];
					if (i - 1 >= 0) {
						min = std::min(min, preMin[i - 1]);
						max = std::max(max, preMax[i - 1]);
					}
					if (j + 1 < n) {
						min = std::min(min, sufMin[j + 1]);
						max = std::max(max, sufMax[j + 1]);
					}
					if (max - min <= mid) return true;
				}
				++j;
			}
			--j;
		}
		return false;
	};

	int lo = 0, hi = 1e9, ans = hi + 1;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (check(mid)) ans = mid, hi = mid - 1;
		else lo = mid + 1;
	}

	std::cout << ans << '\n';

	return 0;
}