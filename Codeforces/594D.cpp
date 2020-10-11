#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef pair<int,int> pii;
typedef long long ll;

const int P = 1e9 + 7;
inline int mpow(int a, int b = P - 2) {
	int ans = 1;
	for (; b; b >>= 1, a = (ll) a * a % P)
		if (b & 1) ans = (ll) ans * a % P;
	return ans;
}

const int N = 2e5 + 10;
vector<int> factor(int n) {
	vector<int> d;
	for (ll i = 2; i * i <= n; ++i) if (n % i == 0) {
		d.push_back(i);
		while (n % i == 0) n /= i;
	}
	if (n > 1) d.push_back(n);
	return d;
}

vector<int> p[N];
vector<pii> qs[N];
int a[N], n, Q;

int bt[N];
void upd(int x, int v) {
	for (; x <= n; x += x & -x)
		bt[x] = (ll) bt[x] * v % P;
}
int qry(int x) {
	int ans = 1;
	for (; x; x -= x & -x)
		ans = (ll) ans * bt[x] % P;
	return ans;
}

int ans[N], mul[N], imul[N];
int pos[1000010];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	imul[0] = 1;
	mul[0] = 1;
	for (int i = 0; i <= n; ++i)
		bt[i] = 1;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i];
		p[i] = factor(a[i]);
		mul[i] = (ll) mul[i - 1] * a[i] % P;
		imul[i] = mpow(mul[i]);
	}
	cin >> Q;
	for (int i = 1; i <= Q; ++i) {
		int l, r;
		cin >> l >> r;
		qs[r].pb(mp(l, i));
	}
	memset(pos, -1, sizeof(pos));
	for (int i = 1; i <= n; ++i) {
		for (auto pr : p[i]) {
			int tmp = (ll) (pr - 1) * mpow(pr) % P;
			int itmp = mpow(tmp);
			if (pos[pr] != -1) upd(pos[pr], itmp);
			pos[pr] = i;
			upd(i, tmp);
		}
		for (auto q : qs[i]) {
			int l = q.fi, r = i;
			int tmp = (ll) qry(r) * mpow(qry(l - 1)) % P;
			ans[q.se] = (ll) tmp * mul[r] % P * imul[l - 1] % P;
		}
	}
	for (int i = 1; i <= Q; ++i)
		cout << ans[i] << '\n';
	return 0;
}