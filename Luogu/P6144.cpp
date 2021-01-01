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

using i64 = int64_t;

constexpr int P = 1e9 + 7, N = 2e5 + 10;

int n, K;
struct Segment {
	int l, r;
	bool operator<(const Segment &o) const {
		return l < o.l;
	}
} segs[N];

using Info = std::vector<int>;
Info operator+(const Info &a, const Info &b) {
	assert(a.size() == b.size());
	Info res(a.size());
	for (int i = 0; i < (int) a.size(); ++i) {
		res[i] = a[i] + b[i];
		if (res[i] >= P)
			res[i] -= P;
	}
	return res;
}
Info &operator+=(Info &a, const Info &b) { return a = a + b; }
Info operator*(const Info &a, const int &v) {
	Info res = a;
	for (int i = 0; i < (int) a.size(); ++i)
		res[i] =  i64(res[i]) * v % P;
	return res;
}
Info &operator*=(Info &a, const int &v) { return a = a * v; }

struct SegmentTree {
	struct Node {
		int l, r, mul;
		Info dat;
	} t[N * 4];

	void pushup(int x) {
		t[x].dat = t[x * 2].dat + t[x * 2 + 1].dat;
	}
	void pmul(int x, int v) {
		assert(v != 0);
		t[x].mul = i64(t[x].mul) * v % P;
		t[x].dat *= v;
	}
	void pushdown(int x) {
		assert(t[x].mul);
		if (t[x].mul == 1) return;
		pmul(x * 2, t[x].mul);
		pmul(x * 2 + 1, t[x].mul);
		t[x].mul = 1;
	}

	void rangeMul(int x, int ql, int qr, int v) {
		int l = t[x].l, r = t[x].r;
		if (ql <= l && r <= qr) {
			pmul(x, v);
			return;
		}
		pushdown(x);
		int mid = (l + r) >> 1;
		if (ql <= mid) rangeMul(x * 2, ql, qr, v);
		if (mid < qr) rangeMul(x * 2 + 1, ql, qr, v);
		pushup(x);
	}

	void pointAdd(int x, int p, const Info &v) {
		int l = t[x].l, r = t[x].r;
		if (l == r) { t[x].dat += v; return; }
		pushdown(x);
		int mid = (l + r) >> 1;
		if (p <= mid) pointAdd(x * 2, p, v);
		else pointAdd(x * 2 + 1, p, v);
		pushup(x);
	}

	Info query(int x, int ql, int qr) {
		if (ql > qr) return Info(K + 1);
		int l = t[x].l, r = t[x].r;
		if (ql <= l && r <= qr) {
			return t[x].dat;
		}
		pushdown(x);
		int mid = (l + r) >> 1;
		if (qr <= mid) return query(x * 2, ql, qr);
		else if (mid < ql) return query(x * 2 + 1, ql, qr);
		else return query(x * 2, ql, qr) + query(x * 2 + 1, ql, qr);
	}

	void build(int x, int l, int r) {
		t[x].l = l, t[x].r = r;
		t[x].mul = 1, t[x].dat = Info(K + 1);
		if (l == r) {
			if (l == 0) t[x].dat[0] = 1;
			return;
		}
		int mid = (l + r) >> 1;
		build(x * 2, l, mid);
		build(x * 2 + 1, mid + 1, r);
		pushup(x);
	}
} ST;

int C[20][20];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	C[0][0] = 1;
	for (int i = 1; i < 20; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
			if (C[i][j] >= P)
				C[i][j] -= P;
		}
	}

	std::cin >> n >> K;
	for (int i = 1; i <= n; ++i)
		std::cin >> segs[i].l >> segs[i].r;
	std::sort(segs + 1, segs + n + 1);

	ST.build(1, 0, 2 * n);

	for (int i = 1; i <= n; ++i) {
		int l = segs[i].l, r = segs[i].r;

		Info sum = ST.query(1, 0, l - 1);
		Info add = ST.query(1, l, r - 1);
		ST.rangeMul(1, r, 2 * n, 2);
		for (int j = 0; j <= K; ++j) {
			for (int k = 0; k <= j; ++k) {
				add[j] += i64(sum[k]) * C[j][k] % P;
				if (add[j] >= P)
					add[j] -= P;
			}
		}

		// std::cerr << "sum = " << sum << "\nadd = " << add << '\n';

		ST.pointAdd(1, r, add);

		/*
		for (int j = 0; j <= n * 2; ++j)
			std::cerr << ST.query(1, j, j) << " ";
		std::cerr << '\n';
		*/
	}
	std::cout << ST.t[1].dat[K] << '\n';
	return 0;
}