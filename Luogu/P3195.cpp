#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 1; char ch; while (!isdigit(ch = getchar())) f = ch=='-' ? -f : f;
	while (isdigit(ch)){ x = x*10 + ch - '0'; ch = getchar(); } return x*f;
}

typedef long long ll;
typedef double db;

const int N = 5e4+10;
int q[N], n, L;
ll a[N], b[N], f[N], s[N];

#define X(i) (b[i])
#define Y(i) (f[i] + b[i]*b[i])
inline db slope(int i, int j) {
	return 1.0 * (Y(j) - Y(i)) / (X(j) - X(i));
}

int main(){
	n = read(), L = read();
	for (int i = 1; i <= n; i++) s[i] = read();
	for (int i = 1; i <= n; i++) { s[i] += s[i-1]; a[i] = s[i]+i; b[i] = s[i]+i+L+1; }
	a[0] = 0, b[0] = L + 1;
	int l = 1, r = 1; q[1] = 0;
	for (int i = 1; i <= n; i++) {
		while (l<r && slope(q[l], q[l+1]) < 2.0*a[i]) l++;
		int j = q[l]; // printf("%d -> %d", j, i); puts("");
//		cout << a[i] << " " << b[j] << endl;
		f[i] = f[j] + (a[i]-b[j]) * (a[i]-b[j]);
//		cout << "f[" << i << "] = " << f[i] << endl;
		while (l<r && slope(q[r-1], q[r]) > slope(q[r-1], i)) r--;
		q[++r] = i;
	}
	printf("%lld\n", f[n]);
	return 0;
}
