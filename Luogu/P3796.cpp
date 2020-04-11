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

const int N=1e6+10,SIGMA=30;

int ans[N];

struct AC_automation {
	struct node {
		int fail,go[SIGMA],id;
	}t[N];
	int root=0,cnt=0;
	inline void init() { root=0,cnt=0; clr(root); }
	inline void clr(int u) {		
		t[u].fail=t[u].id=0;
		rep(i,0,26) t[u].go[i]=0;
	}
	inline int newnode() {int u=++cnt; clr(u); return u;}

	void insert(char *s,int k) {
		int n=strlen(s),u=root;
		rep(i,0,n) {
			int c=s[i]-'a';
			if (!t[u].go[c]) t[u].go[c]=newnode();
			u=t[u].go[c];
		}
		t[u].id=k;
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
	}

	void query(char *s) {
		int n=strlen(s),u=root;
		rep(i,0,n) {
			int c=s[i]-'a'; u=t[u].go[c];
			for (int j=u;j;j=t[j].fail) ans[t[j].id]++;
		}
	}
}ac;

int n,p[2333];
char s[2333][2333];
char ss[1010000];

int main() {
#ifdef LOCAL
	freopen("A.in","r",stdin);
#endif
	while (scanf("%d",&n)==1&&n) {
		ac.init(); rep(i,0,n+1) ans[i]=0;
		rep(i,1,n+1) scanf("%s",s[i]),ac.insert(s[i],i);
		ac.build();
		scanf("%s",ss);
		ac.query(ss);
		rep(i,1,n+1) p[i]=i;
		sort(p+1,p+n+1,[](int i,int j) {
			return ans[i]>ans[j]||(ans[i]==ans[j]&&i<j);
		});
		int mx=ans[p[1]];
		printf("%d\n",mx);
		rep(i,1,n+1) if (ans[p[i]]==mx) puts(s[p[i]]); else break;
	}
	return 0;
}