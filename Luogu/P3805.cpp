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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::string foo;
	std::cin >> foo;
	std::string s = "(!";
	for (auto ch : foo) {
		s += ch;
		s += "!";
	}
	s += ")";

	// std::cerr << s << '\n';

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

	int ans = 0;
	for (int i = 0; i < n; ++i)
		ans = std::max(ans, R[i] - 1);
	std::cout << ans << '\n';
	return 0;
}