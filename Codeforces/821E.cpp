#include <bits/stdc++.h>
using namespace std;
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
typedef long long ll;
const int N=16;
const ll MOD=1e9+7;
struct matrix{
	int n,m;
	ll a[20][20];
	matrix(int r=N,int c=N):n(r),m(c){memset(a,0,sizeof(a));}
	matrix operator * (const matrix& k1) const{
	//	assert(m==k1.n);
	//	cerr << m << k1.n << endl;
		matrix res(n,k1.m);
		rep (k,0,m-1) rep (i,0,n-1) rep (j,0,k1.m-1)
			res.a[i][j]=(res.a[i][j]+this->a[i][k]*k1.a[k][j])%MOD;
		return res;
	}
	void print(char end='\n'){
		rep (i,0,n-1){
			rep (j,0,m-1)
				printf("%lld ",a[i][j]);
			puts("");
		}
		putchar(end);
	}
};
matrix power(matrix A,ll t){
	matrix res(N,N);
	rep (i,0,N-1)res.a[i][i]=1;
	for (;t;t>>=1){
		if (t&1)res=res*A;
		A=A*A;
//		res.print();
	}
//	res.print();
	return res;
}
int main(){
	int n;ll K;
	scanf("%d%lld",&n,&K);
	matrix f(N,1),A;
	f.a[0][0]=1;
	rep (it,1,n){
		ll l,r;int h;
		scanf("%lld%lld%d",&l,&r,&h);
		r=min(K,r);
		rep (i,0,N-1)rep (j,0,N-1)A.a[i][j]=0;
		rep (i,0,N-1){
			if (i-1>=0)A.a[i][i-1]=1;
			A.a[i][i]=1;
			if (i+1<N)A.a[i][i+1]=1;
		}
		rep (i,h+1,N-1) rep (j,0,N-1)
			A.a[i][j]=0;
		if (h+1<N)A.a[h][h+1]=0;
//		A.print();
		A=power(A,r-l);
//		A.print();
		f=A*f;
//		f.print();
	}
	printf("%lld\n",f.a[0][0]%MOD);
	return 0;
}
/*
1 3
0 3 3
*/
/*
2 6
0 3 0
3 10 2
*/




