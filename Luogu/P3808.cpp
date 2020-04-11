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

const int SIGMA=30,N=1e6+10;

struct AC_automation {
	struct node {
		int go[SIGMA],fail,cnt;
	}t[N]; 
	int cnt,root;
	void init() { cnt=0,root=0; rep(i,0,SIGMA) t[root].go[i]=0; }
	inline int newnode() {
		int u=++cnt; rep(i,0,26) t[u].go[i]=0; 
		t[u].fail=t[u].cnt=0; return u;
	}

	void insert(char *s) {
		int u=root,n=strlen(s);
		rep(i,0,n) {
			int c=s[i]-'a';
			if (!t[u].go[c]) t[u].go[c]=newnode();
			u=t[u].go[c];
		}
		t[u].cnt++;
	}

	void build() {
		queue<int> q; int u=root;
		rep(i,0,26) if (t[u].go[i]) 
			t[t[u].go[i]].fail=u,q.push(t[u].go[i]);
		while (q.size()) {
			u=q.front(); q.pop();
			rep(i,0,26) {
				int &v=t[u].go[i];
				if (!v) v=t[t[u].fail].go[i];
				else t[v].fail=t[t[u].fail].go[i],q.push(v); 
			}
		}
	}

	int query(char *s) {
		int u=root,ans=0,n=strlen(s);
		rep(i,0,n) {
			int c=s[i]-'a';	u=t[u].go[c];
			for (int j=u;j&&t[j].cnt!=-1;j=t[j].fail) 
				ans+=t[j].cnt,t[j].cnt=-1;
		}
		return ans;
	}
}ac;

char s[N];
int n;

int main() {
#ifdef LOCAL
	freopen("A.in","r",stdin);
#endif
	scanf("%d",&n); ac.init();
	rep(i,0,n) scanf("%s",s),ac.insert(s);
	ac.build();
	scanf("%s",s);
	printf("%d\n",ac.query(s));
	return 0;
}