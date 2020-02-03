#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD=1e9+7;
struct matrix{
	ll a[30][30];
	matrix(){memset(a,0,sizeof(a));}
	matrix operator * (const matrix& k1)const{
		matrix res;
		for (int k=0;k<26;k++)
			for (int i=0;i<26;i++)
				for (int j=0;j<26;j++)
					res.a[i][j]=(res.a[i][j]+a[i][k]%MOD*k1.a[k][j]%MOD)%MOD;
		return res;
	}
};
matrix power(matrix A,ll t){
	matrix res;
	for (int i=0;i<26;i++)res.a[i][i]=1;
	while (t){
		if (t&1) res=res*A;
		A=A*A;
		t>>=1;
	}
	return res;
}
void print(matrix A){
	for (int i=0;i<26;i++){
		for (int j=0;j<26;j++)
			cerr<<A.a[i][j]<<" ";
		cerr<<endl;
	}
}
char s[100010];
int main(){
	matrix A;
	for (int i=0;i<26;i++)
		for (int j=0;j<26;j++)A.a[i][j]=1;
//	print(A);
	ll n;scanf("%lld",&n);
	scanf("%s",s);
	int m=strlen(s);
	for (int i=0;i<m-1;i++)A.a[s[i]-'a'][s[i+1]-'a']=0;
//	print(A);
	A=power(A,n-1);
//	print(A);
	ll ans=0;
	for (int i=0;i<26;i++)
		for (int j=0;j<26;j++)
			ans=(ans+A.a[i][j])%MOD;
	printf("%lld\n",ans%MOD);
	return 0;
}
