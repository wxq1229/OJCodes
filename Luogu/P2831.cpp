#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-7;
inline int sign(db x) {
	return x < -eps ? -1 : x > eps;
}

void calc(db a, db b, db u, db c, db d, db v, db &x, db &y) {
	// ax + by = u
	// cx + dy = v
	// cerr << a << " * x + " << b << " * y = " << u << '\n';
	// cerr << c << " * x + " << d << " * y = " << v << '\n';
	{
		db k = d / b;
		x = (u * k - v) / (a * k - c);
	}
	{
		db k = c / a;
		y = (u * k - v) / (b * k - d);
	}
}

struct func {
	db a, b;
	int st;
	func(db _a = 0, db _b = 0, bool _st = 0) { 
		a = _a;
		b = _b;
		st = _st;
	}
	db operator()(db x) const {
		return a * x * x + b * x;
	}
};
struct point { 
	db x, y; 
	bool on(const func &f) const {
		return sign(fabs(f(x) - y)) == 0;
	}
	bool operator<(const point &o) const {
		return x < o.x || (x == o.x && y < o.y);
	}
	point(db _x = 0, db _y = 0) { 
		x = _x;
		y = _y;
	}
};

func get_func(point A, point B) {
	db a, b;
	calc(A.x * A.x, A.x, A.y, B.x * B.x, B.x, B.y, a, b);
	// cerr << a << '\n';
	// assert(sign(a) <= 0);
	return func(a, b);
}

inline int lowbit(int x) { return x & -x; }

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt;
	cin >> tt;
	while (tt--) {
		int n, m;
		cin >> n >> m;
		vector<point> ps(n);
		for (int i = 0; i < n; ++i) {
			cin >> ps[i].x >> ps[i].y;
		}
		sort(ps.begin(), ps.end());
		vector<vector<func>> pr(n, vector<func>(n));
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				func tmp = get_func(ps[i], ps[j]);
				tmp.st = 0;
				if (sign(tmp.a) < 0) {
					for (int k = 0; k < n; ++k)
						if (ps[k].on(tmp)) tmp.st |= 1 << k;
				}
				pr[i][j] = tmp;
			}
		}
		const int inf = 0x3f3f3f3f;
		vector<int> dp(1 << n, inf);
		dp[0] = 0;
		for (int i = 0; i < (1 << n); ++i) {
			if (dp[i] == inf) {
				continue;
			}
			int p = __builtin_ctz(lowbit(~i));
			if (p < n) dp[i | (1 << p)] = min(dp[i | (1 << p)], dp[i] + 1);
			for (int q = p + 1; q < n; ++q) {
				func tmp = pr[p][q];
				dp[i | tmp.st] = min(dp[i | tmp.st], dp[i] + 1);
			}
		}
		cout << dp[(1 << n) - 1] << '\n';
	}
	return 0;
}