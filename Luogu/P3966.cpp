#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;++i)
#define per(i,a,n) for (int i=n-1;i>=a;--i)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(),(x).end()
#define SZ(x) ((int)(x).size())
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
typedef vector<int> VI;

const int N=1e6+10,SIGMA=26;

struct node {
	int go[SIGMA],fail,val,id;
	inline void clr() {memset(go,0,sizeof(go));fail=val=id=0;}
}t[N];
int root,cnt;
inline void init() {root=cnt=0; t[root].clr();}
inline int newnode() {int u=++cnt; t[u].clr(); return u;}

inline int append(int u,int c) {
	if (!t[u].go[c]) t[u].go[c]=newnode(); 
	return t[u].go[c];
}
void build() {
	queue<int> q; int u=root;
	rep(i,0,26) if (t[u].go[i]) t[t[u].go[i]].fail=u,q.push(t[u].go[i]);
	while (q.size()) {
		u=q.front(); q.pop();
		rep(i,0,26) {
			int &v=t[u].go[i];
			if (!v) v=t[t[u].fail].go[i];
			else t[v].fail=t[t[u].fail].go[i],q.push(v);
		}
	}
}

int n,fst[N];
char s[N];

VI e[N]; int sum[N],ans[N];

void getans(int u,int ff) {
	sum[u]=t[u].val;
	for (auto v:e[u]) {
		if (v!=ff) getans(v,u),sum[u]+=sum[v];
	}
	ans[t[u].id]=sum[u];
}

int main() {
	init();
	scanf("%d",&n);
	rep(i,1,n+1) {
		scanf("%s",s); int len=strlen(s),u=root;
		rep(j,0,len) u=append(u,s[j]-'a'),t[u].val++;
		if (!t[u].id) t[u].id=i; fst[i]=t[u].id;
	}
	build();
	rep(i,1,cnt+1) {
		// cout<<t[i].fail<<"->"<<i<<endl;
		e[t[i].fail].pb(i),e[i].pb(t[i].fail);
	}
	getans(root,-1);
	rep(i,1,n+1) printf("%d\n",ans[fst[i]]);
	return 0;
}

/*
3
a
aa
aaa
*/