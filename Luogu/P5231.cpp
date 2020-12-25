#include <bits/stdc++.h>

constexpr int N = 1e7 + 10, SIGMA = 4;

inline int idx(char ch) {
	if (ch == 'E') return 0;
	if (ch == 'S') return 1;
	if (ch == 'W') return 2;
	if (ch == 'N') return 3;
	return -1;
}

struct Node {
	int go[SIGMA], fail, id;
	
	Node() { std::memset(go, -1, sizeof go); fail = id = -1; }
} t[N];
int cntNodes = 0;
inline int newNode() { int u = cntNodes++; t[u] = Node(); return u; }
int root = newNode();

int fa[N], depth[N];

int append(int u, int c) {
	int &v = t[u].go[c];
	if (v == -1) v = newNode();
	fa[v] = u, depth[v] = depth[u] + 1;
	return v;
}

void build() {
	std::queue<int> que;
	
	for (int i = 0; i < SIGMA; ++i) {
		int &v = t[root].go[i];
		if (v == -1) v = root;
		else t[v].fail = root, que.push(v);
	}
	
	while (que.size()) {
		int u = que.front();
		que.pop();
		for (int i = 0; i < SIGMA; ++i) {
			int &v = t[u].go[i];
			if (v == -1) v = t[t[u].fail].go[i];
			else t[v].fail = t[t[u].fail].go[i], que.push(v);	
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	
	int n, m;
	std::string s;
	std::cin >> n >> m >> s;

	std::vector<int> ends(m);

	for (int i = 0; i < m; ++i) {
		std::string foo;
		std::cin >> foo;
		int u = root;
		for (auto ch : foo)	u = append(u, idx(ch));
		ends[i] = u;
	}

	build();
	std::vector<int> res(cntNodes);
	{
		int u = root;
		for (auto ch : s) {
			u = t[u].go[idx(ch)];
			res[u] = 1;
		}
	}

	std::vector<std::vector<int>> e(cntNodes);
	for (int i = 1; i < cntNodes; ++i) {
		int u = t[i].fail, v = i;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	
	std::function<void(int, int)> dfs = [&](int u, int f) {
		for (auto v : e[u]) if (v != f)
			dfs(v, u), res[u] |= res[v];
	};

	dfs(root, -1);
	for (int i = 0; i < m; ++i) {
		int u = ends[i];
		while (u != root && !res[u]) u = fa[u];
		std::cout << depth[u] << '\n';
	}
	return 0;
}