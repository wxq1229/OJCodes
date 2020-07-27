#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i = (int)(a); i <= (int)(b); i++)
#define ROF(i,a,b) for (int i = (int)(a); i >= (int)(b); i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second 
typedef pair<int,int> pii;
typedef long double ld;
typedef long long ll;

const int N = 5e5 + 10;
const ll inf = 1e18;
ll a[N], s[N];
int n, k;

inline ll w(int i,int j) {
	int mid = (i+j) >> 1;
	return a[mid]*(mid-i+1) - (s[mid]-s[i-1]) + (s[j]-s[mid-1]) - a[mid]*(j-mid+1);
}

struct node { int p,l,r; };
ll ans, dp[N];
int cnt[N];
int calc(ll mid) {
	auto trans = [&](int i,int j) {
		assert(i < j);
		return dp[i] - mid + w(i+1,j);
	};
	static node q[N];
	node *ql = q+1, *qr = q;
	*(++qr) = (node){0,1,n};
	FOR(i,1,n) {
		while (ql<qr && i>ql->r) ++ql;
		dp[i] = trans(ql->p, i);
		cnt[i] = cnt[ql->p] + 1;
		while (ql <= qr && i<qr->l && trans(i, qr->l) <= trans(qr->p, qr->l))
			--qr;
		if (qr == q) {
			*(++qr) = (node){i,i+1,n};
			continue;
		}
		int lo = max(i,qr->l)+1, hi = qr->r, p = qr->r + 1;
		while (lo <= hi) {
			int mid = (lo+hi) >> 1;
			if (trans(i,mid) <= trans(qr->p,mid)) hi = mid-1, p = mid;
			else lo = mid+1;
		}
		if (p != n+1) {
			qr->r = p-1;
			*(++qr) = (node){i,p,n};
		}
	}
	ans = dp[n];
	return cnt[n];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> k;
	FOR(i,1,n) cin>>a[i], s[i] = s[i-1]+a[i];
	ll lo = -1e9, hi = 0, p = -1;
	while (lo <= hi) {
		ll mid = (lo+hi)>>1;
		if (calc(mid) >= k) hi = mid-1, p = mid;
		else lo = mid+1;
	}
	calc(p);
	cout << ans + p * k << '\n';
	return 0;
}