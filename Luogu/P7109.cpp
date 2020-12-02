#include <bits/stdc++.h>
using std::cin;
using std::cout;

const int N = 1010;

bool query(int i, int j) {
    cout << "? " << i << " " << j << '\n';
    cout.flush();
    bool full;
    cin >> full;
    return full;
}

int ans[N], more[N];

int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        ans[i] = -1;
    int ptr = n;
    ans[1] = query(1, 1);
    while (ptr && query(ptr, ptr)) --ptr;
    if (ptr <= 1) {
        cout << "! ";
        for (int i = 1; i <= n; ++i)
            cout << (i == 1 ? ans[i] : i) << " ";
        cout << '\n';
        cout.flush();
        return 0;
    }
    query(1, ptr);
    more[ptr] += ans[1];
    auto Get = [&](int i) {
        if (query(i, i)) return i;
        int lo = 1, hi = i - 1, res = -1;
        while (lo <= hi) {
            int mid = (lo + hi) >> 1;
            if (query(i, mid))
                res = mid, lo = mid + 1;
            else hi = mid - 1;
            query(mid, i);
        }
        return res == -1 ? 0 : res;
    };
    for (int i = 2; i <= ptr; ++i) {
        // std::cerr << "Asking " << i << '\n';
        ans[i] = Get(i) - more[i];
        int rem = ans[i];
        while (rem != 0 && i <= ptr) {
            if (query(i, ptr)) {
                int nxt = Get(i);
                more[ptr] += rem - nxt;
                rem = nxt;
                --ptr;
            } else {
                more[ptr] += rem;
                rem = 0;
                break;
            }
        }
    }
    // for (int i = 1; i <= n; ++i) std::cerr << more[i] << " ";
    // std::cerr << '\n';
    for (int i = 1; i <= n; ++i)
        if (ans[i] == -1) ans[i] = i - more[i];
    cout << "! ";
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " \n"[i == n];
    cout.flush();
    return 0;
}

/*
2
1 2

3
0 2 1
0 0 3
*/