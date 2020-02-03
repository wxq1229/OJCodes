#include <bits/stdc++.h>
using namespace std;

inline int read() {
    char ch; int f = 1, x = 0; while (!isdigit(ch = getchar())) f = ch == '-' ? -f : f;
    while (isdigit(ch)) { x = (x << 1) + (x << 3) + (ch ^ 48); ch = getchar(); } return x * f;
}

typedef long long ll;
typedef double db;

const db EPS = 1e-9;
const db INF = 1e18;
inline int sign(db a) { return a<-EPS ? -1 : a>EPS;}
const int N = 1e5 + 10;

ll dp[2][N]; int nw;
#define f dp[nw]
#define g dp[nw^1]
int n, K, q[N]; ll s[N];

#define X(i) (s[i])
#define Y(i) (g[i] - s[i]*s[i])
inline db slope(int i, int j) {
    db dx = X(i) - X(j), dy = Y(i) - Y(j);
    if (sign(dx)==0) return sign(dy) * INF; else return dy / dx;
}

int pre[N][210], fst = 1;
void printans(int i, int j) {
    if (!j) return;
    printans(pre[i][j], j - 1);
    if (fst) fst = 0; else putchar(' ');
    printf("%d", pre[i][j]);
}

int main() {
    n = read(), K = read();
    for (int i = 1; i <= n; i++) s[i] = read() + s[i-1];
    nw = 0; for (int it = 1; it <= K; it++) {
        nw ^= 1; int l, r; q[l = r = 1] = 0;
        for (int i = 1; i <= n; i++) {
            while (l<r && slope(q[l+1], q[l]) > -s[i]) l++;
            int j = q[l]; f[i] = g[j] + s[j] * (s[i]-s[j]);
            pre[i][it] = j;
            while (l<r && slope(i, q[r-1]) > slope(q[r], q[r-1])) r--;
            q[++r] = i;
        }
    }
    printf("%lld\n", f[n]), printans(n, K);
    return 0;
}
