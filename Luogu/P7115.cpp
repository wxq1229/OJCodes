#include <bits/stdc++.h>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int n, m;
	std::cin >> n >> m;
	std::vector<std::vector<int>> a(n, std::vector<int>(m));
	a.push_back(std::vector<int>());
	for (int i = 0; i < n; ++i)	
		for (int j = 0; j < m; ++j)
			std::cin >> a[i][j], --a[i][j];

	std::vector<std::pair<int, int>> ans;

	std::function<void(int, int)> solve = [&](int l, int r) {
		if (l == r - 1) return;
		int mid = (r - l) / 2 + l;
		// [l, mid), [mid, r)

		std::vector<std::vector<int>> cc(n + 1, std::vector<int>(2));
		std::vector<std::vector<int>> col(n, std::vector<int>(m));
		col.push_back(std::vector<int>());
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				col[i][j] = a[i][j] >= mid;
				++cc[i][col[i][j]];
			}
		}

		auto move = [&](int p, int q) {
			ans.push_back(std::make_pair(p, q));
			--cc[p][col[p].back()], ++cc[q][col[p].back()];
			a[q].push_back(a[p].back()), a[p].pop_back();
			col[q].push_back(col[p].back()), col[p].pop_back();
		};

		auto modify = [&](int p) {
			std::vector<int> c = cc[p];
			int q = p == l ? l + 1 : l;
			for (int i = 0; i < c[0]; ++i) move(q, n);
			for (int i = m - 1; i >= 0; --i) {
				if (col[p][i] == 0) move(p, q);
				else move(p, n);
			}
			if (p < mid) {
				for (int i = 0; i < c[0]; ++i) move(q, p);
				for (int i = 0; i < c[1]; ++i) move(n, p);
				for (int i = 0; i < c[0]; ++i) move(n, q);
			} else {
				for (int i = 0; i < c[1]; ++i) move(n, p);
				for (int i = 0; i < c[0]; ++i) move(q, p);
				for (int i = 0; i < c[0]; ++i) move(n, q);
			}
		};

		for (int i = l; i < r; ++i)	
			modify(i);

		int ptr = l;
		for (int i = mid; i < r; ++i) {
			while (ptr < mid) {
				if (cc[ptr][0] >= m) { ++ptr; continue; }
				int c1 = cc[ptr][1], c0 = cc[i][0];
				int ct = std::min(c1, c0);
				if (ct == c0) {
					for (int k = 0; k < c1; ++k) move(ptr, n);
					for (int k = 0; k < ct; ++k) move(i, ptr);
					for (int k = 0; k < c1 - ct; ++k) move(n, ptr);
					for (int k = 0; k < ct; ++k) move(n, i);
				} else {
					for (int k = 0; k < ct; ++k) move(ptr, n);
					for (int k = 0; k < ct; ++k) move(i, ptr);
					for (int k = 0; k < ct; ++k) move(n, i);
					modify(ptr), modify(i);
				}
				if (cc[i][0] <= 0) break;
				++ptr;
			}
		}

		solve(l, mid), solve(mid, r);
	};
	
	solve(0, n);
	std::cout << (int) ans.size() << '\n';
	for (auto p : ans) std::cout << p.first + 1 << " " << p.second + 1 << '\n';
	return 0;
}