#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define per(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define mp make_pair
#define pb push_back
const int MAXN=510;
int a[MAXN],b[MAXN][MAXN],c[MAXN],d[MAXN];
int ans=0,n;
void check(){
	memset(d,0,sizeof(d));
	rep (i,1,n) rep (j,1,n) d[i]+=a[j]*b[i][j];
	int tmp=0;
	rep (i,1,n) tmp+=(d[i]-c[i])*a[i];
	ans=max(ans,tmp);
}
int main(){
	srand(1433233);
	scanf("%d",&n);
	rep (i,1,n) rep (j,1,n) scanf("%d",&b[i][j]);
	rep (i,1,n) scanf("%d",&c[i]),a[i]=1;
	check();
	rep (it,1,1500){
		int i=rand()%n+1;
		a[i]^=1;
		check();
	}
	printf("%d\n",ans);
	return 0;
}
