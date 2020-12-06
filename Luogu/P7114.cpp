#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <int P>
struct ModInt {
	int v;
	ModInt() { v = 0; }
	template <typename T> ModInt(T _v) { (v = _v) %= P; if (v < 0) v += P; }
	ModInt &operator+=(const ModInt &o) { v += o.v; if (v >= P) v -= P; return *this; }
	ModInt &operator-=(const ModInt &o) { v -= o.v; if (v < 0) v += P; return *this; }
	ModInt &operator*=(const ModInt &o) { v = (ll) v * o.v % P; return *this; }
	friend ModInt operator+(ModInt a, const ModInt &b) { return a += b; }
	friend ModInt operator-(ModInt a, const ModInt &b) { return a -= b; }
	friend ModInt operator*(ModInt a, const ModInt &b) { return a *= b; }
	friend bool operator==(const ModInt &a, const ModInt &b) { return a.v == b.v; }
	friend bool operator!=(const ModInt &a, const ModInt &b) { return a.v != b.v; }
	friend ostream &operator<<(ostream &os, const ModInt &a) { return os << "(ModInt) " << a.v; }
};

struct Hash {
	static const int P1 = 1e9 + 9, P2 = 19260817;
	ModInt<P1> v1; ModInt<P2> v2;
	Hash() { v1 = 0, v2 = 0; }
	template <typename T> Hash(T _v) { v1 = _v, v2 = _v; }
	Hash &operator+=(const Hash &o) { v1 += o.v1, v2 += o.v2; return *this; }
	Hash &operator-=(const Hash &o) { v1 -= o.v1, v2 -= o.v2; return *this; }
	Hash &operator*=(const Hash &o) { v1 *= o.v1, v2 *= o.v2; return *this; }
	friend Hash operator+(Hash a, const Hash &b) { return a += b; }
	friend Hash operator-(Hash a, const Hash &b) { return a -= b; }
	friend Hash operator*(Hash a, const Hash &b) { return a *= b; }
	friend bool operator==(const Hash &a, const Hash &b) { return a.v1 == b.v1 && a.v2 == b.v2; }
	friend bool operator!=(const Hash &a, const Hash &b) { return a.v1 != b.v1 || a.v2 != b.v2; }
	friend ostream &operator<<(ostream &os, const Hash &a) { return os << "(Hash) {" << a.v1 << ", " << a.v2 << "}"; }
};

const int N = (1 << 20) + 10;
const Hash base = 26;
Hash pw[N];
void hash_init() {
	pw[0] = 1;
	for (int i = 1; i < N; ++i) pw[i] = pw[i - 1] * base;
}

template <typename T>
struct Fenwick {
    vector<T> a;
    int n;

    void init(int _n = 0) {
		n = _n, a = vector<T>(n + 1); 
		for (int i = 0; i <= n; ++i) a[i] = 0; 
	}
    void upd(int x, T v) { for (; x <= n; x += x & -x) a[x] += v; }
    T qry(int x) { int ans = 0; for (; x; x -= x & -x) ans += a[x]; return ans; }
};
Fenwick<int> fenw;

Hash h[N];
int suf[N];

void solve() {
	string s;
	cin >> s;
	int n = (int) s.size();
	s = "!" + s;
	h[n + 1] = 0;
	for (int i = n; i >= 1; --i)
		h[i] = h[i + 1] * base + s[i] - 'a';
	auto GetHash = [&](int l, int r) {
		return h[l] - h[r + 1] * pw[r + 1 - l];
	};

	fenw.init(27);
	vector<int> cnt(26, 0);
	suf[n + 1] = 0;
	for (int i = n; i >= 1; --i) {
		suf[i] = suf[i + 1];
		++cnt[s[i] - 'a'];
		if (cnt[s[i] - 'a'] & 1) ++suf[i];
		else --suf[i];
	}

	int cur = 0;
	cnt = vector<int>(26, 0);
	++cnt[s[1] - 'a'];
	if (cnt[s[1] - 'a'] & 1) ++cur;
	else --cur;
	fenw.upd(cur + 1, 1);
	ll ans = 0;
	for (int i = 2; i < n; ++i) {
		++cnt[s[i] - 'a'];
		if (cnt[s[i] - 'a'] & 1) ++cur;
		else --cur;
		// F(S[1..i]) = cur
		Hash AB = GetHash(1, i);
		// cerr << "i = " << i << '\n';
		// cerr << "AB = " << AB << '\n';
		for (int j = i; j < n; j += i) {
			if (AB != GetHash(j - i + 1, j)) break;
			// cerr << "find [" << j - i + 1 << ", " << j << "]\n";
			int FC = suf[j + 1];
			// cerr << "FC = " << FC << '\n';
			ans += fenw.qry(FC + 1);
			// cerr << "ans += " << fenw.qry(FC) << '\n';
		}
		fenw.upd(cur + 1, 1);
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	hash_init();
	int tt;
	cin >> tt;
	while (tt--) solve();
	return 0;
}