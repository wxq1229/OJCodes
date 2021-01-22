#include <bits/stdc++.h>

using i64 = int64_t;

struct Point {
	i64 x, y;
	int id, col;

	Point operator-(const Point &o) const {
		return {x - o.x, y - o.y};
	}

	bool operator<(const Point &o) const { return x < o.x || (x == o.x && y < o.y); }
};
inline i64 cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }

constexpr int N = 111;
int ans[N];

void solve(std::vector<Point> ps) {
	if (int(ps.size()) == 0) return;

	assert(ps.size() % 2 == 0);

	std::sort(ps.begin(), ps.end(), [](Point a, Point b) {
		return a.y < b.y || (a.y == b.y && a.x < b.x);
	});
	Point O = ps[0];
	std::vector<Point> qs(ps.begin() + 1, ps.end());
	std::sort(qs.begin(), qs.end(), [&](Point a, Point b) {
		i64 s = cross(b - O, a - O);
		if (s != 0) return s > 0;
		else return a < b;
	});

	std::vector<int> cnt(2);
	int n = (int) qs.size(), mid = -1;
	for (int i = 0; i < n; ++i) {
		Point p = qs[i];
		if (p.col != O.col && cnt[0] == cnt[1]) {
			mid = i;
			break;
		}
		++cnt[p.col];
	}
	assert(mid != -1);
	if (O.col == 0) ans[O.id] = qs[mid].id;
	else ans[qs[mid].id] = O.id;

	solve(std::vector<Point>(qs.begin(), qs.begin() + mid));
	solve(std::vector<Point>(qs.begin() + mid + 1, qs.end()));
}

int main() {
	int n;
	bool fst = 1;
	while (std::cin >> n && n != 0) {
		if (!fst) { std::cout << '\n'; }
		else fst = 0;

		std::vector<Point> p(n * 2);
		for (int i = 0; i < n; ++i) {
			std::cin >> p[i].x >> p[i].y;
			p[i].id = i;
			p[i].col = 0;
		}
		for (int i = n; i < n * 2; ++i) {
			std::cin >> p[i].x >> p[i].y;
			p[i].id = i - n;
			p[i].col = 1;
		}
		solve(p);
		for (int i = 0; i < n; ++i)
			std::cout << ans[i] + 1 << '\n';
	}
	return 0;
}