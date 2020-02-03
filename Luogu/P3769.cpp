#include <bits/stdc++.h>
using namespace std;
#define debug(...) fprintf(stderr, __VA_ARGS__)
template <class T> inline void chkmax(T &x, T y){ x = max(x, y); }
template <class T> inline void chkmin(T &x, T y){ x = min(x, y); }
template <class T> inline void read(T &x) {
	x = 0; T f = 1; char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= f;
}
typedef double db;
const db alpha = 0.75;
const int MAXN = 2e5 + 10;
const int INF = 0x3f3f3f3f;
struct point {
	int x, y, z, val;
} p[MAXN];
point max(point a, point b){ return (point){max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)}; }
point min(point a, point b){ return (point){min(a.x, b.x), min(a.y, b.y), min(a.z, b.z)}; }
int cmptype;
int cmp(point a, point b) {
	if (cmptype == 0) return a.x < b.x;
	else if (cmptype == 1) return a.y < b.y;
	else return a.z < b.z;
}
int cnp(int a, int b){ return cmp(p[a], p[b]); }
int order[MAXN], n;
struct KDTree {
	struct node {
		point pos, lpos, rpos;
		int val, maxv, size;
		int lc, rc, d, id;
	} t[MAXN];
	int root, size, n;
	queue<int> freenodes;
	int newnode() {
		int x;
		if (freenodes.size()) x = freenodes.front(), freenodes.pop();
		else x = ++size;
		return x;
	}
	void pushup(int x) {
		t[x].lpos = t[x].rpos = t[x].pos;
		t[x].maxv = t[x].val;
		t[x].size = 1;
		if (t[x].lc) {
			t[x].size += t[t[x].lc].size;
			chkmin(t[x].lpos, t[t[x].lc].lpos);
			chkmax(t[x].rpos, t[t[x].lc].rpos);
			chkmax(t[x].maxv, t[t[x].lc].maxv);
		}
		if (t[x].rc) {
			t[x].size += t[t[x].rc].size;
			chkmin(t[x].lpos, t[t[x].rc].lpos);
			chkmax(t[x].rpos, t[t[x].rc].rpos);
			chkmax(t[x].maxv, t[t[x].rc].maxv);
		}
	}
	int build(int l, int r, int type) {
		if (l > r) return 0;
		int mid = (l + r) >> 1;
		cmptype = type;
		nth_element(order + l, order + mid, order + r + 1, cnp);
		int x = newnode();
		t[x].val = p[order[mid]].val;
		t[x].pos = p[t[x].id = order[mid]];
		t[x].d = type, t[x].size = 1;
		t[x].lc = build(l, mid - 1, (type + 1) % 3);
		t[x].rc = build(mid + 1, r, (type + 1) % 3);
		pushup(x);
		return x;
	}
	void init(int sz) {
		size = 0, n = sz;
		while (freenodes.size()) freenodes.pop();
		for (int i = 1; i <= n; i++) order[i] = i;
	}
	int isbad(int x){ return alpha * t[x].size <= (db) max(t[t[x].lc].size, t[t[x].rc].size); }
	int tot;
	void print(int x) {
		if (t[x].lc) print(t[x].lc);
		freenodes.push(x);
		order[++tot] = t[x].id;
		if (t[x].rc) print(t[x].rc);
	}
	void rebuild(int &x) {
		tot = 0, print(x);
		x = build(1, tot, rand()%3);
	}
	void insert(int &x, int id, int v) {
		if (!x) {
			x = newnode();
			t[x].lc = t[x].rc = 0;
			t[x].pos = p[t[x].id = id];
			t[x].val = v, t[x].size = 1;
			t[x].d = (cmptype + 1) % 3;
			pushup(x);
			return;
		}
		cmptype = t[x].d;
		if (cnp(id, t[x].id)) insert(t[x].lc, id, v);
		else insert(t[x].rc, id, v);
		pushup(x);
		if (isbad(x)) rebuild(x);
	}
	int query(int x, point ql, point qr) {
		if (!x || ql.x > t[x].rpos.x || ql.y > t[x].rpos.y ||
				qr.x < t[x].lpos.x || qr.y < t[x].lpos.y ||
					ql.z > t[x].rpos.z || qr.z < t[x].lpos.z)
			return 0;
		if (ql.x <= t[x].lpos.x && t[x].rpos.x <= qr.x &&
				ql.y <= t[x].lpos.y && t[x].rpos.y <= qr.y &&
					ql.z <= t[x].lpos.z && t[x].rpos.z <= qr.z)
			return t[x].maxv;
		int ans = 0;
		if (ql.x <= t[x].pos.x && t[x].pos.x <= qr.x && 
				ql.y <= t[x].pos.y && t[x].pos.y <= qr.y && 
					ql.z <= t[x].pos.z && t[x].pos.z <= qr.z)
			chkmax(ans, t[x].val);
		return max(ans, max(query(t[x].lc, ql, qr), query(t[x].rc, ql, qr)));
	}
	int solve() {
		int ans = 0;
		root = 0;
		for (int i = 1; i <= n; i++) {
			int ret = query(root, (point){-INF, -INF}, p[i]) + 1;
			p[i].val = ret;
		//	debug("f[%d] = %d\n", i, ret);
			chkmax(ans, ret);
			insert(root, i, ret);
		}
		return ans;
	}
} T;
struct point4 {
	int a, b, c, d;
	bool operator < (const point4 rhs) const {
		return a < rhs.a || (a == rhs.a && (b < rhs.b || (b == rhs.b && (c < rhs.c || (c == rhs.c && d < rhs.d)))));
	}
} a[MAXN];
int main() {
	srand(time(NULL));
	read(n);
	for (int i = 1; i <= n; i++)
		read(a[i].a), read(a[i].b), read(a[i].c), read(a[i].d);
	sort(a + 1, a + n + 1);
//	for (int i = 1; i <= n; i++)
//		debug("%d: %d %d %d %d\n", i, a[i].a, a[i].b, a[i].c, a[i].d);
	for (int i = 1; i <= n; i++) p[i] = (point){a[i].b, a[i].c, a[i].d};
	T.init(n);
	printf("%d\n", T.solve());
	return 0;
}
