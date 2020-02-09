#include <bits/stdc++.h>
using namespace std;
typedef long double db;
typedef long long ll;
const db PI=acos(-1.0);
const int N=8e5+10;
int mod;
inline int fpow(int x,int y){
	int ret=1; for(x%=mod;y;y>>=1,x=1ll*x*x%mod)
		if(y&1) ret=1ll*ret*x%mod;
	return ret;
}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+mod:x-y;}
namespace Poly{
	struct cpl{
		db x,y;
		cpl operator + (cpl k1)const{return (cpl){x+k1.x,y+k1.y};}
		cpl operator - (cpl k1)const{return (cpl){x-k1.x,y-k1.y};}
		cpl operator * (cpl k1)const{return (cpl){x*k1.x-y*k1.y,x*k1.y+y*k1.x};}
	};
	int rev[N];
	void init(int n){
		for(int i=0;i<n;i++)
			rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
	}
	void fft(cpl *f,int n,int flg){
		for(int i=0;i<n;i++) if(rev[i]<i) swap(f[i],f[rev[i]]);
		for(int len=2,k=1;len<=n;len<<=1,k<<=1){
			cpl wn=(cpl){cos(2*PI/len),flg*sin(2*PI/len)};
			for(int i=0;i<n;i+=len){
				cpl w=(cpl){1,0};
				for(int j=i;j<i+k;j++,w=w*wn){
					cpl tmp=w*f[j+k];
					f[j+k]=f[j]-tmp,f[j]=f[j]+tmp;
				}
			}
		}
		if(flg==-1) for(int i=0;i<n;i++)
			f[i].x/=n;
	}
	void mtt(int *a,int *b,int *c,int n){
		static cpl f[2][N],g[2][N],ans[3][N];
		for(int i=0;i<n;i++){
			f[0][i]=(cpl){(db)(a[i]>>15),0};
			f[1][i]=(cpl){(db)(a[i]&0x7fff),0};
			g[0][i]=(cpl){(db)(b[i]>>15),0};
			g[1][i]=(cpl){(db)(b[i]&0x7fff),0};
		}
		fft(f[0],n,1),fft(f[1],n,1),fft(g[0],n,1),fft(g[1],n,1);
		for(int i=0;i<n;i++){
			ans[0][i]=f[0][i]*g[0][i];
			ans[1][i]=f[0][i]*g[1][i]+f[1][i]*g[0][i];
			ans[2][i]=f[1][i]*g[1][i];
		}
		fft(ans[0],n,-1),fft(ans[1],n,-1),fft(ans[2],n,-1);
		#define normal(x) (((ll)((x)+0.5)%mod+mod)%mod)
		for(int i=0;i<n;i++){
			ll t1=(normal(ans[0][i].x)<<30ll)%mod;
			ll t2=(normal(ans[1][i].x)<<15ll)%mod,t3=normal(ans[2][i].x);
			c[i]=((t1+t2)%mod+t3)%mod;
		}
	}
	void dao(int *f,int n,int *G){
		static int F[N]; for(int i=0;i<=n;i++) F[i]=f[i];
		for(int i=1;i<=n;i++) G[i-1]=1ll*F[i]*i%mod; G[n]=0;
	}
	void jifen(int *f,int n,int *G){
		static int F[N]; for(int i=0;i<=n;i++) F[i]=f[i];
		for(int i=0;i<=n;i++) G[i+1]=1ll*F[i]*fpow(i+1,mod-2)%mod; G[0]=0;
	}
	void getinv(int *f,int n,int *G){
		if(n==1){G[0]=fpow(f[0],mod-2);return;}
		getinv(f,(n+1)>>1,G);
		static int F[N],H[N],H1[N];
		int limit=1; while(limit<=(n-1)*2)limit<<=1; init(limit);
		for(int i=0;i<n;i++) H[i]=G[i],F[i]=f[i];
		for(int i=n;i<limit;i++) H[i]=F[i]=G[i]=0;
		mtt(F,G,H1,limit);
//		cout<<"in INV: "; for(int i=0;i<limit/2;i++) cout<<H1[i]<<" "; cout<<endl;
		H1[0]=sub(2,H1[0]);
		for(int i=1;i<limit;i++) H1[i]=i<n?mod-H1[i]:0;
		for(int i=n;i<limit;i++) H1[i]=0;
		mtt(H,H1,G,limit);
		for(int i=n;i<limit;i++) G[i]=0;
	}
	void getln(int *f,int n,int *G){
		static int F[N],iF[N]; for(int i=0;i<n;i++) F[i]=f[i];
		getinv(F,n,iF),dao(F,n-1,F);
//		cout<<"INV: "; for(int i=0;i<n;i++) cout<<iF[i]<<" "; cout<<endl;
//		cout<<"DAO: "; for(int i=0;i<n;i++) cout<<F[i]<<" "; cout<<endl;
		int limit=1; while(limit<=(n-1)*2)limit<<=1; init(limit);
		mtt(F,iF,G,limit);
//		cout<<"FINAL: "; for(int i=0;i<limit;i++) cout<<G[i]<<" "; cout<<endl;
		jifen(G,n-1,G); for(int i=n;i<limit;i++) G[i]=0;
//		cout<<"FINAL: "; for(int i=0;i<limit;i++) cout<<G[i]<<" "; cout<<endl;
	}
}
int n,f[N],ans[N];
int main(){
	scanf("%d%d",&n,&mod);
	f[0]=1; for(int i=1;i<=n;i++) scanf("%d",&f[i]);
	Poly::getln(f,n+1,ans);
	for(int i=1;i<=n;i++) ans[i]=1ll*ans[i]*i%mod;
	for(int i=1;i<=n;i++)
		for(int j=i*2;j<=n;j+=i) ans[j]=sub(ans[j],ans[i]);
	int cnt=0;
	for(int i=1;i<=n;i++) if (ans[i]) ++cnt;
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++) if(ans[i]) printf("%d ",i);
	return 0;
}
