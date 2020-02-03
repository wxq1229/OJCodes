#include <bits/stdc++.h>
using namespace std;

inline int read() {
	int x = 0, f = 1; char ch; while (!isdigit(ch = getchar())) f = ch=='-' ? -f : f;
	while (isdigit(ch)) { x = x*10 + ch - '0'; ch = getchar(); } return x * f;
}

int fpow(int a, int b, int c) {
	int ret = 1;
	for (a %= c; b; b >>= 1, a = 1ll * a * a % c) if (b&1) ret = 1ll*ret*a % c;
	return ret;
}

int exgcd(int a, int b, int &x, int &y){
	if (b == 0) { x = 1, y = 0; return a; }
	int d = exgcd(b, a%b, x, y), tmp = x;
	x = y, y = tmp - a/b * y; return d;
}


int BSGS(int a, int b, int n, int &ret) {
	a %= n, b %= n;
	if (a == 0) { if (b == 0) { ret = 0; return 1; } else return 0; }
	int m = ceil(sqrt(n)); map<int,int> h;
	for (int tmp = b%n, i = 0; i <= m; i++, tmp = 1ll*tmp*a % n) h[tmp] = i;
	a = fpow(a, m, n);
	for (int tmp = a%n, i = 1; i <= m; i++, tmp = 1ll*tmp*a % n)
		if (h.count(tmp)) { ret = 1ll*i*m - h[tmp]; return 1; }
	return 0;
}

int main(){
	for (int T = read(), K = read(); T; T--) {
		int a = read(), b = read(), c = read();
		if (K == 1) printf("%d\n", fpow(a, b, c));
		else if (K == 2) {
			int x, y, d = exgcd(a, c, x, y);
			if (b % d != 0) puts("Orz, I cannot find x!");
			else {
				x  = 1ll * b / d * x % c, x = (x % c + c) % c;
				printf("%d\n", x);
			}
		} else if (K == 3) {
			int ans, flg = BSGS(a, b, c, ans);
			if (!flg) puts("Orz, I cannot find x!"); else printf("%d\n", ans);			
		}
	}
	return 0;
}
