#include <bits/stdc++.h>
using namespace std;

inline int read() {
    char ch; int x=0, f=1; while (!isdigit(ch = getchar()))  f = ch == '-' ? -f : f;
    while (isdigit(ch)) { x = x*10+ch-'0'; ch = getchar(); } return x * f;
}

const int P = 1e9 + 7;

int fpow(int a, int b) {
    int ret = 1;
    for (a %= P; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) ret = 1ll * ret * a % P;
    return ret;
}

int main() {
    int n = read(), K = read();
    printf("%d\n", fpow(fpow(2, K), n));
    return 0;
}