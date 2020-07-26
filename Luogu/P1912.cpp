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

const ld inf = 1e20;
const int N = 1e5 + 10;

ld qpow(ld a, int b) { ld ans = 1; for (; b; b>>=1, a*=a) if (b&1) ans*=a; return ans; }

int n, l, p, sum[N];
string str[N];
ld dp[N];
int q[N], pre[N];

inline ld trans(int i,int j) { return dp[i]+qpow(fabs(sum[j]-sum[i]-1-l),p); }

int getpos(int i,int j) {
	int lo = j+1, hi = n, p = n+1;
	while (lo <= hi) {
		int mid = (lo+hi)>>1;
		if (trans(i,mid) >= trans(j,mid)) {
			p = mid; hi = mid-1;
		}
		else lo = mid+1;
	}
	return p;
}

void solve() {
	cin>>n>>l>>p;
	FOR(i,1,n) dp[i] = inf;
	dp[0] = 0;
	sum[0] = 0;
	FOR(i,1,n) {
		cin>>str[i];
		sum[i] = sum[i-1] + str[i].size() + 1;
	}
	int ql=1, qr=0;
	q[++qr] = 0;
	FOR(i,1,n) {
		while (ql<qr && i>=getpos(q[ql],q[ql+1])) ++ql;
		dp[i] = trans(q[ql], i);
		pre[i] = q[ql];
		while (ql<qr && getpos(q[qr-1],q[qr])>=getpos(q[qr],i)) --qr;
		q[++qr] = i;
	}
	// cerr << dp[n] << endl;
	if (dp[n] > 1e18) cout << "Too hard to arrange\n";
	else {
		cout<<fixed<<setprecision(0)<<dp[n]<<'\n';
		static int stk[N];
		int top=0, now=n;
		while (now) stk[++top]=now, now = pre[now];
		stk[++top] = 0;
		ROF(i,top,2) {
			int l = stk[i]+1, r = stk[i-1];
			FOR(j,l,r) cout << str[j] << (j==r ? "\n" : " ");
		}
	}
	cout << "--------------------\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin>>T; while (T--) solve();
	return 0;
}