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

const int N=1e6+10,mod=1004535809,gn=3;
inline int powmod(int x,int y=mod-2,int m=mod) {
	int ret=1; for (;y;y>>=1,x=1ll*x*x%m) 
		if (y&1) ret=1ll*ret*x%m;
	return ret;
}
const int ign=powmod(gn);
inline int add(int x,int y,int m=mod) {return (x+=y)>=m?x-m:x;}
inline int sub(int x,int y,int m=mod) {return (x-=y)<0?x+m:x;}

namespace Poly {
	int rev[N];
	inline void init(int n) {rep(i,0,n) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);}
	inline int glim(int n) {int lim=1; while (lim<=n) lim<<=1; return lim;}

	void NTT(int *f,int n,int flg) {
		// cout<<"NTT(rev): "; rep(i,0,n) cout<<rev[i]<<" "; cout<<endl;
		rep(i,0,n) if (rev[i]<i) swap(f[i],f[rev[i]]);
		for (int len=2,k=1;len<=n;len<<=1,k<<=1) {
			int wn=powmod(flg==1?gn:ign,(mod-1)/len);
			for (int i=0;i<n;i+=len)
				for (int j=i,w=1;j<i+k;j++,w=1ll*w*wn%mod) {
					int tmp=1ll*f[j+k]*w%mod;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
		}
		if (flg==-1) {
			int inv=powmod(n);
			rep(i,0,n) f[i]=1ll*f[i]*inv%mod;
		}
	}

	void Mul(const int *a,const int *b,int lim,int *c) {
		static int f[N],g[N]; init(lim);
		rep(i,0,lim) f[i]=a[i],g[i]=b[i];
		NTT(f,lim,1),NTT(g,lim,1);
		rep(i,0,lim) c[i]=1ll*f[i]*g[i]%mod;
		NTT(c,lim,-1);
	}

	void Inv(const int *f,int n,int *g) {
		if (n==1) {g[0]=powmod(f[0]);return;}
		Inv(f,(n+1)>>1,g);
		// cout<<"Inv: "; rep(i,0,n) cout<<g[i]<<" "; cout<<endl;
		static int f1[N]; int lim=glim((n-1)<<1); init(lim);
		rep(i,0,lim) f1[i]=i<n?f[i]:0,g[i]=i<n?g[i]:0;
		NTT(f1,lim,1),NTT(g,lim,1);
		rep(i,0,lim) g[i]=1ll*g[i]*sub(2,1ll*f1[i]*g[i]%mod)%mod;
		NTT(g,lim,-1);
		rep(i,n,lim) g[i]=0;
	}

	void Derv(const int *f,int n,int *g) {
		rep(i,1,n) g[i-1]=1ll*f[i]*i%mod;
		g[n-1]=0;
	}
	void Inte(const int *f,int n,int *g) {
		rep(i,0,n) g[i+1]=1ll*f[i]*powmod(i+1)%mod;
		g[0]=g[n]=0;
	}

	void Ln(const int *f,int n,int *g) {
		// cout<<"LN: "; rep(i,0,n) cout<<f[i]<<" "; cout<<endl;
		static int derf[N],invf[N],derg[N];
		Derv(f,n,derf),Inv(f,n,invf);
		// rep(i,0,n) cout<<derf[i]<<" "; cout<<endl;
		// rep(i,0,n) cout<<invf[i]<<" "; cout<<endl;
		int lim=glim((n-1)<<1);
		rep(i,n,lim) derf[i]=invf[i]=0;
		Mul(derf,invf,lim,derg);
		Inte(derg,n,g);
		rep(i,n,lim) g[i]=0;
		// cout<<" = "; rep(i,0,n) cout<<g[i]<<" "; cout<<endl;
	}

	void Exp(const int *f,int n,int *g) {
		if (n==1) {g[0]=1;return;}
		Exp(f,(n+1)>>1,g);
		// cout<<"Exp:\n"; 
		static int f1[N],lng[N];
		Ln(g,n,lng);
		int lim=glim((n-1)<<1); init(lim);
		rep(i,0,lim) f1[i]=i<n?f[i]:0,g[i]=i<n?g[i]:0;
		// rep(i,0,lim) cout<<g[i]<<" "; cout<<endl;
		// rep(i,0,lim) cout<<lng[i]<<" "; cout<<endl;
		// rep(i,0,lim) cout<<f1[i]<<" "; cout<<endl;
		NTT(g,lim,1),NTT(f1,lim,1),NTT(lng,lim,1);
		rep(i,0,lim) g[i]=1ll*g[i]*sub(add(1,f1[i]),lng[i])%mod;
		NTT(g,lim,-1);
		rep(i,n,lim) g[i]=0;
		// rep(i,0,n) cout<<g[i]<<" "; cout<<endl;
	}

	void Pow(const int *f,int n,int k,int *g) {
		static int lnf[N]; Ln(f,n,lnf);
		// cout<<"Lnf: "; rep(i,0,n) cout<<lnf[i]<<" "; cout<<endl;
		rep(i,0,n) lnf[i]=1ll*lnf[i]*k%mod;
		Exp(lnf,n,g);
	}
}

int a[N],n,k,t,b[N],c[N],ans[N];

inline int read() {
	int x=0; char ch; while (!isdigit(ch=getchar()));
	while (isdigit(ch)) {x=add(10ll*x%mod,ch-48);ch=getchar();}
	return x;
}

int main() {
#ifdef LOCAL
	freopen("a.in","r",stdin);
#endif
	scanf("%d",&n); k=read(); scanf("%d",&t);
	rep(i,0,n) scanf("%d",&a[i]);
	if (t==0) c[0]=1,c[1]=mod-1,Poly::Inv(c,n,b);
	else b[0]=1,b[1]=mod-1;
	memset(c,0,sizeof(c));
	// rep(i,0,n) cout<<b[i]<<" "; cout<<endl;
	Poly::Pow(b,n,k,c);
	// rep(i,0,n) cout<<c[i]<<" "; cout<<endl;
	Poly::Mul(a,c,Poly::glim(2*(n-1)),ans);
	rep(i,0,n) printf("%d%c",ans[i]," \n"[i==n-1]);
	return 0;
}