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
	int go[SIGMA],fail,id;
	inline void clr() {memset(go,0,sizeof(go)); fail=id=0;}
}t[N];
int cnt,root;

inline void init() {root=cnt=0; t[root].clr();}
inline int newnode() {int u=++cnt; t[u].clr(); return u;}

int append(int u,int c) {
	if (!t[u].go[c]) t[u].go[c]=newnode();
	return t[u].go[c];
}
void build() {
	queue<int> q; int u=root;
	rep(i,0,SIGMA) if (t[u].go[i]) 
		t[t[u].go[i]].fail=u,q.push(t[u].go[i]);
	while (q.size()) {
		int u=q.front(); q.pop();
		rep(i,0,SIGMA) {
			int &v=t[u].go[i];
			if (!v) v=t[t[u].fail].go[i];
			else t[v].fail=t[t[u].fail].go[i],q.push(v);
		}
	}
}

char s[N],ts[N],ans[N];
int n,len[N],stk[N];

int main() {
#ifdef LOCAL
	freopen("A.in","r",stdin);
#endif
	init();
	scanf("%s",s); len[0]=strlen(s);
	scanf("%d",&n);
	rep(i,1,n+1) {
		scanf("%s",ts);
		len[i]=strlen(ts);
		int u=root; rep(j,0,len[i]) u=append(u,ts[j]-'a'); 
		t[u].id=i;
	}
	build();
	int top=0,tans=0,u=root;
	rep(i,0,len[0]) {
		int c=s[i]-'a'; u=t[u].go[c];
		if (t[u].id) {
			int j=t[u].id; tans-=len[j],top-=len[j];
			top++,tans++;
			if (top<=0) tans=top=0,u=root;
			else u=stk[top];
		}
		else ans[++tans]=s[i],stk[++top]=u;
		// cout<<i+1<<"("<<s[i]<<"): "<<top<<" "<<stk[top]<<endl;
	}
	rep(i,1,tans+1) putchar(ans[i]);
	return 0;
}

/*
beginthatthebreakofdawn
beginthatthebreakofdawn
begintheescapexecutionatthebreakofdawn 
begintheescaatthebreakofdawn
*/