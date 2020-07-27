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
inline ld qpow(ld a, ll b) { ld ans=1; for (; b; b>>=1,a*=a) if (b&1) ans*=a; return ans; }

const int MXN = 1e5 + 10;
ld dp[MXN];
int pre[MXN], s[MXN], N, P, L;
string str[MXN];

inline ld trans(int i,int j) {
	assert(i<j);
	return dp[i] + qpow(fabs(s[j]-s[i]-1-L), P);
}

struct node { int p,l,r; };

void solve() {
	cin>>N>>L>>P;
	FOR(i,1,N) cin >> str[i], s[i] = s[i-1]+str[i].size()+1;
	static node q[MXN];
	node *ql = q+1, *qr = q;
	*(++qr) = (node){0,1,N};
	FOR(i,1,N) {
		while (ql<qr && ql->r < i) ++ql;
		dp[i] = trans(ql->p, i);
		pre[i] = ql->p;
		while (ql<=qr && i<qr->l && trans(i,qr->l) <= trans(qr->p,qr->l)) --qr;
		if (qr == q) {
			*(++qr) = (node){i,i+1,N};
			continue;
		}
		int lo = max(qr->l,i)+1, hi = qr->r, p = qr->r + 1;
		while (lo<=hi) {
			int mid=(lo+hi)>>1;
			if (trans(i,mid) <= trans(qr->p,mid)) hi=mid-1, p=mid;
			else lo=mid+1;
		}
		if (p != N+1) {
			qr->r = p-1;
			*(++qr) = (node){i,p,N};
		}
	}
	if (dp[N] <= 1e18) {
		cout<<fixed<<setprecision(0)<<dp[N]<<endl;
		vector<pii> stk;
		int now = N;
		while (now) stk.pb(mp(pre[now]+1, now)), now = pre[now];
		while (stk.size()) {
			pii seg = stk.back(); stk.pop_back();
			FOR(i,seg.fi,seg.se) cout<<str[i]<<(i==seg.se ? "\n" : " ");
		}
	} else {
		cout<<"Too hard to arrange\n";
	}
	cout<<"--------------------\n";
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int T; cin>>T; while(T--) solve();
	return 0;
}