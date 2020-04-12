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

const int SIGMA=14,N=1e6+10;

struct AC_automation{
	struct node {
		int go[SIGMA],fail;
		ll val;
		void clr() {fail=val=0;memset(go,0,sizeof(go));}
	}t[N];
	int root,cnt;

	void init() { cnt=root=0; t[root].clr(); }
	inline int newnode() { int u=++cnt; t[u].clr(); return u; }

	int append(int u,int c) {
		if (!t[u].go[c]) t[u].go[c]=newnode();
		return t[u].go[c];
	}
	void insert(char *s,ll w) {
		int n=strlen(s),u=root;
		rep(i,0,n) u=append(u,s[i]-'a');
		t[u].val+=w;
	}

	void build() {
		queue<int> q; int u=root;
		rep(i,0,SIGMA) if (t[u].go[i])
			t[t[u].go[i]].fail=u,q.push(t[u].go[i]);
		while (q.size()) {
			int u=q.front(); q.pop();
			t[u].val+=t[t[u].fail].val;;
			rep(i,0,SIGMA) {
				int &v=t[u].go[i];
				if (!v) v=t[t[u].fail].go[i];
				else t[v].fail=t[t[u].fail].go[i],q.push(v);
			}
		}
	}
}ac;

const ll INF=1e18;
char s[401000];
int n,unk[N],totu,m,tots;
PII seg[N];
int ed[1010][20];
ll tmp[1010][20],dp[(1<<14)+10][1010];

int main() {
	ac.init(); scanf("%d",&n);
	rep(i,0,n) {
		ll c; scanf("%s%lld",s,&c);
		ac.insert(s,c);
	}
	ac.build();
	scanf("%s",s+1); m=strlen(s+1);
	rep(i,1,m+1) if (s[i]=='?') unk[++totu]=i;
	{
		int lst=0;
		rep(i,1,m+2) if (i>m||s[i]=='?') 
			seg[++tots]=mp(lst+1,i-1),lst=i;
	}
	rep(i,0,ac.cnt+1) rep(j,1,tots+1) {
		int u=i,l=seg[j].fi,r=seg[j].se;
		rep(k,l,r+1) u=ac.t[u].go[s[k]-'a'],tmp[i][j]+=ac.t[u].val;
		ed[i][j]=u;
	}
	rep(S,0,(1<<14)) rep(i,0,ac.cnt+1) dp[S][i]=-INF;
	dp[0][ed[ac.root][1]]=tmp[ac.root][1];
	rep(S,1,(1<<14)) {
		int cs=__builtin_popcount(S);
		if (cs>=tots) continue;
		rep(i,0,14) if (S&(1<<i)) rep(j,0,ac.cnt+1) {
			int u=ac.t[j].go[i],v=ed[u][cs+1]; ll add=tmp[u][cs+1];
			dp[S][v]=max(dp[S][v],dp[S^(1<<i)][j]+add+ac.t[u].val);
		}
	}
	ll ans=-INF;
	rep(S,0,(1<<14)) if (__builtin_popcount(S)==tots-1)
		rep(j,0,ac.cnt+1) ans=max(ans,dp[S][j]);
	printf("%lld\n",ans); 
	return 0;
}