#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
const int N=200010;
int head[N],cnt=0;
struct edge{
	int to,nxt;
}e[N<<1];
inline void add(int x,int y){
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
inline void addedge(int x,int y){
	add(x,y);
	add(y,x);
}
inline int id(int i){return ceil(1.0*i/2.0);}
vector<int>pre[N];
int d[N];
void bfs(int s){
	queue<int>q;
	q.push(s);
	memset(d,0,sizeof(d));
	d[s]=1;
	while (q.size()){
		int x=q.front();
		q.pop();
//		cerr<<x<<endl;
		for (int i=head[x];i;i=e[i].nxt){
			int v=e[i].to;
			if (!d[v]){
				d[v]=d[x]+1;
				q.push(v);
				pre[v].push_back(id(i));
			}
			else if (d[v]==d[x]+1)
				pre[v].push_back(id(i));
		}
	}
}
int n,m,k,tot=0;
int used[N];
void output(){
	tot++;
	rep (i,1,m)
		printf("%d",used[i]);
	puts("");
}
void dfs(int now){
	if (tot>=k)return;
	if (now>n){
		output();
		return;
	}
	rep (i,0,pre[now].size()-1){
		int which=pre[now][i];
		used[which]=1;
		dfs(now+1);
		used[which]=0;
	}
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	rep (i,0,m-1){
		int x,y;scanf("%d%d",&x,&y);
		addedge(x,y);
	}
	bfs(1);
//	rep (i,1,n)
//		printf("%d\n",pre[i].size());
	ll ans=1;
	rep (i,2,n){
		ans*=pre[i].size();
		if (ans>=k){
			ans=k;
			break;
		}
	}
	printf("%lld\n",ans);
	dfs(2);
	return 0;
}
/*
4 4 3
1 2
2 3
1 4
4 3
*/
/*
4 6 3
1 2
2 3
1 4
4 3
2 4
1 3
*/
/*
5 6 2
1 2
1 3
2 4
2 5
3 4
3 5
*/

