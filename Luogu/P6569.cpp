#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace FakeIO
{
	const int SZ=1111111;
	char buf[SZ],*p1=buf,*p2=buf;
	inline char nc() {return p1==p2&&(p2=(p1=buf)+fread(buf,1,SZ,stdin),p1==p2)?EOF:*p1++;}
}
using FakeIO::nc;
template<typename T> inline T rd()
{
	T x=0; char ch=getchar(); bool f=1;
	for(;!isdigit(ch);ch=nc()) f^=ch=='-';
	for(;isdigit(ch);ch=nc()) x=(x<<1)+(x<<3)+(ch^48);
	return f?x:-x;
}
#define gi rd<int>
#define gl rd<ll>
struct mat
{
	int n,m,v[105][105];
	void init(int R=0,int C=0,int val=0)
	{
		n=R,m=C;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++) v[i][j]=val;
	}
	mat(int R=0,int C=0,int val=0) {init(R,C,val);}
	mat operator*(const mat &o)const
	{
//		printf("(%d,%d) * (%d,%d)\n",n,m,o.n,o.m);
		assert(m==o.n);
		mat ans(n,o.m);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=o.m;j++)
				for(int k=1;k<=m;k++)
				{
					ans.v[i][j]+=v[i][k]*o.v[k][j];
					if(ans.v[i][j]>=2) ans.v[i][j]-=2;
				}
		return ans;
	}
};
inline mat I(int n)
{
	mat ans(n,n);
	for(int i=1;i<=n;i++) ans.v[i][i]=1;
	return ans;
}
mat mpw[70];
void matinit(const mat &g)
{
	mpw[1]=g;
	for(int i=2;i<=33;i++) mpw[i]=mpw[i-1]*mpw[i-1];
}
const int N=105;
int n,m,Q;
struct Qry
{
	int id; ll a;
	bool operator<(Qry o)const
	{
		return a<o.a;
	}
}q[N];
ll f0[N],ans[N];
mat f,g;
int main()
{
//	freopen("magic.in","r",stdin);
//	freopen("magic.out","w",stdout);
	n=gi(),m=gi(),Q=gi();
	for(int i=1;i<=n;i++) f0[i]=gl();
	f.init(n,1); f.v[1][1]=1;
	g.init(n,n); // printf("%d %d\n",g.n,g.m);
	for(int i=1;i<=m;i++)
	{
		int u=gi(),v=gi();
		g.v[u][v]=g.v[v][u]=1;
	}
	matinit(g);
//	for(int i=1;i<=n;i++)
//	{
//		for(int j=1;j<=n;j++) printf("%d%c",g.v[i][j]," \n"[j==n]);
//	}
	for(int i=1;i<=Q;i++) q[i].a=gl(),q[i].id=i;
	sort(q+1,q+Q+1);
	q[0].a=0;
	for(int i=1;i<=Q;i++)
	{
//		cout<<i<<endl;
		ll k=q[i].a-q[i-1].a;
		int bit=1;
		while(k)
		{
			if(k&1) f=mpw[bit]*f;
			++bit,k>>=1;
		}
		ll tmp=0;
		for(int j=1;j<=n;j++) if(f.v[j][1]&1) tmp^=f0[j];
		ans[q[i].id]=tmp;
//		cout<<q[i].a<<": "; for(int j=1;j<=n;j++) printf("%d%c",f.v[j][1]," \n"[j==n]);
	}
	for(int i=1;i<=Q;i++) printf("%lld\n",ans[i]);
	return 0;
}
/*
3 3 2
12 13 24
1 2
1 3
2 3
1
2
*/
