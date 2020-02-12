#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const ld PI=acos(-1.0);
const int N=3e5+10;
int rev[N];
void init(int n){
	for(int i=0;i<n;i++)
		rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
}
struct cpl{
	ld x,y;
	cpl operator + (cpl k1)const{return (cpl){x+k1.x,y+k1.y};}
	cpl operator - (cpl k1)const{return (cpl){x-k1.x,y-k1.y};}
	cpl operator * (cpl k1)const{return (cpl){x*k1.x-y*k1.y,x*k1.y+y*k1.x};}
};
void fft(cpl *f,int n,int flg){
	for(int i=0;i<n;i++) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int len=2,k=1;len<=n;len<<=1,k<<=1){
		cpl wn=(cpl){cos(2*PI/len),flg*sin(2*PI/len)};
		for(int i=0;i<n;i+=len){
			cpl w=(cpl){1,0};
			for(int j=i;j<i+k;j++,w=w*wn){
				cpl tmp=f[j+k]*w;
				f[j+k]=f[j]-tmp,f[j]=f[j]+tmp;
			}
		}
	}
	if(flg==-1)	for(int i=0;i<n;i++) f[i].x/=n;
}
const int P=1e9+7;
inline int fpow(int x,int y){
	int ret=1; for(x%=P;y;y>>=1,x=1ll*x*x%P)
		if(y&1) ret=1ll*x*ret%P;
	return ret;
}
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
void mtt(int *a,int *b,int *c,int n){
	static cpl F[2][N],G[2][N],ans[3][N];
	for(int i=0;i<n;i++){
		F[0][i]=(cpl){a[i]>>15,0};
		F[1][i]=(cpl){a[i]&0x7fff,0};
		G[0][i]=(cpl){b[i]>>15,0};
		G[1][i]=(cpl){b[i]&0x7fff,0};
	}
	fft(F[0],n,1),fft(F[1],n,1),fft(G[0],n,1),fft(G[1],n,1);
	for(int i=0;i<n;i++){
		ans[0][i]=F[0][i]*G[0][i];
		ans[1][i]=F[0][i]*G[1][i]+F[1][i]*G[0][i];
		ans[2][i]=F[1][i]*G[1][i];
	}
	fft(ans[0],n,-1),fft(ans[1],n,-1),fft(ans[2],n,-1);
	#define normal(x) (((ll)(x+0.5)%P+P)%P)
	for(int i=0;i<n;i++){
		ll A=(normal(ans[0][i].x)<<30ll)%P;
		ll B=(normal(ans[1][i].x)<<15ll)%P;
		ll C=normal(ans[2][i].x);
		c[i]=add(A,add(B,C));
	}
	#undef normal
}
namespace polyInv{int F[N],H[N];}
void getinv(int *f,int n,int *G){
	if(n==1){G[0]=fpow(f[0],P-2);return;}
	getinv(f,(n+1)>>1,G);
	using namespace polyInv;
	int limit=1; while(limit<=(n-1)*2) limit<<=1; init(limit);
	for(int i=0;i<limit;i++)
		F[i]=i>=n?0:f[i],G[i]=i>=n?0:G[i];
	mtt(F,G,H,limit);
	for(int i=n;i<limit;i++) H[i]=0;
	for(int i=0;i<n;i++) H[i]=i==0?sub(2,H[i]):P-H[i];
	mtt(G,H,G,limit);
	for(int i=n;i<limit;i++) G[i]=0;
}
int n,f[N],inv[N];
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",&f[i]);
	getinv(f,n,inv);
	for(int i=0;i<n;i++) printf("%d ",inv[i]);
	return 0;
}
