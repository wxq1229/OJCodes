#include <bits/stdc++.h>

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	std::cin >> n;
	
	std::vector<std::vector<int>> e(n);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		std::cin >> u >> v;
		--u, --v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	auto chk = [&](int len) {
		std::function<int(int, int)> dfs = [&](int u, int f) {
			std::multiset<int> set;
			for (auto v : e[u]) if (v != f) {
				int tmp = dfs(v, u);
				if (tmp == -1) return -1;
				set.insert(tmp + 1);
			}
			
			if (f == -1) {
				if (set.size() & 1) {
					auto del = set.end();
					for (auto it = set.begin(); it != set.end(); ++it) if (*it >= len) {
						del = it;
						break;
					}
					if (del == set.end()) return -1;
					set.erase(del);
				}
				while (set.size()) {
					auto p = set.begin();
					set.erase(p);
					auto q = set.lower_bound(len - (*p));
					if (q == set.end()) return -1;
					set.erase(q);
				}
				return 0;
			} else {
				int res = 0, cnt = 0;
				while (set.size()) {
					auto p = set.begin();
					set.erase(p);
					if (*p >= len) { res = std::max(res, (*p)); continue; }
					auto q = set.lower_bound(len - (*p));
					if (q == set.end()) {
						res = std::max(res, (*p));
						if (++cnt > 1) return -1;
						continue;
					}
					if ((*q) >= len) res = std::max(res, *p);
					set.erase(q);
				}
				return res;
			}
		};

		return dfs(0, -1) != -1;
	};

	int lo = 0, hi = n, ans = 0;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (chk(mid)) ans = mid, lo = mid + 1;
		else hi = mid - 1;
	}

	std::cout << ans << '\n';
	return  0;
}