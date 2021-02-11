#include <bits/stdc++.h>
using i64 = long long;

std::string adjust(const std::string &s) {
	std::string res = "";
	for (auto ch : s) {
		res += "!";
		res += ch;
	}
	res += "!";
    return res;
}
std::vector<int> manacher(const std::string &s) {
	int n = (int) s.size();
	std::vector<int> R(n);
	int p = -1, mx = -1;
	for (int i = 0; i < n; ++i) {
		if (i <= mx) R[i] = std::min(mx - i + 1, R[2 * p - i]);
		else R[i] = 1;
		while (i - R[i] >= 0 && i + R[i] < n && s[i - R[i]] == s[i + R[i]])
			++R[i];
		if (i + R[i] - 1 > mx)
			p = i, mx = i + R[i] - 1;
	}
	return R;
}

constexpr int N = 300010, SIGMA = 26;
int len[2 * N], endpos[2 * N], next[2 * N][SIGMA], link[N * 2], cnt, last;
int newNode() {
	int u = cnt++;
	endpos[u] = len[u] = 0;
	link[u] = -1;
	std::fill(next[u], next[u] + SIGMA, -1);
	return u;
}
void init() {
	cnt = 0;
	last = newNode();
}
void extend(int c) {
	int cur = newNode();
	len[cur] = len[last] + 1;
	endpos[cur] = 1;
	int p = last;
	for (; p != -1 && next[p][c] == -1; p = link[p])
		next[p][c] = cur;
	if (p == -1) link[cur] = 0;
	else {
		int q = next[p][c];
		if (len[q] == len[p] + 1) link[cur] = q;
		else {
			int clone = newNode();
			len[clone] = len[p] + 1;
			link[clone] = link[q];
			std::copy(next[q], next[q] + SIGMA, next[clone]);
			for (; p != -1 && next[p][c] == q; p = link[p])
				next[p][c] = clone;
			link[q] = link[cur] = clone;
		}
	}
	last = cur;
}

constexpr int LOG = 19;
int anc[LOG][2 * N], order[N * 2];

int get(int u, int k) {
	for (int i = LOG - 1; i >= 0; --i) {
		int v = anc[i][u];
		if (v == -1) continue;
		if (len[v] >= k) u = v;
	}
	return u;
}

int at[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	init();
	std::string s;
	std::cin >> s;
	int n = int(s.size());
	for (auto c : s) extend(c - 'a');

	int cur = 0;
	for (int i = 0; i < n; ++i) {
		cur = next[cur][s[i] - 'a'];
		assert(cur != -1);
		at[i] = cur;
	}
	
	std::memset(anc, -1, sizeof anc);
	std::iota(order, order + cnt, 0);
	std::sort(order, order + cnt, [](int i, int j) { return len[i] < len[j]; });
	for (int i = cnt - 1; i > 0; --i) {
		int u = order[i];
		endpos[link[u]] += endpos[u];
	}
	for (int i = 0; i < cnt; ++i)
		anc[0][i] = link[i];
	for (int i = 1; i < LOG; ++i) {
		for (int u = 0; u < cnt; ++u) {
			int v = anc[i - 1][u];
			if (v != -1) anc[i][u] = anc[i - 1][v];
		}
	}
	
	s = adjust(s);
	int m = int(s.size());
	auto R = manacher(s);
	i64 ans = 0;
	for (int i = 1; i < m - 1; ++i) {
		int l = i - R[i] + 1;
		int r = i + R[i] - 1;
		++l, --r;
		if (l > r) continue;
		l /= 2, r /= 2;
		int tot = endpos[get(at[r], r - l + 1)];
		ans = std::max(ans, 1ll * tot * (r - l + 1));
	}
	std::cout << ans << '\n';
	return 0;
}