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

int mod;
inline int add(int x,int y) { return (x+=y) >= mod ? x-mod : x; }
inline int sub(int x,int y) { return (x-=y) < 0 ? x+mod : x; }

struct Matrix {
  static const int SZ = 21;
  int a[SZ][SZ], n, m;

  void init(int R=0, int C=0, int v=0) {
    rep(i,0,R+1) rep(j,0,C+1) a[i][j] = v;
    n = R, m = C;
  }

  Matrix(int R=0, int C=0, int v=0) { init(R,C,v); }
};

Matrix I(int n) {
  Matrix ans(n, n);
  rep(i,0,n) ans.a[i][i] = 1;
  return ans;
}

Matrix operator * (const Matrix &a, const Matrix &b) {
  assert(a.m == b.n);
  // cerr << a.n << "," << a.m << " " << b.n << "," << b.m << endl;
  Matrix ans(a.n, b.m);
  rep(i,0,ans.n) rep(j,0,ans.m) rep(k,0,a.m)
    ans.a[i][j] = add(ans.a[i][j], 1ll*a.a[i][k]*b.a[k][j]%mod);
  return ans;
}

Matrix qpow(Matrix A, ll n) {
  assert(A.n==A.m); Matrix ans = I(A.n);
  for (; n; n>>=1, A=A*A) if (n&1) ans = ans*A;
  return ans;
}

char s[233];
int nxt[233], n, m, f[233][233];

void init() {
  nxt[1] = 0;
  rep(i,2,m+1) {
    int j = nxt[i-1];
    while (j && s[j+1] != s[i]) j = nxt[j];
    nxt[i] = j + (s[j+1]==s[i]);
  }
  rep(i,0,m)  rep(j,'0','9'+1) {
    int k = i;
    while (k && s[k+1] != j) k = nxt[k];
    k += s[k+1] == j;
    f[i][k] = add(f[i][k], 1);
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &mod);
  scanf("%s", s+1);
  init();
  Matrix G(m, m);
  rep(i,0,m) rep(j,0,m) G.a[i][j] = f[j][i];
  // rep(i,0,m) { rep(j,0,m) printf("%d ", f[i][j]); puts("");}
  Matrix F(m, 1); F.a[0][0] = 1;
  F = qpow(G, n) * F;
  // rep(i,0,m) rep(j,0,m) printf("%d%c", F.a[i][j], " \n"[j==m-1]); 
  int ans = 0;
  rep(i,0,m) ans = add(ans,F.a[i][0]);
  printf("%d\n", ans);
  return 0;
}