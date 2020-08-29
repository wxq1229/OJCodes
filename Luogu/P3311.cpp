#include <bits/stdc++.h>
using namespace std;

const int N = 3010;
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

void init() { root = cnt = 0; }

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
void upd(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	init();
    bool flg = 0;
	string str;
	cin >> str;
	int len = (int) str.size(), n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		string s;
		cin >> s;
        flg |= s == "0";
		int u = root;
		for (auto c : s)
			u = append(u, c - '0');
		t[u].val = 1;
	}
	build();
    vector<vector<int>> dp(cnt + 1, vector<int>(3));
    dp[root][2] = 1;
    for (int i = 0; i < len; ++i) {
        vector<vector<int>> new_dp(cnt + 1, vector<int>(3));
        for (int j = 0; j <= cnt; ++j) {
            for (int c = 0; c < SIGMA; ++c) {
                int nj = t[j].go[c];
                if (t[nj].val) continue;
                upd(new_dp[nj][0], dp[j][0]);
                if (c < str[i] - '0') upd(new_dp[nj][0], dp[j][1]);
                if (c == str[i] - '0') upd(new_dp[nj][1], dp[j][1]);
                if (c == 0) {
                    upd(new_dp[j][2], dp[j][2]);
                } else {
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
	for (int i = 0; i <= cnt; ++i)
		upd(ans, dp[i][0]), upd(ans, dp[i][1]);
	cout << ans << '\n';
	return 0;
}