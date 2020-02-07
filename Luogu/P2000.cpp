#include <bits/stdc++.h>
using namespace std;
const int N=6e5+10,P=998244353,gen=3,igen=(P+1)/gen;
inline int add(int x,int y){
	return x+y>=P?x+y-P:x+y;
}
inline int sub(int x,int y){
	return x-y<0?x-y+P:x-y;
}
inline int fpow(int x,int y){
	int ret=1; for(;y;y>>=1,x=1ll*x*x%P)
		if(y&1) ret=1ll*ret*x%P;
	return ret;
}
int rev[N];
void init(int n){
	for(int i=0;i<n;i++) rev[i]=rev[i>>1]>>1|((i&1)?n>>1:0);
}
void ntt(int *f,int n,int flg){
	for(int i=0;i<n;i++)
		if(rev[i]<i) swap(f[i],f[rev[i]]);
	for(int k=1,len=2;len<=n;len<<=1,k<<=1){
		int wn=fpow(flg==1?gen:igen,(P-1)/len);
		for(int i=0;i<n;i+=len)
			for(int w=1,j=i;j<i+k;j++,w=1ll*w*wn%P){
				int tmp=1ll*w*f[j+k]%P; 
				f[j+k]=sub(f[j],tmp),f[j]=add(f[j],tmp);
			}
	}
	if(flg==-1){
		int inv=fpow(n,P-2);
		for(int i=0;i<n;i++) f[i]=1ll*f[i]*inv%P;
	}
}
struct BigInt{
	static const int bas=100,basl=2;
	int a[N],len;
	int &operator [] (int k1){return a[k1];}
	BigInt(char *s){
		len=strlen(s); reverse(s,s+len);
		for(int i=0;i<len;i++) s[i]-=48;
		for(int i=0;i<len;i+=basl)
			a[i>>1]=s[i]+s[i+1]*10;
		maintain();
	}
	BigInt(){memset(a,0,sizeof(a));len=0;}
	void maintain(){
		while(len&&!a[len-1])len--;
		while(a[len])a[len]+=a[len-1]/bas,a[len-1]%=bas,len++;
	}
	void mdf(){
		a[0]++; for(int i=0;i<len;i++) a[i+1]+=a[i]/bas,a[i]%=bas;
		maintain();
	}
	BigInt operator * (BigInt &k1){
		int n=len,m=k1.len; int limit=1;while(limit<=n+m-1)limit<<=1; init(limit);
		static int A[N],B[N];
		for(int i=0;i<limit;i++) A[i]=a[i],B[i]=k1[i];
		ntt(A,limit,1),ntt(B,limit,1);
		BigInt ans; ans.len=n+m;
		for(int i=0;i<limit;i++) ans[i]=1ll*A[i]*B[i]%P;
		ntt(ans.a,limit,-1);
		for(int i=0;i<ans.len;i++) ans[i+1]+=ans[i]/bas,ans[i]%=bas;
		ans.maintain();
		return ans;
	}
	BigInt operator /= (int q){
		int r=0;
		for(int i=len-1;i>=0;i--){
			int nw=r*100+a[i];
			a[i]=nw/q; r=nw%q;
		}
		maintain();
		return *this;
	}
	void print(){
		printf("%d",a[len-1]);
		for(int i=len-2;i>=0;i--) printf("%.02d",a[i]);
	}
}a[5],ans;
char s[1000010];
int main(){
	scanf("%s",s); a[1]=s;
	a[1].mdf();for(int i=2;i<=4;i++) a[i]=a[i-1],a[i].mdf();
	ans=a[1]*a[2]*a[3]*a[4];
	ans/=24;
	ans.print();
	return 0;
}