#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a; i<n; i++)
#define per(i,a,n) for (int i=n-1; i>=a; i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef pair<int,int> pii;
typedef long long ll;
typedef vector<int> VI;

const int N = 6010, mod = 10007, SIGMA = 26;

inline int add(int x,int y) { return (x+=y) >= mod ? x-mod : x; }
inline int sub(int x,int y) { return (x-=y) < 0 ? x+mod : x; }

inline int qpow(int x,int y) {
  int ans = 1; for (; y; y>>=1, x=1ll*x*x%mod)
    if (y&1) ans = 1ll*ans*x%mod;
  return ans;
}

struct node {
  int go[SIGMA], fail;
  int flg;
  void clear() {
    memset(go,0,sizeof(go));
    fail = flg = 0;
  }
} t[N];
int cnt, root;

void init() { cnt = root = 0; t[root].clear(); }
int newnode() { int u = ++cnt; t[u].clear(); return u; }

inline int append(int u,int c) { 
  if (!t[u].go[c]) t[u].go[c] = newnode();
  return t[u].go[c];
}

void build() {
  VI q; int u=root;
  rep(i,0,SIGMA) if (t[u].go[i]) t[t[u].go[i]].fail = u, q.pb(t[u].go[i]);
  rep(cur,0,SZ(q)) {
    int u = q[cur];
    t[u].flg |= t[t[u].fail].flg;
    rep(i,0,SIGMA) {
      int &v = t[u].go[i];
      if (!v) v = t[t[u].fail].go[i];
      else t[v].fail = t[t[u].fail].go[i], q.pb(v);
    }
  }
}

int f[N][N], n, m;
char s[N];

int main() {
  scanf("%d%d", &n, &m);
  rep(i,0,n) {
    scanf("%s", s);
    int len = strlen(s), u = root;
    rep(j,0,len) u = append(u, s[j] - 'A');
    t[u].flg = 1;
  }
  build();
  f[0][root] = 1;
  rep(i,0,m) rep(u,0,cnt+1) if (!t[u].flg) {
    rep(c,0,SIGMA) {
      int v = t[u].go[c];
      if (t[v].flg) continue;
      f[i+1][v] = add(f[i+1][v], f[i][u]);
    }
  }
  int ans = qpow(26, m);
  rep(i,0,cnt+1) if (!t[i].flg) ans = sub(ans,f[m][i]);
  printf("%d\n", ans);
  return 0;
}