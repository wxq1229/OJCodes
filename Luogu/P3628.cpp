#include <bits/stdc++.h>
using namespace std;

inline int read() {
    char ch; int x = 0, f = 1; while (!isdigit(ch = getchar())) f = ch == '-' ? -f : f;
    while (isdigit(ch)) { x = (x<<1) + (x<<3) + (ch^48); ch = getchar(); } return x * f;
}

typedef double db;
typedef long long ll;

const int N = 1e6 + 10;
int q[N], n, a, b, c;
ll f[N], s[N];

#define X(i) (1ll*s[i])
#define Y(i) (f[i] + 1ll*a*s[i]*s[i] - 1ll*b*s[i] + 1ll*c)
inline db slope(int i, int j) {
    return 1.0 * (Y(i) - Y(j)) / (X(i) - X(j));
}

int main() {
    n = read(), a = read(), b = read(), c = read();
    for (int i = 1; i <= n; i++) s[i] = read() + s[i-1];
    int l, r; q[l = r = 1] = 0;
    for (int i = 1; i <= n; i++) {
        while (l<r && slope(q[l+1], q[l]) > 2ll*a*s[i]) l++;
        int j = q[l]; f[i] = f[j] + 1ll * a * (s[i]-s[j])*(s[i]-s[j]) + 1ll * b*(s[i]-s[j]) + 1ll * c;
        while (l<r && slope(i, q[r-1]) > slope(q[r], q[r-1])) r--;
        q[++r] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}