#include <bits/stdc++.h>

#define UND 0
#define UP 1
#define DOWN -1

struct Edge {
	int v;
	int type;
};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int u;
	while (std::cin >> u && u) {
		int n = u;
		std::vector<std::vector<Edge>> e(222);
		std::vector<bool> isRoot(222, true);
		std::string foo;
		--u;
		while (std::cin >> foo && foo != "0") {
			std::stringstream ss(foo);
			int v, type;
			ss >> v;
			if (std::isdigit(foo.back())) type = UND;
			else { char c; ss >> c; type = c == 'u' ? UP : DOWN; }
			n = std::max(n, v);
			--v;
			e[u].push_back({v, type});
			e[v].push_back({u, -type});
			isRoot[v] = false;
		}
		while (std::cin >> u && u) {
			n = std::max(n, u);
			--u;
			while (std::cin >> foo && foo != "0") {
				std::stringstream ss(foo);
				int v, type;
				ss >> v;
				if (std::isdigit(foo.back())) type = UND;
				else { char c; ss >> c; type = c == 'u' ? UP : DOWN; }
				n = std::max(n, v);
				--v;
				e[u].push_back({v, type});
				e[v].push_back({u, -type});
				isRoot[v] = false;
			}
		}

		// std::cerr << "n = " << n << '\n';
		e.resize(n);
		isRoot.resize(n);
		int root = -1;
		for (int i = 0; i < n; ++i)
			if (isRoot[i]) { root = i; break; }

		auto check = [&](int mid) {
			std::vector<int> upMax(n), downMax(n);
			bool failed = false;

			std::function<void(int, int)> dfs = [&](int u, int p) {
				// std::cerr << "DFS " << u << " " << p << '\n';
				if (failed) return;
				upMax[u] = 1, downMax[u] = 1;
				std::vector<int> undSons;
				for (auto ei : e[u]) {
					int v = ei.v, type = ei.type;
					if (v == p) continue;
					dfs(v, u);
					if (type == UND) undSons.push_back(v);
					else if (type == UP) upMax[u] = std::max(upMax[u], upMax[v] + 1);
					else if (type == DOWN) downMax[u] = std::max(downMax[u], downMax[v] + 1);
				}

				int m = int(undSons.size());
				{
					std::sort(undSons.begin(), undSons.end(), [&](int i, int j) {
						return upMax[i] < upMax[j]; 
					});
					std::vector<int> sufMax(m);
					for (int i = m - 1; i >= 0; --i) {
						if (i + 1 < m)
							sufMax[i] = sufMax[i + 1];
						int v = undSons[i];
						sufMax[i] = std::max(sufMax[i], downMax[v]);
					}
					int curMax = 0;
					bool found = false;
					for (int i = 0; i < m; ++i) {
						if (std::max(curMax, upMax[u]) + std::max(sufMax[i], downMax[u] - 1) <= mid) {
							upMax[u] = std::max(curMax, upMax[u]);
							found = true;
							break;
						}
						int v = undSons[i];
						curMax = std::max(curMax, upMax[v] + 1);
					}
					if (std::max(curMax, upMax[u]) + downMax[u] - 1 <= mid) {
						if (!found) upMax[u] = std::max(curMax, upMax[u]);
						found = 1;
					}
					if (!found) { failed = true; return; }
				}
				{
					std::sort(undSons.begin(), undSons.end(), [&](int i, int j) {
						return downMax[i] < downMax[j]; 
					});
					std::vector<int> sufMax(m);
					for (int i = m - 1; i >= 0; --i) {
						if (i + 1 < m)
							sufMax[i] = sufMax[i + 1];
						int v = undSons[i];
						sufMax[i] = std::max(sufMax[i], upMax[v]);
					}
					int curMax = 0;
					bool found = false;
					for (int i = 0; i < m; ++i) {
						if (std::max(curMax, downMax[u]) + std::max(sufMax[i], upMax[u] - 1) <= mid) {
							downMax[u] = std::max(curMax, downMax[u]);
							found = true;
							break;
						}
						int v = undSons[i];
						curMax = std::max(curMax, downMax[v] + 1);
					}
					if (std::max(curMax, downMax[u]) + upMax[u] - 1 <= mid) {
						if (!found) downMax[u] = std::max(curMax, downMax[u]);
						found = 1;
					}
					if (!found) { failed = true; return; }
				}
			};
			
			dfs(root, -1);
			return !failed;
		};

		int lo = 0, hi = n, ans = -1;
		while (lo <= hi) {
			int mid = (lo + hi) >> 1;
			if (check(mid)) hi = mid - 1, ans = mid;
			else lo = mid + 1;
		}
		std::cout << ans << '\n';
	}
	
	return 0;
}