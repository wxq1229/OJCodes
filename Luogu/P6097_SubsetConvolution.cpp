#include <bits/stdc++.h>
using namespace std;
inline int nc()
{
	const int SZ=233333;
	static char buf[SZ],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,SZ,stdin),p1==p2)?EOF:*p1++;
}
template<typename T> inline T rd()
{
	T x=0; bool f=0; char ch=nc();
	while(!isdigit(ch)) f^=ch=='-',ch=nc();
	while(isdigit(ch)) x=x*10+ch-'0',ch=nc();
	return f?-x:x;
}
#define gi rd<int>
const int MOD=1e9+9;
template<typename T> inline void upd(T &x) {while(x>=MOD)x-=MOD; while(x<0)x+=MOD;}
void fwt(int *f,int n,int flg)
{
	for(int len=2,k=1;len<=n;len<<=1,k<<=1)
		for(int i=0;i<n;i+=len)
			for(int j=i;j<i+k;j++) upd(f[j+k]+=flg*f[j]);
}
const int N=(1<<20)+5;
int f[23][N],g[23][N],h[23][N],bitcnt[N];
int main()
{
	int n=gi(),lim=1<<n;
	bitcnt[0]=0;
	for(int i=1;i<lim;i++) bitcnt[i]=bitcnt[i>>1]+i%2;
	for(int i=0;i<lim;i++) f[bitcnt[i]][i]=gi();
	for(int i=0;i<lim;i++) g[bitcnt[i]][i]=gi();
	for(int i=0;i<=n;i++) fwt(f[i],lim,1),fwt(g[i],lim,1);
	for(int i=0;i<=n;i++)
		for(int j=0;j<lim;j++)
		{
			for(int k=0;k<=i;k++)
				upd(h[i][j]+=1ll*f[k][j]*g[i-k][j]%MOD);
		}
	for(int i=0;i<=n;i++) fwt(h[i],lim,-1);
	for(int i=0;i<lim;i++) printf("%d%c",h[bitcnt[i]][i]," \n"[i==lim-1]);
	return 0;
}