#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int mod,K,g;ll n;
inline int fpow(ll a,ll b){
	int ret=1; for (a%=mod;b;b>>=1,a=1ll*a*a%mod)
		if (b&1) ret=1ll*ret*a%mod;
	return ret;
}
inline int check(int k1){
	for (int i=2;i*i<=mod-1;i++)
		if ((mod-1)%i==0&&(fpow(k1,i)==1||fpow(k1,(mod-1)/i)==1))return 0;
	return 1;
}
inline void getG(){
	for (int i=2;i<=100;i++)
		if (check(i)){g=i;break;}
}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
struct matrix{
	int a[3][3];
	matrix(int R=2,int C=2){
		for (int i=0;i<R;i++)
			for (int j=0;j<C;j++) a[i][j]=0;
	}
	int* operator [] (int k1){return a[k1];}
	matrix operator * (matrix k1)const{
		matrix res;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				for (int k=0;k<2;k++)res[i][j]=add(res[i][j],1ll*a[i][k]*k1[k][j]%mod);
		return res;
	}
	matrix operator * (ll k1)const{
		k1%=mod; matrix ret;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++)
				ret[i][j]=1ll*a[i][j]*k1%mod;
		return ret;
	}
	matrix operator + (matrix k1)const{
		matrix ret;
		for (int i=0;i<2;i++)
			for (int j=0;j<2;j++) ret[i][j]=add(a[i][j],k1[i][j]);
		return ret;
	}
	void print(){
		for (int i=0;i<2;i++,puts(""))
			for (int j=0;j<2;j++)
				printf("%d ",a[i][j]);
	}
};
inline matrix fmpow(matrix A,ll t){
	matrix ret; ret[0][0]=ret[1][1]=1;
	for (;t;t>>=1,A=A*A) if (t&1) ret=ret*A;
	return ret;
}
int main(){
	matrix I; I[0][0]=I[1][1]=1;
	matrix A; A[0][0]=A[0][1]=A[1][0]=1;
	int T;scanf("%d",&T);while(T--){
		scanf("%lld%d%d",&n,&K,&mod);
		getG(); int ans=0,wk=fpow(g,(mod-1)/K);
//		cout<<g<<endl;
//		cout<<"wk: "<<wk<<endl;
		for (int i=0,w=1;i<K;i++,w=1ll*w*wk%mod){
			matrix B=fmpow(A*w+I,n); //B.print();
			ans=add(ans,B[0][1]),ans=add(ans,B[1][1]);
		}
		ans=1ll*ans*fpow(K,mod-2)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
