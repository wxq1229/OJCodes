#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef long long ll;
typedef double db;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=2e6+10,SIGMA=30;

int n;
char s[N];
struct node {
	int go[SIGMA],fail,id;
}t[N];
int root=0,cnt=0,at[N],sum[N];

inline void clr(int u) {
	memset(t[u].go,0,sizeof(t[u].go));
	t[u].fail=t[u].id=0;
}
inline void init() {root=0,cnt=0;clr(root);}
inline int newnode() {int u=++cnt;clr(u);return u;}

void insert(char *s,int k) {
	int n=strlen(s),u=root;
	rep(i,0,n) {
		int c=s[i]-'a'; if (!t[u].go[c]) t[u].go[c]=newnode();
		u=t[u].go[c];
	}
	t[u].id=k,at[k]=u;
}

void build() {
	queue<int> q; int u=root;
	rep(i,0,26) if (t[u].go[i])
		t[t[u].go[i]].fail=u,q.push(t[u].go[i]);
	while (q.size()) {
		int u=q.front(); q.pop();
		rep(i,0,26) {
			int &v=t[u].go[i];
			if (!v) v=t[t[u].fail].go[i];
			else t[v].fail=t[t[u].fail].go[i],q.push(v);
		}
	}
	// rep(i,1,cnt+1) printf("%d ",t[i].fail); puts("");
}

VI e[N];
void buildFail() {
	rep(i,1,cnt+1)
		e[i].pb(t[i].fail),e[t[i].fail].pb(i);
}
void dfs(int u,int ff) { for (auto v:e[u]) if (v!=ff) dfs(v,u),sum[u]+=sum[v]; }
void find(char *s) {
	int n=strlen(s),u=root;
	rep(i,0,n) u=t[u].go[s[i]-'a'],++sum[u];
}

int main() {
#ifdef LOCAL
	freopen("A.in","r",stdin);
#endif
	scanf("%d",&n); init();
	rep(i,1,n+1) scanf("%s",s),insert(s,i);
	build();
	scanf("%s",s);
	find(s),buildFail();
	dfs(root,-1);
	rep(i,1,n+1) printf("%d\n",sum[at[i]]);
	return 0;
}