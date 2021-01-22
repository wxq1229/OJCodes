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

struct Segment {
	int l, r;
	int id;

	bool operator<(const Segment &o) const { return r < o.r || (r == o.r && l < o.l); }

	friend std::ostream &operator<<(std::ostream &os, const Segment &seg) { return os << "[" << seg.l << ", " << seg.r << "]"; }
};

bool solve(std::vector<Segment> segs, std::vector<int> &ans) {
	int n = int(segs.size());
	std::sort(segs.begin(), segs.end());

	// std::cerr << "SEGS: " << segs << '\n';

	std::vector<bool> vis(n, 0);
	for (int i = 0; i < n; ++i) {
		int l = segs[i].l, r = segs[i].r;
		bool found = 0;
		for (int j = l; j <= r; ++j) if (!vis[j]) {
			vis[j] = 1;
			found = 1;
			ans[segs[i].id] = j;
			break;
		}
		if (!found) return 0;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n;
	while (std::cin >> n && n != 0) {
		// std::cerr << n << '\n';
		std::vector<int> xl(n), yl(n), xr(n), yr(n);
		for (int i = 0; i < n; ++i) {
			std::cin >> xl[i] >> yl[i] >> xr[i] >> yr[i];
			--xl[i], --xr[i];
			--yl[i], --yr[i];
		}

		std::vector<int> x(n), y(n);
		std::vector<Segment> segX(n), segY(n);
		for (int i = 0; i < n; ++i) {
			segX[i] = {xl[i], xr[i], i};
			segY[i] = {yl[i], yr[i], i};
		}
		if ((!solve(segX, x)) || (!solve(segY, y))) { std::cout << "IMPOSSIBLE\n"; }
		else {
			for (int i = 0; i < n; ++i)
				std::cout << x[i] + 1 << " " << y[i] + 1 << '\n';
		}
	}
	return 0;
}