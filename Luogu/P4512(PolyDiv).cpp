#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10,P=998244353,gen=3,igen=(P+1)/gen;
inline int fpow(int x,int y){
	int ret=1; for (x%=P;y;y>>=1,x=1ll*x*x%P)
		if (y&1) ret=1ll*ret*x%P;
	return ret;
}
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
namespace Poly{
	int rev[N];
	void init(int n){
		for (int i=0;i<n;i++) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
	}
	void ntt(int *f,int n,int flg){
		for (int i=0;i<n;i++) if (rev[i]<i) swap(f[i],f[rev[i]]);
		for (int k=1,len=2;len<=n;len<<=1,k<<=1){
			int wn=fpow(flg==1?gen:igen,(P-1)/len);
			for (int i=0;i<n;i+=len){
				for (int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
					int tmp=1ll*w*f[j+k]%P;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
			}
		}
		if (flg==-1){
			int inv=fpow(n,P-2);
			for (int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
		}
	}
	void getinv(int *f,int n,int *G){
		if (n==1){G[0]=fpow(f[0],P-2);return;}
		getinv(f,(n+1)>>1,G);
		static int F[N];
		int limit=1; for (;limit<=n*2;limit<<=1); init(limit);
		for (int i=0;i<limit;i++) F[i]=i>=n?0:f[i],G[i]=i>=n?0:G[i];
		ntt(F,limit,1),ntt(G,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*G[i]*sub(2,1ll*F[i]*G[i]%P)%P;
		ntt(G,limit,-1);
		for (int i=n;i<limit;i++) G[i]=0;
	}
	void van(int *f,int n){
		for (int i=0,j=n;i<j;i++,j--)swap(f[i],f[j]);
	}
	void div(int *f,int n,int *g,int m,int *Q,int *R){
		static int F[N],G[N],iG[N],qwq[N];
		for (int i=0;i<=n;i++) F[i]=f[i];
		for (int i=0;i<=m;i++) G[i]=g[i];
		van(F,n),van(G,m); getinv(G,n-m+1,iG);
/*		cout<<"F: "; for (int i=0;i<=n;i++) cout<<F[i]<<" "; cout<<endl;
		cout<<"G: "; for (int i=0;i<=m;i++) cout<<G[i]<<" "; cout<<endl;
		cout<<"iG: "; for (int i=0;i<=n-m+1;i++) cout<<iG[i]<<" "; cout<<endl; */
		int limit=1; while (limit<=2*n)limit<<=1; init(limit);
		for (int i=n+1;i<limit;i++) F[i]=0;
		for (int i=n-m+1;i<limit;i++) iG[i]=0;
		ntt(F,limit,1),ntt(iG,limit,1);
		for (int i=0;i<limit;i++) Q[i]=1ll*F[i]*iG[i]%P;
		ntt(Q,limit,-1);
		for (int i=n-m+1;i<limit;i++) Q[i]=0;
		van(Q,n-m);
		for (int i=0;i<=n-m;i++) qwq[i]=Q[i];
		for (int i=n-m+1;i<limit;i++) qwq[i]=0;
		for (int i=0;i<=m;i++) G[i]=g[i];
		for (int i=m+1;i<limit;i++) G[i]=0;
		limit=1; while(limit<=n)limit<<=1; init(limit);
		ntt(qwq,limit,1),ntt(G,limit,1);
		for (int i=0;i<limit;i++) G[i]=1ll*G[i]*qwq[i]%P;
		ntt(G,limit,-1);
		for (int i=n+1;i<limit;i++) G[i]=0;
		for (int i=0;i<m;i++) R[i]=sub(f[i],G[i]);
	}
}
int n,m,f[N],g[N],q[N],r[N];
int main(){
	scanf("%d%d",&n,&m);
	for (int i=0;i<=n;i++) scanf("%d",&f[i]);
	for (int i=0;i<=m;i++) scanf("%d",&g[i]);
	Poly::div(f,n,g,m,q,r);
	for (int i=0;i<=n-m;i++) printf("%d ",q[i]); puts("");
	for (int i=0;i<m;i++) printf("%d ",r[i]);
	return 0;
}
