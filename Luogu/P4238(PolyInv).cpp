#include <bits/stdc++.h>
using namespace std;
const int N=1e6+10,P=998244353,G=3,IG=(P+1)/G;
inline int fpow(int x,int y){
	int ret=1; for (;y;y>>=1,x=1ll*x*x%P) if (y&1) ret=1ll*ret*x%P;
	return ret;	
}
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
int rev[N];
void init(int len){
	for (int i=0;i<len;i++) rev[i]=rev[i>>1]>>1|((i&1)?len>>1:0);
}
void ntt(int *f,int n,int flg){
	for (int i=0;i<n;i++) if(rev[i]<i) swap(f[i],f[rev[i]]);
	for (int len=2,k=1;len<=n;len<<=1,k<<=1){
		int wn=fpow(flg==1?G:IG,(P-1)/len);
		for (int i=0;i<n;i+=len){
			for (int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
				int tmp=1ll*w*f[j+k]%P;
				f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
			}
		}
	}
}
int FF[N];
void getinv(int *F,int *G,int n){
	if (n==1){G[0]=fpow(F[0],P-2);return;}
	getinv(F,G,(int)ceil(n/2.0));
	int limit=1; while (limit<=2*n)limit<<=1;
	init(limit);
	for (int i=0;i<n;i++) FF[i]=F[i];
	for (int i=n;i<limit;i++) FF[i]=0;
	ntt(FF,limit,1),ntt(G,limit,1);
	for (int i=0;i<limit;i++) G[i]=1ll*sub(2,1ll*FF[i]*G[i]%P)*G[i]%P;
	ntt(G,limit,-1); int inv=fpow(limit,P-2);
	for (int i=0;i<limit;i++) G[i]=1ll*G[i]*inv%P;
	for (int i=n;i<limit;i++) G[i]=0;
}
int f[N],inv[N];
int main(){
	int n;scanf("%d",&n);
	for (int i=0;i<n;i++)scanf("%d",&f[i]);
	getinv(f,inv,n);
	for (int i=0;i<n;i++)printf("%d ",inv[i]);
	return 0;
}
