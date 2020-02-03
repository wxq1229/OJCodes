#include <bits/stdc++.h>
using namespace std;
const int N=3e5+10,P=998244353,G=3,IG=(P+1)/G;
inline int fpow(int a,int b){
	int ret=1; for (;b;b>>=1,a=1ll*a*a%P)
		if (b&1) ret=1ll*a*ret%P;
	return ret;
}
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
int rev[N];
void init(int limit){
	for (int i=0;i<limit;i++)rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
}
void ntt(int *f,int n,int flg){
	for (int i=0;i<n;i++) if (rev[i]<i)swap(f[i],f[rev[i]]);
	for (int len=2,k=1;len<=n;len<<=1,k<<=1){
		int wn=fpow(flg==1?G:IG,(P-1)/len);
		for (int i=0;i<n;i+=len){
			for (int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
				int tmp=1ll*w*f[j+k]%P;
				f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
			}
		}
	}
	if (flg==-1){
		int inv=fpow(n,P-2);
		for (int i=0;i<n;i++)f[i]=1ll*f[i]*inv%P;
	}
}
int f[N],g[N],a[N],inv[N];
int main(){
	int n,k; scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)scanf("%d",&a[i]);
	inv[1]=1; for (int i=2;i<=n;i++) inv[i]=1ll*inv[P%i]*(P-P/i)%P;
	g[0]=1,g[1]=k%P; for (int i=2;i<=n;i++)
		g[i]=1ll*g[i-1]*inv[i]%P*(i+k-1>0?i+k-1:1)%P;
	for (int i=1;i<=n;i++) f[i]=1ll*a[i]*g[i-1]%P;
//	for (int i=1;i<=n;i++) cout<<f[i]<<" "; cout<<endl;
//	for (int i=1;i<=n;i++) cout<<g[i]<<" "; cout<<endl;
	int limit=1; while(limit<=n*2)limit<<=1; init(limit);
	ntt(f,limit,1),ntt(g,limit,1);
	for (int i=0;i<limit;i++) f[i]=1ll*f[i]*g[i]%P;
	ntt(f,limit,-1);
	for (int i=1;i<=n;i++) printf("%d ",f[i]);
	return 0;
}




