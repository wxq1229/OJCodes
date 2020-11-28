#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 100010;

int bel[N], n, m, k, a[N];

struct Qry {
    int l, r, id, type;
    
    bool operator<(const Qry &o) const {
        if (bel[l] != bel[o.l]) return bel[l] < bel[o.l];
        else return (bel[l] & 1) ? r < o.r : r > o.r;
    }
} qrys[N];
ll ans[N];

vector<Qry> qs[N];
ll res[N << 1], sum1[N], sum2[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m >> k;
    const int BLOCK = sqrt(n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        bel[i] = (i - 1) / BLOCK + 1;
    }
    for (int i = 1; i <= m; ++i) {
        cin >> qrys[i].l >> qrys[i].r;
        qrys[i].id = i;
    }
    const int MAXV = 16384;
    vector<int> vals;
    for (int i = 0; i < MAXV; ++i) if (__builtin_popcount(i) == k)
        vals.push_back(i);
    sort(qrys + 1, qrys + m + 1);
    int curl = 1, curr = 0;
    for (int i = 1; i <= m; ++i) {
        int l = qrys[i].l, r = qrys[i].r;
        if (curl < l) {
            qs[curr].push_back({curl, l - 1, i, -1});
        } else if (l < curl) {
            qs[curr].push_back({l, curl - 1, i, 1});
        }
        curl = l;
        if (curr < r) {
            qs[curl - 1].push_back({curr + 1, r, i + m, -1});
        } else if (r < curr) {
            qs[curl - 1].push_back({r + 1, curr, i + m, 1});
        }
        curr = r;
    }
    vector<int> cnt(MAXV);
    for (int i = 1; i <= n; ++i) {
        sum1[i] = sum1[i - 1] + cnt[a[i]];
        for (auto v : vals) ++cnt[a[i] ^ v];
        sum2[i] = sum2[i - 1] + cnt[a[i]];
        for (auto q : qs[i]) for (int j = q.l; j <= q.r; ++j)
            res[q.id] += cnt[a[j]] * q.type;
    }
    ll cur = 0;
    curl = 1, curr = 0;
    for (int i = 1; i <= m; ++i) {
        int l = qrys[i].l, r = qrys[i].r, id = qrys[i].id;
        cur += res[i] + res[i + m];
        if (curl < l) cur += sum2[l - 1] - sum2[curl - 1];
        else if (l < curl) cur -= sum2[curl - 1] - sum2[l - 1];
        curl = l;
        if (curr < r) cur += sum1[r] - sum1[curr];
        else if (r < curr) cur -= sum1[curr] - sum1[r];
        curr = r;
        ans[id] = cur;
    }
    for (int i = 1; i <= m; ++i)
        cout << ans[i] << '\n';
    return 0;
}