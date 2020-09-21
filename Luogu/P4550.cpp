#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using vi = vector<int>;
using db = double;

db f[10010], g[10010];
int n;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	f[n] = 0;
	for (int i=n-1; i>=0; --i)
		f[i] = f[i+1] + (db)n / (n-i);
	g[n] = 0;
	for (int i=n-1; i>=0; --i)
		g[i] = (2.0*i/n*f[i] + (db)(n-i)/n*g[i+1] + 2.0*(n-i)/n*f[i+1] + 1) / ((db)(n-i)/n);
	cout << fixed << setprecision(2) << 0.5 * (g[0] + f[0]) << '\n';
	return 0;
}
