#include <bits/stdc++.h>

template <typename A, typename B> 
std::ostream &operator<<(std::ostream &os, const std::pair<A, B> &p) {
	os << "{" << p.first << ", " << p.second << "}";
	return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
	bool fst = true;
	os << "{";
	for (auto t : v) {
		if (fst) fst = false;
		else os << ", ";
		os << t;
	}
	os << "}";
	return os;
}

std::vector<int> getNext(const std::string &s) {
	int n = (int) s.size();
	std::vector<int> nxt(n);
	nxt[0] = -1;
	for (int i = 1; i < n; ++i) {
		int j = nxt[i - 1];
		while (j != -1 && s[j + 1] != s[i])
			j = nxt[j];
		nxt[i] = j + (s[j + 1] == s[i]);
	}
	return nxt;
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::string s;
	std::cin >> s;
	
	auto R = manacher(s);
	int n = int(s.size());
	int singleLen = -1, singleP = -1;
	for (int i = 0; i < n; ++i)
		if (2 * R[i] - 1 > singleLen) {
			singleLen = 2 * R[i] - 1;
			singleP = i - R[i] + 1;
		}

	auto t = s;
	std::reverse(t.begin(), t.end());
	t += "!" + s;
	auto nxt = getNext(t);
	
	// std::cerr << t << '\n' << nxt << '\n';

	std::vector<std::pair<int, int>> mx(n);
	for (int i = n + 1; i < n * 2 + 1; ++i) {
		mx[i - n - 1].first = nxt[i] + 1;
		mx[i - n - 1].second = i - n - 1;
	}
	for (int i = 1; i < n; ++i)
		mx[i] = std::max(mx[i], mx[i - 1]);

	std::vector<int> x(3), l(3);
	int len = 0;
	bool found = false;
	for (int i = 0; i < n; ++i) {
		int left = i - R[i], right = i + R[i];
		while (left < 0 || right > n - 1)
			++left, --right;
		if (left >= right) continue;
		// std::cerr << left << " " << right << '\n';
		int tlen = std::min(mx[left].first, n - right);
		int tmp = tlen * 2 + (i - left) * 2 - 1;
		if (tmp > len && tlen) {
			found = true;
			len = tmp;
			x[0] = mx[left].second - tlen + 1;
			l[0] = tlen;
			x[1] = left + 1;
			l[1] = (i - left) * 2 - 1;
			x[2] = n - tlen;
			l[2] = tlen;
		}
	}
	if (len > singleLen) {
		std::cout << "3\n";
		for (int i = 0; i < 3; ++i)
			std::cout << x[i] + 1 << " " << l[i] << '\n';
	} else {
		std::cout << "1\n";
		std::cout << singleP + 1 << " " << singleLen << '\n';
	}

	return 0;
}