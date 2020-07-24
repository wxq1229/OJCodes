#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for (int i=(int)(a); i<=(int)(b); ++i)
#define ROF(i,a,b) for (int i=(int)(a); i>=(int)(b); --i)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
typedef pair<int,int> pii;

inline string to_bin(unsigned int x) {
	string ans = "";
	while (x) ans = (char) ((x&1) + 48) + ans, x >>= 1;
	return ans; 
}

const int N = 16, INF = 0x3f3f3f3f;
int n, f[(1<<15)+10][N][N], a[N], sum[(1<<15)+10];
int pos[(1<<15)+10][N][N];
struct node {
	int s,i,j;
}pre[(1<<15)+10][N][N];

vector<pii> opt;
int at[N];

void print(node now) {
	if (now.s == 0) return;
	print(pre[now.s][now.i][now.j]);
	node pr = pre[now.s][now.i][now.j];
	int s0 = now.s ^ pr.s, to = now.j;
	FOR(i,1,n) if ((s0 & (1<<(i-1))) && i != to) {
		opt.pb(mp(at[i],at[to]));
		FOR(j,i+1,n) --at[j];
	}
}

void solve() {
	cin>>n; FOR(i,1,n) cin>>a[i];
	FOR(s,0,(1<<n)-1) {
		sum[s] = 0;
		FOR(i,0,n-1) if (s&(1<<i)) sum[s]+=a[i+1];
	}
	FOR(s,0,(1<<n)) FOR(i,0,n) FOR(j,0,n) {
		f[s][i][j] = INF;
		pre[s][i][j] = (node){11,45,14};
	}
	f[0][0][0] = 0;
	int all = (1<<n)-1;
	FOR(s,0,all-1) {
		int bcnt = __builtin_popcount(s);
		FOR(i,0,bcnt) FOR(j,0,n-1) if (f[s][i][j] != INF) {
			// cerr<<"F\n";
			int u = all - s;
			for (int t = u; t; t = (t - 1) & u) {
				int s0 = s | t;
				// cerr << s << " " << i << " " << j << " -> "
					// << s0 << " " << i+1 << " " << j+__builtin_ctz(t)+1 << endl;
				if (sum[t] > f[s][i][j] && (t>>j) && sum[t] < f[s0][i + 1][j + __builtin_ctz(t>>j) + 1]) {
					f[s0][i + 1][j + __builtin_ctz(t>>j) + 1] = sum[t];
					// cerr << s << " " << i << " " << j << " -> "
						// << s0 << " " << i+1 << " " << j+__builtin_ctz(t)+1 << endl;
					pre[s0][i+1][j+__builtin_ctz(t>>j)+1] = (node){s,i,j};
				}
			}
		}
	}

	node ans = (node){11,45,14};
	ROF(i,n,1) {
		bool flg=0;
		FOR(j,1,n) if (f[all][i][j] != INF) {
			flg=1, ans = (node){all,i,j};
			break;
		}
		if (flg) break;
	}
	// cerr << to_bin(ans.s) << " " << ans.i << " " << ans.j << " " << f[ans.s][ans.i][ans.j] << endl;
	cout << n-ans.i << "\n";
	opt.clear(); FOR(i,1,n) at[i] = i;
	print(ans);
	for (auto o:opt) cout << o.fi << " " << o.se << '\n';
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tt; cin>>tt; while(tt--) solve();
	return 0;
}