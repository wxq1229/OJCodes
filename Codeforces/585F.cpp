#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &a) {
	bool first = true;
	os << "{";
	for (auto v : a) {
		if (first) first = false;
		else os << ", ";
		os << v;
	}
	os << "}";
	return os;
}

const int N = 5e5 + 10;
const int SIGMA = 10;

struct node {
	int go[SIGMA], fail;
	bool val;
	
	void init() {
		memset(go, 0, sizeof(go));
		fail = val = 0;
	}
} t[N];
int cnt, root;

void init() { root = cnt = 0; t[root].init(); }

inline int newnode() {
	t[++cnt].init(); return cnt;
}

int append(int u, int c) {
	if (!t[u].go[c])
		t[u].go[c] = newnode();
	return t[u].go[c];
}

void build() {
	queue<int> q;
	for (int i = 0; i < SIGMA; ++i)
		if (t[root].go[i] == 0) {
			t[root].go[i] = root;
		} else {
			q.push(t[root].go[i]);
			t[t[root].go[i]].fail = root;
		}
	while (q.size()) {
		int u = q.front();
		q.pop();
//		cerr << u << '\n';
		t[u].val |= t[t[u].fail].val;
		for (int i = 0; i < SIGMA; ++i) {
			int &v = t[u].go[i];
			if (!v) {
				v = t[t[u].fail].go[i];
			} else {
				q.push(v);
				t[v].fail = t[t[u].fail].go[i];
			}
		}
	}	
}

const int P = 1e9 + 7;
void upd(int &x, int y) { x += y; if (x >= P) x -= P; }

int solve(string str) {
	int n = (int) str.size();
    vector<vector<int>> dp(cnt + 1, vector<int>(3));
    dp[root][2] = 1;
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> new_dp(cnt + 1, vector<int>(3));
        for (int j = 0; j <= cnt; ++j) {
            for (int c = 0; c < SIGMA; ++c) {
                int nj = t[j].go[c];
				if (c == 0) upd(new_dp[j][2], dp[j][2]);
                if (t[nj].val) continue;
                upd(new_dp[nj][0], dp[j][0]);
                if (c < str[i] - '0') upd(new_dp[nj][0], dp[j][1]);
                if (c == str[i] - '0') upd(new_dp[nj][1], dp[j][1]);
                if (c != 0) {
                    if (i == 0) {
                        if (c <= str[i] - '0')
                            upd(new_dp[nj][c == str[i] - '0'], dp[j][2]);
                    } else {
                        upd(new_dp[nj][0], dp[j][2]);
                    }
                }
            }
        }
        swap(dp, new_dp);
    }
	int ans = 0;
	for (auto c : str)
		ans = ((ll) ans * 10 + c - '0') % P;
//	cerr << "bef: " << ans << '\n';
	for (int i = 0; i <= cnt; ++i) {
		upd(ans, P - dp[i][0]);
		upd(ans, P - dp[i][1]);
	}
//	cerr << str << ": " << ans << '\n';
	return ans;
}

int main() {
#ifdef LOCAL
	freopen("a.in", "r", stdin);
#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	string s, x, y;
	cin >> s >> x >> y;
	int d = x.size();
	--x[d - 1];
	for (int i = d - 2; i >= 0; --i)
		if (x[i + 1] < '0') x[i + 1] += 10, --x[i];
	while (x[0] == '0') x.erase(0, 1);
	init();
//	cerr << x << " " << y << '\n';
	int n = (int) s.size(), len = max(1, d / 2);
	for (int i = 0; i + len - 1 < n; ++i) {
		string sub = s.substr(i, len);
		int u = root;
//		cerr << "ins " << sub << '\n';
		for (char c : sub)
			u = append(u, c - '0');
		t[u].val = 1;
	}
	build();
	cout << ((ll) P - solve(x) + solve(y)) % P << '\n';
	return 0;
}
