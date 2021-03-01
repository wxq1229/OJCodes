#include <bits/stdc++.h>
using ld = long double;
constexpr ld EPS = 1e-7;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.precision(6);
    std::cout << std::fixed;

    int tt;
    std::cin >> tt;
    while (tt--) {
        ld a, b, S;
        std::cin >> a >> b >> S;
        if (a * b < S) std::cout << 0.L << "%\n";
        else if (std::fabs(S) < EPS) std::cout << 100.L << "%\n";
        else {
            ld c = S / b;
            ld all = a * b;
            ld p = all - S * (std::log(a) - std::log(c)) - S;
            ld ans = p / all * 100;
            std::cout << ans << "%\n";
        }
    }
    
    return 0;
}