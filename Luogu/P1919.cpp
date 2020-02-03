#include <bits/stdc++.h>
using namespace std;
typedef double db;
const int N=4e6+10,P=998244353,g=3,ig=(P+1)/g;
inline int fpow(int a,int b,int mod=P){
	int ret=1; for (a%=mod;b;b>>=1,a=1ll*a*a%mod)
		if (b&1) ret=1ll*ret*a%mod;
	return ret;
}
inline int add(int x,int y,int mod=P){return x+y>=mod?x+y-mod:x+y;}
inline int sub(int x,int y,int mod=P){return x-y<0?x-y+mod:x-y;}
int rev[N];
void ntt(int *f,int n,int flg){
	for (int i=0;i<n;i++)
		if (rev[i]<i) swap(f[i],f[rev[i]]);
	for (int len=2;len<=n;len<<=1){
		int wn=fpow(flg==1?g:ig,(P-1)/len);
		for (int i=0;i<n;i+=len){
			int w=1;
			for (int j=i;j<i+(len>>1);j++){
				int tmp=1ll*w*f[j+(len>>1)]%P;
				f[j+(len>>1)]=sub(f[j],tmp);
				f[j]=add(f[j],tmp);
				w=1ll*w*wn%P;
			}
		}
	}
}
char s1[1001000],s2[1001000];
int a[3001000],b[3001000];
int main(){
	scanf("%s",s1);
	scanf("%s",s2);
	int n=strlen(s1),m=strlen(s2),limit=1;
	for (int i=0;i<n;i++) a[i]=s1[n-i-1]-'0';
	for (int i=0;i<m;i++) b[i]=s2[m-i-1]-'0';
	--m,--n; while (limit<=n+m)limit<<=1;
	for (int i=0;i<limit;i++) rev[i]=rev[i>>1]>>1|((i&1)?limit>>1:0);
	ntt(a,limit,1),ntt(b,limit,1);
	for (int i=0;i<limit;i++) a[i]=1ll*a[i]*b[i]%P;
	ntt(a,limit,-1); int invn=fpow(limit,P-2);
	for (int i=0;i<limit;i++) a[i]=1ll*a[i]*invn%P;
	int len=n+m;
	for (int i=0;i<=len;i++)
		a[i+1]+=a[i]/10,a[i]%=10;
	while (a[len+1])++len;
	for (int i=len;i>=0;i--)putchar(a[i]+48);
	return 0;
}
