#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
typedef pair<int,int> pii;
typedef vector<pii> pfac;
pfac factor(int n,int k)
{
	pfac ans;
	for(int i=2;i*i<=n;i++)
	{
		int cnt=0;
		while(n%i==0) (++cnt)>=k?cnt-=k:0,n/=i;
		if(cnt) ans.pb(mp(i,cnt));
	}
	if(n>1&&k!=1) ans.pb(mp(n,1));
	return ans;
}
pfac mpfac(const pfac &pf,int k)
{
	pfac ans;
	for (auto p:pf) ans.pb(mp(p.fi,k-p.se));
	return ans;
}
const int N=1111111;
int n,m,k;
struct edge
{
	int u,v,w,l,nxt;
	pfac pf;
}e[N];
int fst[N],ec=0,ind[N],ans=0;
void ade(int u,int v,int w,int l)
{
	e[++ec]=(edge){u,v,w,l};
	e[ec].pf=factor(w,k);
	e[ec].nxt=fst[u],fst[u]=ec;
	++ind[v];
	ans=max(ans,l);
}
int tps[N],tn;
void topo()
{
	tn=0;
	queue<int> q;
	for(int i=1;i<=n;i++) if(ind[i]==0) q.push(i);
	while(q.size())
	{
		int u=q.front(); q.pop();
		tps[++tn]=u;
		for(int i=fst[u];i;i=e[i].nxt)
		{
			int v=e[i].v; --ind[v];
			if (ind[v]==0) q.push(v);
		}
	}
}
map<pfac,int> f[N];
void dp()
{
	for(int i=1;i<=tn;i++)
	{
		int u=tps[i];
		for(int j=fst[u];j;j=e[j].nxt)
		{
			int v=e[j].v;
			pfac pf=e[j].pf,mpf=mpfac(pf,k);
			f[v][mpf]=max(f[v][mpf],f[u][pf]+e[j].l);
			ans=max(ans,f[v][mpf]);
		}
	}
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1,u,v,w,l;i<=m;i++)
		scanf("%d%d%d%d",&u,&v,&w,&l),ade(u,v,w,l);
	topo(),dp();
	printf("%d\n",ans);
	return 0;
}
