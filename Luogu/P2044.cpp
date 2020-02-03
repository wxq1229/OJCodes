#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
typedef long long ll;
ll x0,n,m,a,c;
int g;
inline ll add(ll x,ll y){return x+y>=m?x+y-m:x+y;}
inline ll mul(ll x,ll y){
	ll ret=0;
	for (;y;y>>=1,x=add(x,x))if(y&1)ret=add(ret,x);
	return ret;
}
struct matrix{
	int n,m;ll a[3][3];
	matrix(){}
	matrix(int R,int C){
		n=R,m=C;
		rep(i,0,n-1)rep(j,0,m-1)a[i][j]=0;
	}
	matrix operator * (matrix k1)const{
		matrix ret(n,k1.m);
		rep(k,0,k1.n-1)rep(i,0,n-1)rep(j,0,k1.m-1)
			ret.a[i][j]=add(ret.a[i][j],mul(a[i][k],k1.a[k][j]));
		return ret;
	}
}A,C;
matrix fpow(matrix M,ll t){
	matrix ret(M.n,M.m);
	rep(i,0,M.n-1)ret.a[i][i]=1;
	for (;t;t>>=1,M=M*M)if(t&1)ret=ret*M;
	return ret;
}
int main(){
	scanf("%lld%lld%lld%lld%lld%d",&m,&a,&c,&x0,&n,&g);
	a%=m,c%=m,x0%=m;
	A=matrix(2,1);
	A.a[0][0]=x0,A.a[1][0]=c;
	C=matrix(2,2);
	C.a[0][0]=a,C.a[0][1]=1;
	C.a[1][0]=0,C.a[1][1]=1;
	A=fpow(C,n)*A;
	printf("%lld\n",A.a[0][0]%g);
	return 0;
}
