#include <bits/stdc++.h>
using namespace std;
inline char NC(){
	static char buf[1<<10], *p1=buf, *p2=buf;
	if (p1==p2) p2 = (p1=buf)+fread(buf,1,1433223,stdin);
	return p1==p2 ? EOF : *p1++;
}
template<class T> inline T RD(){
	T x=0, f=1; char ch; while(!isdigit(ch=NC())) f = ch=='-'?-f:f;
	while (isdigit(ch)){ x = x*10+ch-'0'; ch = NC(); }
	return x*f;
}

#define read() RD<int>()
#define rep(i,a,b) for (int i=(int)(a);i<=(int)(b);i++)
#define per(i,a,b) for (int i=(int)(a);i>=(int)(b);i--)

const int N = 4100;
int a[N][N], f[2][N], q[N], dl[N], dr[N];

int main(){
	int n=read(), m=read(), K=read(), T=read();
	rep(i,1,K){
		int x=read(), y=read();
		a[x][y] = read();
	}
	int nw = 0;
	rep(i,1,m) f[nw][i] = a[1][i];
	rep(i,2,n){
		nw ^= 1;
		int l = 1, r = 0;
		rep(j,1,m){
			while (l<=r && f[nw^1][q[r]]<=f[nw^1][j]) r--;
			q[++r] = j;
			while (l<=r && abs(j-q[l])>T) l++;
			dl[j] = f[nw^1][q[l]] + a[i][j];
		}
		l=1, r=0;
		per(j,m,1){
			while (l<=r && f[nw^1][q[r]]<=f[nw^1][j]) r--;
			q[++r] = j;
			while (l<=r && abs(j-q[l])>T) l++;
			dr[j] = f[nw^1][q[l]] + a[i][j];
		}
		rep(j,1,m) f[nw][j] = max(dl[j],dr[j]);
	}
	int ans=0;
	rep(i,1,m) ans = max(ans,f[nw][i]);
	printf("%d\n",ans);
	return 0;
}
