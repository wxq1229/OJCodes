#include <bits/stdc++.h>
using namespace std;
const int N=300010,P=998244353,G=3,IG=(P+1)/G;
inline int fpow(int a,int b){
	int ret=1; for (;b;b>>=1,a=1ll*a*a%P)
		if(b&1)ret=1ll*ret*a%P;
	return ret;
}
inline int add(int x,int y){return x+y>=P?x+y-P:x+y;}
inline int sub(int x,int y){return x-y<0?x-y+P:x-y;}
namespace Poly{
	int rev[N];
	void init(int limit){
		for (int i=0;i<limit;i++) rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
	}
	void ntt(int *f,int n,int flg){
		for (int i=0;i<n;i++)
			if(rev[i]<i) swap(f[i],f[rev[i]]);
		for (int len=2,k=1;len<=n;len<<=1,k<<=1){
			int wn=fpow(flg==1?G:IG,(P-1)/len);
			for (int i=0;i<n;i+=len){
				for (int j=i,w=1;j<i+k;j++,w=1ll*w*wn%P){
					int tmp=1ll*w*f[j+k]%P;
					f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
				}
			}	
		}
	}
}
using Poly::ntt;
int ans[N],f[N],g[N],a[N],n;
void solve(int l,int r){
	if (l+1>=r) return;
	int mid=l+((r-l)>>1);
	solve(l,mid); int len=r-l;
	Poly::init(len);
	for (int i=0;i<len;i++) g[i]=a[i];
	for (int i=l;i<mid;i++) f[i-l]=ans[i];
	for (int i=mid;i<r;i++) f[i-l]=0;
	ntt(f,len,1),ntt(g,len,1);
	for (int i=0;i<len;i++) f[i]=1ll*f[i]*g[i]%P;
	ntt(f,len,-1); int inv=fpow(len,P-2);
	for (int i=mid;i<r;i++) ans[i]=add(ans[i],1ll*f[i-l]*inv%P);
	solve(mid,r);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<n;i++) scanf("%d",&a[i]);
	int limit=1; while(limit<=n)limit<<=1;
	ans[0]=1,solve(0,limit);
	for (int i=0;i<n;i++)printf("%d ",ans[i]);
	return 0;
}
